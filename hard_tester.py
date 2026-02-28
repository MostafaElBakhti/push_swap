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
def header(msg): print(f"\n{BOLD}{CYAN}{'═'*70}\n  {msg}\n{'═'*70}{RESET}")

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
#  1. Error Management — push_swap (Extensive)
# ─────────────────────────────────────────────
header("1. Error Management — push_swap (Extensive Mode)")
sec_pass = True

error_cases = [
    (["abc"],                    "Non-numeric single"),
    (["1", "abc", "3"],          "Non-numeric in middle"),
    (["1", "2", "abc"],          "Non-numeric at end"),
    (["a1"],                     "Mixed alpha-digits"),
    (["1a"],                     "Digits-alpha"),
    (["1.5"],                    "Float number"),
    (["1", "2", "2"],            "Duplicate (simple)"),
    (["3", "3", "3"],            "All same"),
    (["-1", "-1"],               "Negative duplicates"),
    (["0", "1", "0"],            "Zero duplicate"),
    (["+1", "1"],                "+1 and 1 as duplicate"),
    (["-0", "0"],                "-0 and 0 as duplicate"),
    (["2147483648"],             "INT_MAX + 1"),
    (["-2147483649"],            "INT_MIN - 1"),
    (["99999999999"],            "Large overflow"),
    (["-99999999999"],           "Large underflow"),
    (["1", "2147483648", "3"],   "Overflow in middle"),
    (["", "1", "2"],             "Empty string arg"),
    (["1 2 2"],                  "Duplicate inside quoted arg"),
    (["1", "1 2 3 3"],           "Dup inside multiarg quote"),
    (["1-2"],                    "Minus in middle of number"),
    (["+1+2"],                   "Plus in middle of number"),
    ([" "],                      "Single space arg"),
    ([" 1 2 a"],                 "Alpha with spaces"),
    (["--1"],                    "Double minus"),
    (["++1"],                    "Double plus"),
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

# Identical values string format
if expects_error(["1", " 1 "]):
    ok("1 and ' 1 ': Error")
else:
    fail("1 and ' 1 ': expected Error")
    sec_pass = False

section_result(sec_pass, "Error Management (push_swap)")

# ─────────────────────────────────────────────
#  2. Identity Tests (already sorted - Stress)
# ─────────────────────────────────────────────
header("2. Identity Tests — already sorted (50 tests)")
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
        pass
    else:
        fail(f"{desc}: expected 0, got {moves}")
        sec_pass = False

# 50 random already-sorted
success_count = 0
for _ in range(50):
    n = random.randint(2, 500)
    lst = sorted(random.sample(range(-2000000, 2000000), n))
    out, _, _ = run_ps(*[str(x) for x in lst])
    moves = len([l for l in out.split('\n') if l.strip()])
    if moves == 0:
        success_count += 1
    else:
        fail(f"Random sorted {n} values: got {moves}")
        sec_pass = False

if success_count == 50:
    ok(f"Passed all fixed and {success_count} random sorted tests")

section_result(sec_pass, "Identity Tests")

# ─────────────────────────────────────────────
#  3. Simple Version — 3 values (100 tests)
# ─────────────────────────────────────────────
header("3. Simple Version — 3 values (max 3 moves, 100 tests)")
sec_pass = True

perms = [[0,1,2],[0,2,1],[1,0,2],[1,2,0],[2,0,1],[2,1,0]]
for p in perms:
    ch_out, moves, _ = pipe_test(p)
    if not (ch_out == "OK" and moves <= 3):
        fail(f"{p}: {ch_out}, {moves} moves (need ≤3)")
        sec_pass = False

success_count = 0
for _ in range(100):
    nums = random.sample(range(-100000, 100000), 3)
    ch_out, moves, _ = pipe_test(nums)
    if ch_out == "OK" and moves <= 3:
        success_count += 1
    else:
        fail(f"{nums}: {ch_out}, {moves} moves")
        sec_pass = False

if success_count == 100:
    ok("Passed 100 random 3-value tests and all permutations")
section_result(sec_pass, "Simple Version (3 values, ≤3 moves)")

# ─────────────────────────────────────────────
#  4. Another Simple — 5 values (100 tests)
# ─────────────────────────────────────────────
header("4. Another Simple — 5 values (max 12 moves, 100 tests)")
sec_pass = True
kudos_count = 0
all_moves = []

for _ in range(100):
    nums = random.sample(range(-100000, 100000), 5)
    ch_out, moves, _ = pipe_test(nums)
    all_moves.append(moves)
    if moves <= 8: kudos_count += 1
    if ch_out != "OK" or moves > 12:
        fail(f"{nums}: {ch_out}, {moves} moves (need ≤12)")
        sec_pass = False

if sec_pass:
    ok(f"Passed 100 random 5-value tests. Max moves used: {max(all_moves)}")
    info(f"KUDOS achieved on {kudos_count}/100 tests (≤8 moves)")

section_result(sec_pass, "Simple Version (5 values, ≤12)")

# ─────────────────────────────────────────────
#  5. Middle Version — 100 values (100 tests)
# ─────────────────────────────────────────────
header("5. Middle Version — 100 values (100 tests, rated 0-5)")
sec_pass = True
all_moves = []
errs = 0

for i in range(100):
    nums = random.sample(range(-500000, 500000), 100)
    ch_out, moves, elapsed = pipe_test(nums)
    if ch_out == "OK":
        all_moves.append(moves)
    else:
        fail(f"Test {i+1}: checker={ch_out}, {moves} moves")
        sec_pass = False
        errs += 1

if errs == 0:
    avg, mx, mn = sum(all_moves)//len(all_moves), max(all_moves), min(all_moves)
    ok(f"Passed 100 tests!")
    info(f"Average: {avg} | Min: {mn} | Max: {mx}")
    
    if   mx < 700:  score=5; grade="5/5 ★★★★★ PERFECT"
    elif mx < 900:  score=4; grade="4/5 ★★★★☆"
    elif mx < 1100: score=3; grade="3/5 ★★★☆☆"
    elif mx < 1300: score=2; grade="2/5 ★★☆☆☆"
    elif mx < 1500: score=1; grade="1/5 ★☆☆☆☆"
    else:           score=0; grade="0/5 ☆☆☆☆☆ FAIL"
    
    print(f"  {BOLD}Score: {grade}{RESET}")
    sec_pass = sec_pass and score >= 1
else:
    score = 0
section_result(sec_pass, f"Middle Version (100 values) — {score}/5")

# ─────────────────────────────────────────────
#  6. Advanced Version — 500 values (100 tests)
# ─────────────────────────────────────────────
header("6. Advanced Version — 500 values (100 tests, rated 0-5)")
sec_pass = True
all_moves = []
errs = 0

print("  Running 100 tests... (this might take a few seconds)")
for i in range(100):
    nums = random.sample(range(-2000000, 2000000), 500)
    ch_out, moves, elapsed = pipe_test(nums)
    if ch_out == "OK":
        all_moves.append(moves)
        if (i+1) % 10 == 0:
            sys.stdout.write(f"\r  {CYAN}Progress: {i+1}/100{RESET}")
            sys.stdout.flush()
    else:
        fail(f"Test {i+1}: checker={ch_out}, {moves} moves")
        sec_pass = False
        errs += 1

print("\n")

if errs == 0:
    avg, mx, mn = sum(all_moves)//len(all_moves), max(all_moves), min(all_moves)
    ok(f"Passed 100 tests!")
    info(f"Average: {avg} | Min: {mn} | Max: {mx}")
    
    if   mx < 5500:  score=5; grade="5/5 ★★★★★ PERFECT"
    elif mx < 7000:  score=4; grade="4/5 ★★★★☆"
    elif mx < 8500:  score=3; grade="3/5 ★★★☆☆"
    elif mx < 10000: score=2; grade="2/5 ★★☆☆☆"
    elif mx < 11500: score=1; grade="1/5 ★☆☆☆☆"
    else:            score=0; grade="0/5 ☆☆☆☆☆ FAIL"
    
    print(f"  {BOLD}Score: {grade}{RESET}")
    sec_pass = sec_pass and score >= 1
else:
    score = 0
section_result(sec_pass, f"Advanced Version (500 values) — {score}/5")

# ─────────────────────────────────────────────
#  7. Checker Error Management (Extensive)
# ─────────────────────────────────────────────
header("7. BONUS — Checker Error Management (Extensive)")
sec_pass = True

checker_errors = [
    (["abc"],              "",          "Non-numeric param"),
    (["1", "abc"],         "",          "Non-numeric 2nd arg"),
    (["1", "2", "2"],      "",          "Duplicate"),
    (["-5", "-5"],         "",          "Negative duplicate"),
    (["0", "0"],           "",          "Zero duplicate"),
    (["1"],                "xyz\n",     "Non-existent instruction"),
    (["1"],                " sa\n",     "Space before sa"),
    (["1"],                "sa \n",     "Space after sa"),
    (["1"],                "sa\n \n",   "Space instruction"),
    (["1"],                "SA\n",      "Uppercase SA"),
    (["1"],                "sa  pb\n",  "Double instruction"),
    ([""],                 "",          "Empty string arg"),
]

for args, stdin, desc in checker_errors:
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
#  8. Checker False Tests (KO) — 50 tests
# ─────────────────────────────────────────────
header("8. BONUS — Checker False Tests (KO, 50 tests)")
sec_pass = True

# Fixed from correction sheet
out, _, _ = run_checker(["0","9","1","8","2","7","3","6","4","5"], "sa\npb\nrrr\n")
if out == "KO":
    ok("[0 9...5] + sa,pb,rrr: KO")
else:
    fail(f"Expected KO, got '{out}'")
    sec_pass = False

success_count = 0
for _ in range(50):
    nums = random.sample(range(-100000, 100000), random.choice([3, 5, 10, 50, 100]))
    str_nums = [str(n) for n in nums]
    
    # 50% pb, 50% random reversed instructions
    if random.choice([True, False]):
        out, _, _ = run_checker(str_nums, "pb\n")
        if out == "KO": success_count += 1
        else: fail(f"{nums}: expected KO after pb, got {out}"); sec_pass = False
    else:
        out, _, _ = run_checker(str_nums, "rrr\n"*10)
        # Check manually if sorted (extremely unlikely with random and just rrr)
        if out == "KO": success_count += 1
        elif out == "OK": info("Rare OK with just rrrr (probably luck), ignoring")
        else: fail(f"Expected KO, got: {out}"); sec_pass = False

if success_count == 50:
    ok("Passed 50 false sequence tests")
section_result(sec_pass, "Checker False Tests (KO)")

# ─────────────────────────────────────────────
#  9. Checker Right Tests (OK) — 100 tests
# ─────────────────────────────────────────────
header("9. BONUS — Checker Right Tests (OK, 100 tests)")
sec_pass = True

out, _, _ = run_checker(["0","1","2"], "")
if out == "OK": ok("[0 1 2] empty stdin: OK")
else: fail(f"[0 1 2] empty stdin: got '{out}'"); sec_pass = False

out, _, _ = run_checker(["0","9","1","8","2"], "pb\nra\npb\nra\nsa\nra\npa\npa\n")
if out == "OK": ok("[0 9 1 8 2] + valid manual sequence: OK")
else: fail(f"Expected OK, got '{out}'"); sec_pass = False

success_count = 0
for _ in range(100):
    size = random.choice([3, 5, 10, 20, 50, 100, 200, 500])
    nums = random.sample(range(-1000000, 1000000), size)
    str_nums = [str(n) for n in nums]
    ps = subprocess.Popen(["./push_swap"] + str_nums,
                          stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    ps_out, _ = ps.communicate()
    ch = subprocess.Popen(["./checker"] + str_nums,
                          stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    ch_out, _ = ch.communicate(input=ps_out)
    ch_out = ch_out.strip()
    if ch_out == "OK":
        success_count += 1
    else:
        fail(f"{size} values: expected OK, got '{ch_out}'")
        sec_pass = False

if success_count == 100:
    ok("Passed 100 valid sort checks with checker")
section_result(sec_pass, "Checker Right Tests (OK)")

# ─────────────────────────────────────────────
#  Final
# ─────────────────────────────────────────────
print(f"\n{BOLD}{'═'*70}")
print(f"  HARD TESTER FINAL RESULT: {passed_sections}/{total_sections} sections passed")
if passed_sections == total_sections:
    print(f"  {GREEN}🎉 ALL MASTER SECTIONS PASSED — READY FOR FLAWLESS EVALUATION!{RESET}")
else:
    print(f"  {RED}⚠️  {total_sections - passed_sections} section(s) failed.{RESET}")
print(f"{BOLD}{'═'*70}{RESET}\n")

