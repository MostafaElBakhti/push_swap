import subprocess
import random
import sys

def colored_print(text, color):
    colors = {
        'green': '\033[92m',
        'yellow': '\033[93m',
        'red': '\033[91m',
        'reset': '\033[0m'
    }
    print(f"{colors.get(color, '')}{text}{colors['reset']}")

def run_tests(size, num_tests):
    print(f"==================================================")
    print(f"  Running {num_tests} tests for {size} values")
    print(f"==================================================")
    
    total_moves = 0
    max_moves = 0
    min_moves = float('inf')
    
    for i in range(num_tests):
        # Generate random unique integers
        numbers = random.sample(range(-100000, 100000), size)
        str_numbers = [str(num) for num in numbers]
        
        try:
            # Run push_swap and count lines of output
            process = subprocess.Popen(
                ["./push_swap"] + str_numbers,
                stdout=subprocess.PIPE,
                stderr=subprocess.PIPE,
                text=True
            )
            out, err = process.communicate()
            
            if process.returncode != 0:
                colored_print(f"Test {i+1} failed with error/segfault.", 'red')
                if err:
                    print(err.strip())
                continue
                
            # Count moves (each line is a move)
            moves = len([line for line in out.split('\n') if line.strip()])
            
            total_moves += moves
            if moves > max_moves: max_moves = moves
            if moves < min_moves: min_moves = moves
            
            # Print status with colors based on common 42 benchmarks
            status_color = 'green'
            if size == 100 and moves > 700: status_color = 'red'
            elif size == 100 and moves > 600: status_color = 'yellow'
            if size == 500 and moves > 5500: status_color = 'red'
            elif size == 500 and moves > 4600: status_color = 'yellow'
            
            colored_print(f"Test {i+1:2d}: {moves} moves", status_color)
            
        except FileNotFoundError:
            colored_print("Error: ./push_swap not found. Please compile your project first (e.g., run 'make').", 'red')
            sys.exit(1)

    if num_tests > 0:
        avg_moves = total_moves // num_tests
        print(f"--------------------------------------------------")
        print(f"Summary for {size} values:")
        print(f"Average: {avg_moves} moves")
        print(f"Maximum: {max_moves} moves")
        print(f"Minimum: {min_moves} moves")
        print(f"==================================================\n")

if __name__ == "__main__":
    run_tests(100, 20)
    run_tests(500, 20)
