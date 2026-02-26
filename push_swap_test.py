import subprocess
import random
import sys

def run_command(cmd, input_data=None):
    process = subprocess.Popen(cmd, shell=True, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    stdout, stderr = process.communicate(input=input_data)
    return stdout, stderr, process.returncode

def test_push_swap(numbers):
    arg = " ".join(map(str, numbers))
    ps_stdout, ps_stderr, ps_ret = run_command(f"./push_swap {arg}")
    
    if ps_stderr:
        print(f"Push_swap stderr: {ps_stderr.strip()}")
        return None, ps_stderr.strip()
    
    op_count = len(ps_stdout.strip().split("\n")) if ps_stdout.strip() else 0
    
    # Check with our checker
    checker_stdout, checker_stderr, checker_ret = run_command(f"./checker {arg}", input_data=ps_stdout)
    
    return op_count, checker_stdout.strip()

def run_performance_test(size, goal, iterations=10):
    print(f"\n--- Performance Test: {size} random values (Goal: < {goal}) ---")
    counts = []
    for i in range(iterations):
        numbers = random.sample(range(-10000, 10000), size)
        count, result = test_push_swap(numbers)
        if result == "OK":
            counts.append(count)
            print(f"Iteration {i+1}: {count} operations - OK")
        else:
            print(f"Iteration {i+1}: FAILED (Result: {result})")
    
    if counts:
        avg = sum(counts) / len(counts)
        max_c = max(counts)
        print(f"Average: {avg:.2f}, Max: {max_c}")
    else:
        print("No successful iterations.")

def test_errors():
    print("\n--- Error Management Tests ---")
    tests = [
        ("abc", "Error", "Non-numeric"),
        ("1 2 1", "Error", "Duplicates"),
        ("2147483648", "Error", "Greater than INT_MAX"),
        ("-2147483649", "Error", "Less than INT_MIN"),
        ("", "", "Empty parameter")
    ]
    for arg, expected, desc in tests:
        stdout, stderr, ret = run_command(f"./push_swap {arg}")
        if expected == "Error":
             # Subject says "The program must display \"Error\"". Usually this goes to stderr.
             # In previous logs, write(2, "Error\n", 6) was seen.
            actual = (stdout + stderr).strip()
            if actual == "Error":
                print(f"PASS: {desc}")
            else:
                print(f"FAIL: {desc} (Expected Error, got '{actual}')")
        elif expected == "":
            actual = (stdout + stderr).strip()
            if actual == "":
                print(f"PASS: {desc}")
            else:
                print(f"FAIL: {desc} (Expected empty, got '{actual}')")

def test_identity():
    print("\n--- Identity Tests (Sorted) ---")
    tests = [
        ("42", ""),
        ("2 3", ""),
        ("0 1 2 3", "")
    ]
    for arg, expected in tests:
        stdout, stderr, ret = run_command(f"./push_swap {arg}")
        actual = (stdout + stderr).strip()
        if actual == "":
            print(f"PASS: {arg}")
        else:
            print(f"FAIL: {arg} (Got '{actual}')")

if __name__ == "__main__":
    test_errors()
    test_identity()
    run_performance_test(3, 3)
    run_performance_test(5, 12)
    run_performance_test(100, 700)
    run_performance_test(500, 5500)
