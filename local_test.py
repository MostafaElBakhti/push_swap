import subprocess
import random
import sys

OPS = {"sa","sb","ss","pa","pb","ra","rb","rr","rra","rrb","rrr"}

def run_push_swap(numbers):
    arg = " ".join(map(str, numbers))
    p = subprocess.Popen(["./push_swap"] + list(map(str, numbers)), stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    out, err = p.communicate()
    return out.strip().splitlines(), err.strip(), p.returncode

def apply_ops(numbers, ops):
    a = numbers[:]
    b = []
    for op in ops:
        if op == "sa":
            if len(a) >= 2: a[0], a[1] = a[1], a[0]
        elif op == "sb":
            if len(b) >= 2: b[0], b[1] = b[1], b[0]
        elif op == "ss":
            if len(a) >= 2: a[0], a[1] = a[1], a[0]
            if len(b) >= 2: b[0], b[1] = b[1], b[0]
        elif op == "pa":
            if b: a.insert(0, b.pop(0))
        elif op == "pb":
            if a: b.insert(0, a.pop(0))
        elif op == "ra":
            if len(a) >= 1: a.append(a.pop(0))
        elif op == "rb":
            if len(b) >= 1: b.append(b.pop(0))
        elif op == "rr":
            if len(a) >= 1: a.append(a.pop(0))
            if len(b) >= 1: b.append(b.pop(0))
        elif op == "rra":
            if len(a) >= 1: a.insert(0, a.pop())
        elif op == "rrb":
            if len(b) >= 1: b.insert(0, b.pop())
        elif op == "rrr":
            if len(a) >= 1: a.insert(0, a.pop())
            if len(b) >= 1: b.insert(0, b.pop())
        else:
            return False, f"Invalid op: {op}"
    return (a, b), None

def is_sorted(a):
    return all(a[i] <= a[i+1] for i in range(len(a)-1))

def test_random(size, iterations=5, valgrind=False):
    print(f"\n--- Testing size={size}, iterations={iterations}, valgrind={valgrind} ---")
    success = 0
    ops_counts = []
    for i in range(iterations):
        nums = random.sample(range(-100000,100000), size)
        ops, err, rc = run_push_swap(nums)
        if err:
            print(f"Iteration {i+1}: push_swap stderr: {err}")
            continue
        if rc != 0 and rc is not None:
            print(f"Iteration {i+1}: push_swap returned code {rc}")
        if any(op not in OPS for op in ops):
            bad = [op for op in ops if op not in OPS]
            print(f"Iteration {i+1}: Invalid operations from push_swap: {bad}")
            continue
        (a,b), op_err = apply_ops(nums, ops)
        if op_err:
            print(f"Iteration {i+1}: {op_err}")
            continue
        if is_sorted(a) and len(b) == 0:
            success += 1
            ops_counts.append(len(ops))
            print(f"Iteration {i+1}: OK - {len(ops)} ops")
            # run valgrind on first successful iteration if requested
            if valgrind and i == 0:
                try:
                    print("Running valgrind for leak check on this iteration...")
                    vg = subprocess.Popen(["valgrind","--leak-check=full","--error-exitcode=1","./push_swap"] + list(map(str, nums)), stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
                    vout, verr = vg.communicate(timeout=120)
                    print("Valgrind stderr (summary):")
                    print('\n'.join(verr.strip().splitlines()[-20:]))
                except Exception as e:
                    print(f"Valgrind run failed: {e}")
        else:
            print(f"Iteration {i+1}: KO - Not sorted or b not empty (b size={len(b)})")
    if ops_counts:
        print(f"Success: {success}/{iterations}, avg ops: {sum(ops_counts)/len(ops_counts):.2f}, max ops: {max(ops_counts)}")
    else:
        print(f"Success: {success}/{iterations}")

if __name__ == '__main__':
    # small identity tests
    print("Running basic error/identity checks")
    # Error tests
    tests = ["abc","1 1","2147483648","-2147483649"]
    for t in tests:
        p = subprocess.Popen(["./push_swap"] + t.split(), stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
        out, err = p.communicate()
        print(f"Args='{t}' -> stdout:'{out.strip()}', stderr:'{err.strip()}'")

    # identity
    for t in [[42],[2,3],[0,1,2,3]]:
        p = subprocess.Popen(["./push_swap"] + list(map(str,t)), stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
        out, err = p.communicate()
        print(f"Identity {t} -> ops: {len(out.strip().splitlines()) if out.strip() else 0}")

    # performance tests
    test_random(3, iterations=3)
    test_random(5, iterations=3)
    test_random(100, iterations=5)
    test_random(500, iterations=3, valgrind=True)
