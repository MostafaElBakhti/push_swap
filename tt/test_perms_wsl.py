import itertools
import subprocess

def run_tests(n):
    nums = list(range(1, n+1))
    bad = []
    total = 0
    for p in itertools.permutations(nums):
        total += 1
        args = ' '.join(map(str, p))
        cmd = f"./push_swap {args} | ./checker {args}"
        proc = subprocess.run(cmd, shell=True, capture_output=True, text=True)
        out = (proc.stdout + proc.stderr).strip()
        if 'KO' in out or proc.returncode != 0:
            bad.append((p, out))
    return total, bad

if __name__ == '__main__':
    for n in (4, 5):
        total, bad = run_tests(n)
        print(f"RESULT n={n}: total={total} failed={len(bad)}")
        for p, out in bad:
            print('FAILED', p, (out[:200].replace('\n', '\\n') if out else '<no output>'))
