import subprocess
import random
import sys
import time

# ─────────────────────────────────────────────
#  Helpers
# ─────────────────────────────────────────────
GREEN  = '\033[92m'
RED    = '\033[91m'
YELLOW = '\033[93m'
CYAN   = '\033[96m'
BOLD   = '\033[1m'
RESET  = '\033[0m'

def ok(msg):    print(f"  {GREEN}✓ {msg}{RESET}")
def fail(msg):  print(f"  {RED}✗ {msg}{RESET}")
def info(msg):  print(f"  {YELLOW}→ {msg}{RESET}")
def header(msg): print(f"\n{BOLD}{CYAN}{'═'*60}\n  {msg}\n{'═'*60}{RESET}")

total_sections = 0
passed_sections = 0

def section_result(passed, name):
    global total_sections, passed_sections
    total_sections += 1
    if passed:
        passed_sections += 1
        print(f"\n  {GREEN}{BOLD}[SECTION PASS]{RESET} {name}\n")
    else:
        print(f"\n  {RED}{BOLD}[SECTION FAIL]{RESET} {name}\n")

def run_ps(*args):
    r = subprocess.run(["./push_swap"] + list(args), capture_output=True, text=True)
    return r.stdout, r.stderr, r.returncode

def run_checker(args_list, instructions=""):
    r = subprocess.run(["./checker"] + args_list, input=instructions,
                       capture_output=True, text=True)
    return r.stdout.strip(), r.stderr.strip(), r.returncode

def pipe_test(numbers):
    str_nums = [str(n) for n in numbers]
    t0 = time.time()
    ps = subprocess.Popen(["./push_swap"] + str_nums,
                          stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    ps_out, ps_err = ps.communicate()
    elapsed = time.time() - t0
    moves = len([l for l in ps_out.split('\n') if l.strip()])
    ch = subprocess.Popen(["./checker"] + str_nums,
                          stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    ch_out, _ = ch.communicate(input=ps_out)
    return ch_out.strip(), moves, elapsed

def expects_error(args, stdin="", prog="push_swap"):
    exe = f"./{prog}"
    r = subprocess.run([exe] + args, input=stdin, capture_output=True, text=True)
    return "Error" in (r.stdout + r.stderr)

def expects_silence(args, prog="push_swap"):
    exe = f"./{prog}"
    r = subprocess.run([exe] + args, capture_output=True, text=True)
    return r.stdout.strip() == "" and r.stderr.strip() == ""

# ─────────────────────────────────────────────
#  1. Error Management — push_swap (hard)
# ─────────────────────────────────────────────
header("1. Error Management — push_swap")
sec_pass = True

error_cases = [
    (["abc"],                    "Non-numeric single"),
    (["1", "abc", "3"],          "Non-numeric in middle"),
    (["1", "2", "abc"],          "Non-numeric at end"),
    (["a1"],                     "Mixed alpha-digits"),
    (["1.5"],                    "Float number"),
    (["1", "2", "2"],            "Duplicate (simple)"),
    (["3", "3", "3"],            "All same"),
    (["-1", "-1"],               "Negative duplicates"),
    (["0", "1", "0"],            "Zero duplicate"),
    (["2147483648"],             "INT_MAX + 1"),
    (["-2147483649"],            "INT_MIN - 1"),
    (["99999999999"],            "Large overflow"),
    (["-99999999999"],           "Large underflow"),
    (["1", "2147483648", "3"],   "Overflow in middle"),
    (["", "1", "2"],             "Empty string arg"),
    (["1 2 2"],                  "Duplicate inside quoted arg"),
    (["1", "1 2 3 3"],           "Dup inside multiarg quote"),
]
for args, desc in error_cases:
    if expects_error(args):
        ok(f"{desc}")
    else:
        fail(f"{desc}: expected Error")
        sec_pass = False

# No args → silence
if expects_silence([]):
    ok("No args: silent")
else:
    fail("No args: expected silence")
    sec_pass = False

# Single zero → valid, no output
out, err, rc = run_ps("0")
if out.strip() == "" and rc == 0:
    ok("Single '0': silent (valid, already sorted)")
else:
    fail(f"Single '0': got '{out.strip()}' rc={rc}")
    sec_pass = False

section_result(sec_pass, "Error Management (push_swap)")

# ─────────────────────────────────────────────
#  2. Identity Tests (already sorted)
# ─────────────────────────────────────────────
header("2. Identity Tests — already sorted")
sec_pass = True

fixed = [
    (["42"],                           "Single element"),
    (["2", "3"],                       "Two sorted"),
    (["0", "1", "2", "3"],             "Four sorted"),
    (["0","1","2","3","4","5","6","7","8","9"], "Ten sorted"),
    (["-5", "-3", "-1", "0", "2"],     "Negative + positive sorted"),
    (["-2147483648", "2147483647"],    "INT_MIN and INT_MAX sorted"),
]
for args, desc in fixed:
    out, _, _ = run_ps(*args)
    moves = len([l for l in out.split('\n') if l.strip()])
    if moves == 0:
        ok(f"{desc}: 0 moves")
    else:
        fail(f"{desc}: expected 0, got {moves}")
        sec_pass = False

# 10 random already-sorted
for _ in range(10):
    n = random.randint(2, 20)
    lst = sorted(random.sample(range(-100000, 100000), n))
    out, _, _ = run_ps(*[str(x) for x in lst])
    moves = len([l for l in out.split('\n') if l.strip()])
    if moves == 0:
        ok(f"Random sorted {n} values: 0 moves")
    else:
        fail(f"Random sorted {n} values: got {moves}")
        sec_pass = False

section_result(sec_pass, "Identity Tests")

# ─────────────────────────────────────────────
#  3. Simple Version — 3 values (≤3 moves)
# ─────────────────────────────────────────────
header("3. Simple Version — 3 values (max 3 moves)")
sec_pass = True

ch_out, moves, _ = pipe_test([2, 1, 0])
if ch_out == "OK" and moves <= 3:
    ok(f"[2 1 0]: OK, {moves} moves")
else:
    fail(f"[2 1 0]: {ch_out}, {moves} moves (need ≤3)")
    sec_pass = False

# All 6 permutations of {0,1,2}
perms = [[0,1,2],[0,2,1],[1,0,2],[1,2,0],[2,0,1],[2,1,0]]
for p in perms:
    ch_out, moves, _ = pipe_test(p)
    if ch_out == "OK" and moves <= 3:
        ok(f"{p}: OK, {moves} moves")
    else:
        fail(f"{p}: {ch_out}, {moves} moves (need ≤3)")
        sec_pass = False

# 15 random 3-value tests
for _ in range(15):
    nums = random.sample(range(-100000, 100000), 3)
    ch_out, moves, _ = pipe_test(nums)
    if ch_out == "OK" and moves <= 3:
        ok(f"{nums}: OK, {moves} moves")
    else:
        fail(f"{nums}: {ch_out}, {moves} moves")
        sec_pass = False

section_result(sec_pass, "Simple Version (3 values, ≤3 moves)")

# ─────────────────────────────────────────────
#  4. Another Simple — 5 values (≤12 moves)
# ─────────────────────────────────────────────
header("4. Another Simple — 5 values (max 12 moves, kudos ≤8)")
sec_pass = True
kudos_count = 0

fixed5 = [
    [1, 5, 2, 4, 3],
    [5, 4, 3, 2, 1],
    [2, 1, 5, 3, 4],
    [-3, -1, -5, -2, -4],
]
for nums in fixed5:
    ch_out, moves, _ = pipe_test(nums)
    kudos = " 🌟 KUDOS!" if moves <= 8 else ""
    if moves <= 8: kudos_count += 1
    if ch_out == "OK" and moves <= 12:
        ok(f"{nums}: OK, {moves} moves{kudos}")
    else:
        fail(f"{nums}: {ch_out}, {moves} moves (need ≤12)")
        sec_pass = False

for _ in range(20):
    nums = random.sample(range(-100000, 100000), 5)
    ch_out, moves, _ = pipe_test(nums)
    kudos = " 🌟" if moves <= 8 else ""
    if moves <= 8: kudos_count += 1
    if ch_out == "OK" and moves <= 12:
        ok(f"{nums}: OK, {moves} moves{kudos}")
    else:
        fail(f"{nums}: {ch_out}, {moves} moves (need ≤12)")
        sec_pass = False

info(f"KUDOS achieved on {kudos_count}/{24} tests (≤8 moves)")
section_result(sec_pass, "Simple Version (5 values, ≤12)")

# ─────────────────────────────────────────────
#  5. Middle Version — 100 values (rated)
# ─────────────────────────────────────────────
header("5. Middle Version — 100 values (rated 0-5, 20 tests)")
sec_pass = True
all_moves = []

for i in range(20):
    nums = random.sample(range(-100000, 100000), 100)
    ch_out, moves, elapsed = pipe_test(nums)
    all_moves.append(moves)
    status = f"OK, {moves} moves ({elapsed*1000:.0f}ms)"
    if ch_out == "OK":
        ok(f"Test {i+1:2d}: {status}")
    else:
        fail(f"Test {i+1:2d}: checker={ch_out}, {moves} moves")
        sec_pass = False

avg, mx, mn = sum(all_moves)//len(all_moves), max(all_moves), min(all_moves)
info(f"Average: {avg} | Min: {mn} | Max: {mx}")

if   mx < 700:  score=5; grade="5/5 ★★★★★ PERFECT"
elif mx < 900:  score=4; grade="4/5 ★★★★☆"
elif mx < 1100: score=3; grade="3/5 ★★★☆☆"
elif mx < 1300: score=2; grade="2/5 ★★☆☆☆"
elif mx < 1500: score=1; grade="1/5 ★☆☆☆☆"
else:           score=0; grade="0/5 ☆☆☆☆☆ FAIL"

print(f"  {BOLD}Score: {grade}{RESET}")
sec_pass = sec_pass and score >= 1
section_result(sec_pass, f"Middle Version (100 values) — {score}/5")

# ─────────────────────────────────────────────
#  6. Advanced Version — 500 values (rated)
# ─────────────────────────────────────────────
header("6. Advanced Version — 500 values (rated 0-5, 20 tests)")
sec_pass = True
all_moves = []

for i in range(20):
    nums = random.sample(range(-100000, 100000), 500)
    ch_out, moves, elapsed = pipe_test(nums)
    all_moves.append(moves)
    if ch_out == "OK":
        ok(f"Test {i+1:2d}: OK, {moves} moves ({elapsed*1000:.0f}ms)")
    else:
        fail(f"Test {i+1:2d}: {ch_out}, {moves} moves")
        sec_pass = False

avg, mx, mn = sum(all_moves)//len(all_moves), max(all_moves), min(all_moves)
info(f"Average: {avg} | Min: {mn} | Max: {mx}")

if   mx < 5500:  score=5; grade="5/5 ★★★★★ PERFECT"
elif mx < 7000:  score=4; grade="4/5 ★★★★☆"
elif mx < 8500:  score=3; grade="3/5 ★★★☆☆"
elif mx < 10000: score=2; grade="2/5 ★★☆☆☆"
elif mx < 11500: score=1; grade="1/5 ★☆☆☆☆"
else:            score=0; grade="0/5 ☆☆☆☆☆ FAIL"

print(f"  {BOLD}Score: {grade}{RESET}")
sec_pass = sec_pass and score >= 1
section_result(sec_pass, f"Advanced Version (500 values) — {score}/5")

# ─────────────────────────────────────────────
#  7. Checker Error Management (hard)
# ─────────────────────────────────────────────
header("7. BONUS — Checker Error Management")
sec_pass = True

checker_errors = [
    (["abc"],              "",          "Non-numeric param"),
    (["1", "abc"],         "",          "Non-numeric 2nd arg"),
    (["1", "2", "2"],      "",          "Duplicate"),
    (["-5", "-5"],         "",          "Negative duplicate"),
    (["0", "0"],           "",          "Zero duplicate"),
    (["2147483648"],       "",          "INT_MAX + 1"),
    (["-2147483649"],      "",          "INT_MIN - 1"),
    (["1", "2", "3"],      "rz\n",      "Invalid instruction 'rz'"),
    (["1", "2", "3"],      "SA\n",      "Uppercase instruction"),
    (["1", "2", "3"],      " sa\n",     "Leading space before instruction"),
    (["1", "2", "3"],      "sa \n",     "Trailing space after instruction"),
    (["1", "2", "3"],      "sa  ra\n",  "Two instructions on one line"),
    (["1", "2", "3"],      "\n",        "Empty line as instruction"),
    ([""],                 "",          "Empty string argument"),
]
for args, stdin, desc in checker_errors:
    if args == []:
        if expects_silence([], prog="checker"):
            ok(f"No params: silent")
        else:
            fail(f"No params: expected silence")
            sec_pass = False
        continue
    if expects_error(args, stdin=stdin, prog="checker"):
        ok(desc)
    else:
        fail(f"{desc}: expected Error")
        sec_pass = False

# No params → silent
if expects_silence([], prog="checker"):
    ok("No params: silent")
else:
    fail("No params: expected silence")
    sec_pass = False

section_result(sec_pass, "Checker Error Management")

# ─────────────────────────────────────────────
#  8. Checker False Tests (KO) — hard
# ─────────────────────────────────────────────
header("8. BONUS — Checker False Tests (KO)")
sec_pass = True

# Fixed from correction sheet
out, _, _ = run_checker(["0","9","1","8","2","7","3","6","4","5"], "sa\npb\nrrr\n")
if out == "KO":
    ok("[0 9 1 8 2 7 3 6 4 5] + sa,pb,rrr: KO")
else:
    fail(f"Expected KO, got '{out}'")
    sec_pass = False

# Push everything to b and nothing else → not sorted
for _ in range(15):
    nums = random.sample(range(-100000, 100000), random.choice([3, 5, 10]))
    str_nums = [str(n) for n in nums]
    # pb the top element — leaves stack unsorted unless only 1 element
    if len(nums) > 2:
        out, _, _ = run_checker(str_nums, "pb\n")
        if out == "KO":
            ok(f"{nums}: KO (pb then stop)")
        else:
            fail(f"{nums}: expected KO after pb, got {out}")
            sec_pass = False

# Give deliberately wrong sequence (reverse of what's needed)
for _ in range(10):
    nums = random.sample(range(-100000, 100000), 5)
    str_nums = [str(n) for n in nums]
    # Use a sequence that is unlikely to sort: just rrr many times
    instructions = "rrr\n" * 7
    out, _, _ = run_checker(str_nums, instructions)
    # verify manually
    a = nums[:]; b = []
    for _ in range(7):
        if a: last_a = a.pop(); a.insert(0, last_a)
        if b: last_b = b.pop(); b.insert(0, last_b)
    expected = "OK" if a == sorted(nums) and b == [] else "KO"
    if out == expected:
        ok(f"{nums} + rrr×7: {out}")
    else:
        fail(f"{nums} + rrr×7: expected {expected}, got {out}")
        sec_pass = False

section_result(sec_pass, "Checker False Tests (KO)")

# ─────────────────────────────────────────────
#  9. Checker Right Tests (OK) — hard
# ─────────────────────────────────────────────
header("9. BONUS — Checker Right Tests (OK)")
sec_pass = True

# Fixed from correction sheet
out, _, _ = run_checker(["0","1","2"], "")
if out == "OK": ok("[0 1 2] empty stdin: OK")
else: fail(f"[0 1 2] empty stdin: got '{out}'"); sec_pass = False

out, _, _ = run_checker(["0","9","1","8","2"], "pb\nra\npb\nra\nsa\nra\npa\npa\n")
if out == "OK": ok("[0 9 1 8 2] + pb,ra,pb,ra,sa,ra,pa,pa: OK")
else: fail(f"Expected OK, got '{out}'"); sec_pass = False

# 30 random sizes from 3 to 100
for _ in range(30):
    size = random.choice([3, 5, 10, 20, 50, 100])
    nums = random.sample(range(-100000, 100000), size)
    str_nums = [str(n) for n in nums]
    ps = subprocess.Popen(["./push_swap"] + str_nums,
                          stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    ps_out, _ = ps.communicate()
    ch = subprocess.Popen(["./checker"] + str_nums,
                          stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    ch_out, _ = ch.communicate(input=ps_out)
    ch_out = ch_out.strip()
    moves = len([l for l in ps_out.split('\n') if l.strip()])
    if ch_out == "OK":
        ok(f"{size} values, {moves} moves: OK")
    else:
        fail(f"{size} values: expected OK, got '{ch_out}'")
        sec_pass = False

section_result(sec_pass, "Checker Right Tests (OK)")

# ─────────────────────────────────────────────
#  10. STRESS TEST — 2-value edge cases
# ─────────────────────────────────────────────
header("10. Stress Test — 2-value edge cases")
sec_pass = True

two_value_cases = [
    [0, 1], [1, 0],
    [-1, 0], [0, -1],
    [2147483647, -2147483648],
    [-2147483648, 2147483647],
    [-1, 1], [1, -1],
    [100, 99], [99, 100],
]
for nums in two_value_cases:
    ch_out, moves, _ = pipe_test(nums)
    if ch_out == "OK" and moves <= 1:
        ok(f"{nums}: OK, {moves} moves")
    else:
        fail(f"{nums}: {ch_out}, {moves} moves (need ≤1)")
        sec_pass = False

# 20 random 2-value
for _ in range(20):
    nums = random.sample(range(-100000, 100000), 2)
    ch_out, moves, _ = pipe_test(nums)
    if ch_out == "OK" and moves <= 1:
        ok(f"{nums}: OK, {moves} moves")
    else:
        fail(f"{nums}: {ch_out}, {moves} moves")
        sec_pass = False

section_result(sec_pass, "2-Value Edge Cases")

# ─────────────────────────────────────────────
#  Final
# ─────────────────────────────────────────────
print(f"\n{BOLD}{'═'*60}")
print(f"  FINAL RESULT: {passed_sections}/{total_sections} sections passed")
if passed_sections == total_sections:
    print(f"  {GREEN}🎉 ALL SECTIONS PASSED — READY FOR EVALUATION!{RESET}")
else:
    print(f"  {RED}⚠️  {total_sections - passed_sections} section(s) failed.{RESET}")
print(f"{BOLD}{'═'*60}{RESET}\n")
