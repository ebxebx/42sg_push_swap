#!/usr/bin/env bash
set -euo pipefail

# ================= CONFIG =================
PS_BIN="${PS_BIN:-./push_swap}"
CHK_BIN="${CHK_BIN:-./checker_linux}"

N="${1:-500}"                 # number count
RUNS="${2:-100}"              # random runs
SEED="${SEED:-42}"             # fixed seed (reproducible)
RANGE_MULT="${RANGE_MULT:-10}"

OUT_WORST="${OUT_WORST:-worst_case.txt}"
OUT_CSV="${OUT_CSV:-results.csv}"
# =========================================

if [[ ! -x "$PS_BIN" ]]; then
  echo "push_swap not found: $PS_BIN" >&2
  exit 1
fi
if [[ ! -x "$CHK_BIN" ]]; then
  echo "checker not found: $CHK_BIN" >&2
  exit 1
fi

python3 - <<'PY' "$PS_BIN" "$CHK_BIN" "$N" "$RUNS" "$SEED" "$RANGE_MULT" "$OUT_WORST" "$OUT_CSV"
import sys, random, subprocess, statistics, csv

PS_BIN, CHK_BIN = sys.argv[1], sys.argv[2]
N, RUNS = int(sys.argv[3]), int(sys.argv[4])
SEED = int(sys.argv[5])
RANGE_MULT = int(sys.argv[6])
OUT_WORST, OUT_CSV = sys.argv[7], sys.argv[8]

random.seed(SEED)

def run_case(nums):
    args = list(map(str, nums))
    ps = subprocess.run([PS_BIN, *args], text=True, capture_output=True)
    if ps.returncode != 0:
        return None, "push_swap error"

    ops = ps.stdout
    count = len([l for l in ops.splitlines() if l.strip()])

    chk = subprocess.run([CHK_BIN, *args], input=ops, text=True, capture_output=True)
    if chk.returncode != 0 or chk.stdout.strip() != "OK":
        return None, "checker error"

    return count, None

def gen_random():
    lo, hi = -N * RANGE_MULT, N * RANGE_MULT
    return random.sample(range(lo, hi + 1), N)

def gen_sorted():
    return list(range(N))

def gen_reverse():
    return list(range(N - 1, -1, -1))

def gen_zigzag():
    res = []
    l, r = 0, N - 1
    while l <= r:
        if l == r:
            res.append(l)
        else:
            res.extend([l, r])
        l += 1
        r -= 1
    return res

tests = []
moves = []
worst = (-1, None)

def do_test(name, nums):
    global worst
    count, err = run_case(nums)
    if err:
        print(f"[FAIL] {name}: {err}")
        return
    moves.append(count)
    tests.append((name, count))
    if count > worst[0]:
        worst = (count, nums)
    print(f"[OK] {name:12s} moves={count}")

print("\n=== Fixed pattern tests ===")
do_test("sorted", gen_sorted())
do_test("reverse", gen_reverse())
do_test("zigzag", gen_zigzag())

print("\n=== Random tests ===")
for i in range(1, RUNS + 1):
    do_test(f"random_{i}", gen_random())

# Save worst case
if worst[1]:
    with open(OUT_WORST, "w") as f:
        f.write(" ".join(map(str, worst[1])) + "\n")

# Save CSV
with open(OUT_CSV, "w", newline="") as f:
    writer = csv.writer(f)
    writer.writerow(["case", "moves"])
    for name, c in tests:
        writer.writerow([name, c])

print("\n=== Summary ===")
print(f"N={N}  runs={len(moves)}  seed={SEED}")
print(f"min={min(moves)}")
print(f"median={statistics.median(moves)}")
print(f"avg={sum(moves)/len(moves):.2f}")
print(f"max={max(moves)}")
print(f"Worst case saved to: {OUT_WORST}")
print(f"CSV saved to: {OUT_CSV}")
PY
