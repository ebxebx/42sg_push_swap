#!/usr/bin/env bash
set -euo pipefail

PS_BIN="${PS_BIN:-./push_swap}"
CHK_BIN="${CHK_BIN:-./checker_linux}"

N="${1:-500}"          # how many numbers
RUNS="${2:-50}"        # how many tests
RANGE_MULT="${RANGE_MULT:-10}"
OUT_WORST="${OUT_WORST:-worst_case.txt}"

if [[ ! -x "$PS_BIN" ]]; then
  echo "Error: push_swap binary not found/executable at: $PS_BIN" >&2
  exit 1
fi
if [[ ! -x "$CHK_BIN" ]]; then
  echo "Error: checker not found/executable at: $CHK_BIN" >&2
  exit 1
fi

python3 - <<'PY' "$PS_BIN" "$CHK_BIN" "$N" "$RUNS" "$RANGE_MULT" "$OUT_WORST"
import sys, random, subprocess, statistics

PS_BIN = sys.argv[1]
CHK_BIN = sys.argv[2]
N = int(sys.argv[3])
RUNS = int(sys.argv[4])
RANGE_MULT = int(sys.argv[5])
OUT_WORST = sys.argv[6]

def gen_case(n):
    lo = -n * RANGE_MULT
    hi =  n * RANGE_MULT
    # unique ints
    return random.sample(range(lo, hi+1), n)

moves = []
fails = 0
worst_moves = -1
worst_case = None

for t in range(1, RUNS + 1):
    nums = gen_case(N)
    args = list(map(str, nums))

    # Run push_swap
    try:
        ps = subprocess.run([PS_BIN, *args], text=True, capture_output=True)
    except Exception as e:
        print(f"[{t:03d}] FAIL: could not execute push_swap: {e}")
        fails += 1
        continue

    if ps.returncode != 0:
        print(f"[{t:03d}] FAIL: push_swap exit={ps.returncode}")
        if ps.stdout.strip():
            print("  stdout:", ps.stdout.strip().splitlines()[:3])
        if ps.stderr.strip():
            print("  stderr:", ps.stderr.strip().splitlines()[:3])
        fails += 1
        continue

    ops_text = ps.stdout
    op_lines = [ln for ln in ops_text.splitlines() if ln.strip()]
    count = len(op_lines)

    # Validate with checker_linux (pipe operations to stdin)
    chk = subprocess.run([CHK_BIN, *args], input=ops_text, text=True, capture_output=True)
    result = (chk.stdout or "").strip()

    if chk.returncode != 0 or result != "OK":
        print(f"[{t:03d}] FAIL: checker says {result or '???'} (moves={count})")
        if chk.stderr.strip():
            print("  checker stderr:", chk.stderr.strip().splitlines()[:3])
        fails += 1
        continue

    moves.append(count)
    if count > worst_moves:
        worst_moves = count
        worst_case = nums

    print(f"[{t:03d}] OK   moves={count}")

if worst_case is not None:
    with open(OUT_WORST, "w") as f:
        f.write(" ".join(map(str, worst_case)) + "\n")
    print(f"\nSaved worst case (moves={worst_moves}) to: {OUT_WORST}")

if moves:
    avg = sum(moves) / len(moves)
    mn = min(moves)
    mx = max(moves)
    med = statistics.median(moves)
    print("\n--- Summary ---")
    print(f"N={N}  RUNS={RUNS}  PASS={len(moves)}  FAIL={fails}")
    print(f"min={mn}  median={med}  avg={avg:.2f}  max={mx}")
else:
    print("\nNo successful runs to summarize.")
PY
