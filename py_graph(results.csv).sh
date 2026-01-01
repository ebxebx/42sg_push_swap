python3 - <<'PY'
import csv
import matplotlib.pyplot as plt

moves = []
with open("results.csv") as f:
    r = csv.DictReader(f)
    for row in r:
        if row["case"].startswith("random"):
            moves.append(int(row["moves"]))

plt.plot(moves)
plt.title("push_swap random cases")
plt.ylabel("moves")
plt.xlabel("test #")
plt.show()
PY

