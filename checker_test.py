import subprocess
import random
import sys

GREEN  = '\033[92m'
RED    = '\033[91m'
YELLOW = '\033[93m'
CYAN   = '\033[96m'
BOLD   = '\033[1m'
RESET  = '\033[0m'

def test_checker(size, num_tests):
    print(f"\n{BOLD}{CYAN}--- Testing {size} values ({num_tests} tests) ---{RESET}")
    passed = 0
    leaks = 0

    for i in range(num_tests):
        nums = random.sample(range(-1000000, 1000000), size)
        str_nums = [str(n) for n in nums]
        
        # Run push_swap
        ps = subprocess.Popen(["./push_swap"] + str_nums, stdout=subprocess.PIPE, text=True)
        ps_out, _ = ps.communicate()
        
        # Run checker with valgrind
        valgrind_cmd = ["valgrind", "--leak-check=full", "--show-leak-kinds=all", "--error-exitcode=42", "./checker"] + str_nums
        ch = subprocess.Popen(valgrind_cmd, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
        ch_out, ch_err = ch.communicate(input=ps_out)
        
        ch_out = ch_out.strip()
        
        has_leak = (ch.returncode == 42) or ("definitely lost:" in ch_err and " 0 bytes in 0 blocks" not in ch_err)

        if ch_out == "OK" and not has_leak:
            passed += 1
            if (i+1) % 10 == 0 or num_tests < 20:
                print(f"  Test {i+1}: {GREEN}OK{RESET} (No leaks)")
        else:
            print(f"  Test {i+1}: ", end="")
            if ch_out != "OK":
                print(f"{RED}FAILED{RESET} (Got {ch_out}) ", end="")
            else:
                print(f"{GREEN}OK{RESET} ", end="")
                
            if has_leak:
                leaks += 1
                print(f"{RED}[LEAK DETECTED]{RESET}")
            else:
                print(f"{GREEN}[No leaks]{RESET}")

    print(f"{BOLD}Results for size {size}:{RESET}")
    print(f"  Passed correctness: {passed}/{num_tests}")
    if leaks == 0:
         print(f"  Leaks failed:       {GREEN}{leaks}/{num_tests}{RESET}")
    else:
         print(f"  Leaks failed:       {RED}{leaks}/{num_tests}{RESET}")

def main():
    print(f"{BOLD}HARD TESTER FOR ./checker WITH VALGRIND{RESET}\n")
    test_checker(3, 10)
    test_checker(5, 10)
    test_checker(100, 20)
    test_checker(500, 20)
    
if __name__ == "__main__":
    main()
