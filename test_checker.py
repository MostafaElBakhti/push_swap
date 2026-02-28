import subprocess
import random
import sys

def test_checker(size, num_tests):
    print(f"==================================================")
    print(f"  Running {num_tests} tests for checker with {size} values")
    print(f"==================================================")
    
    passed = 0
    failed = 0
    
    # Try to find checker executable name
    checker_exec = "./checker"
    if sys.platform == "win32":
        checker_exec = "checker.exe"
        
    push_swap_exec = "./push_swap"
    if sys.platform == "win32":
        push_swap_exec = "push_swap.exe"
    
    for i in range(num_tests):
        numbers = random.sample(range(-100000, 100000), size)
        str_numbers = [str(num) for num in numbers]
        
        try:
            # First, run push_swap to get the instructions
            ps_process = subprocess.Popen(
                [push_swap_exec] + str_numbers,
                stdout=subprocess.PIPE,
                stderr=subprocess.PIPE,
                text=True
            )
            ps_out, ps_err = ps_process.communicate()
            
            if ps_process.returncode != 0:
                print(f"\033[91mTest {i+1}: push_swap crashed or returned error.\033[0m")
                failed += 1
                continue
                
            # Then, run checker and feed the output of push_swap into its stdin
            ch_process = subprocess.Popen(
                [checker_exec] + str_numbers,
                stdin=subprocess.PIPE,
                stdout=subprocess.PIPE,
                stderr=subprocess.PIPE,
                text=True
            )
            ch_out, ch_err = ch_process.communicate(input=ps_out)
            
            output = ch_out.strip()
            if output == "OK":
                print(f"\033[92mTest {i+1:2d}: [OK]\033[0m")
                passed += 1
            else:
                # Provide some context if it fails
                print(f"\033[91mTest {i+1:2d}: [{output if output else 'NO OUTPUT/KO'}]\033[0m")
                failed += 1
                
        except FileNotFoundError as e:
            # Fallback for Windows/WSL naming differences
            if checker_exec == "checker.exe":
                checker_exec = "./checker"
                push_swap_exec = "./push_swap"
                continue # Retry
            else:
                print(f"\033[91mError: Executable not found. Make sure {push_swap_exec} and {checker_exec} are compiled.\033[0m")
                sys.exit(1)

    print(f"--------------------------------------------------")
    print(f"Summary for checker ({size} values):")
    print(f"\033[92mPassed: {passed}/{num_tests}\033[0m")
    if failed > 0:
        print(f"\033[91mFailed: {failed}/{num_tests}\033[0m")
    else:
        print(f"Failed: {failed}/{num_tests}")
    print(f"==================================================\n")

if __name__ == "__main__":
    test_checker(100, 20)
    test_checker(500, 20)
