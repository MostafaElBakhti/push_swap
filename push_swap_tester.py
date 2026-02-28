#!/usr/bin/env python3
"""
push_swap_tester.py

Usage: python push_swap_tester.py [--sizes 3 5 100] [--iterations 10]

Generates random tests, runs `push_swap` to get operations, feeds them to `checker`,
counts operations, and prints a summary (avg/max/min). Works on Windows and Unix.
"""
import argparse
import subprocess
import random
import shutil
import platform
import os
import csv
import sys
from datetime import datetime


def find_executable(base):
    # Try local and bonus paths, prefer exact files when present
    cand = []
    if platform.system() == "Windows":
        cand.extend([f"{base}.exe", os.path.join("bonus", f"{base}.exe"), base, os.path.join("bonus", base)])
    else:
        # prefer local built binary or bonus/checker
        cand.extend([os.path.join(".", base), os.path.join("bonus", base)])
    for p in cand:
        if shutil.which(p) or os.path.exists(p):
            return p
    # fall back to base name and rely on PATH
    return base


def run_program(cmd_list, input_text=None, timeout=10):
    try:
        proc = subprocess.run(cmd_list, input=input_text, text=True, capture_output=True, timeout=timeout)
        return proc.stdout, proc.stderr, proc.returncode
    except subprocess.TimeoutExpired:
        return "", "TIMEOUT", -1


def gen_numbers(n, min_v, max_v, allow_duplicates=False):
    if allow_duplicates:
        return [random.randint(min_v, max_v) for _ in range(n)]
    else:
        # sample requires range length >= n
        rng = max_v - min_v + 1
        if rng < n:
            raise ValueError("Range too small for unique numbers")
        return random.sample(range(min_v, max_v + 1), n)


def count_ops(ops_text):
    if not ops_text:
        return 0
    return sum(1 for line in ops_text.splitlines() if line.strip())


def single_test(push_exe, checker_exe, numbers, timeout_per_test):
    args = list(map(str, numbers))
    # run push_swap
    ps_cmd = [push_exe] + args
    ps_out, ps_err, ps_rc = run_program(ps_cmd, timeout=timeout_per_test)
    if ps_rc != 0 and ps_err.strip():
        return {'result': 'PS_ERROR', 'ops': ps_out, 'stderr': ps_err.strip(), 'ops_count': None}
    ops_count = count_ops(ps_out)
    # run checker feeding operations via stdin
    chk_cmd = [checker_exe] + args
    chk_out, chk_err, chk_rc = run_program(chk_cmd, input_text=ps_out, timeout=timeout_per_test)
    chk_combined = (chk_out or "") + (chk_err or "")
    result = chk_out.strip() if chk_out.strip() else (chk_err.strip() or ("TIMEOUT" if chk_rc == -1 else str(chk_rc)))
    return {'result': result, 'ops': ps_out, 'stderr': ps_err.strip() if ps_err else '', 'ops_count': ops_count, 'checker_out': chk_out.strip(), 'checker_err': chk_err.strip()}


def run_batch(sizes, iterations, min_v, max_v, timeout_per_test, seed, out_csv=None, allow_duplicates=False):
    random.seed(seed)
    push_exe = find_executable('push_swap')
    checker_exe = find_executable('checker')
    print(f"Using push_swap: {push_exe}")
    print(f"Using checker: {checker_exe}")

    rows = []
    for size in sizes:
        print(f"\nSize {size}: running {iterations} iterations")
        stats = []
        for i in range(1, iterations + 1):
            nums = gen_numbers(size, min_v, max_v, allow_duplicates=allow_duplicates)
            res = single_test(push_exe, checker_exe, nums, timeout_per_test)
            ok = (res['checker_out'] == 'OK') if 'checker_out' in res else False
            status = 'OK' if ok else (res['result'] or 'FAIL')
            ops = res['ops_count'] if res['ops_count'] is not None else 0
            stats.append(ops)
            rows.append({'size': size, 'iteration': i, 'ops': ops, 'status': status, 'numbers': ' '.join(map(str, nums)), 'push_stderr': res.get('stderr',''), 'checker_out': res.get('checker_out',''), 'checker_err': res.get('checker_err','')})
            print(f"  iter {i}: {ops} ops - {status}")
        if stats:
            print(f"Summary size {size}: avg={sum(stats)/len(stats):.2f}, max={max(stats)}, min={min(stats)}")
    if out_csv:
        with open(out_csv, 'w', newline='', encoding='utf-8') as f:
            writer = csv.DictWriter(f, fieldnames=list(rows[0].keys()) if rows else ['size','iteration','ops','status','numbers'])
            writer.writeheader()
            writer.writerows(rows)
        print(f"Results written to {out_csv}")
    return rows


def parse_args():
    p = argparse.ArgumentParser(description='Test push_swap and count moves')
    p.add_argument('--sizes', nargs='+', type=int, default=[3,5,100], help='Sizes to test')
    p.add_argument('--iterations', type=int, default=10, help='Iterations per size')
    p.add_argument('--min', type=int, default=-10000, dest='min_v', help='Minimum random value')
    p.add_argument('--max', type=int, default=10000, dest='max_v', help='Maximum random value')
    p.add_argument('--timeout', type=int, default=5, help='Timeout per test in seconds')
    p.add_argument('--seed', type=int, default=int(datetime.now().timestamp()), help='Random seed')
    p.add_argument('--out', type=str, default=None, help='CSV output path')
    p.add_argument('--allow-duplicates', action='store_true', help='Allow duplicate numbers in generated tests')
    return p.parse_args()


if __name__ == '__main__':
    args = parse_args()
    try:
        run_batch(args.sizes, args.iterations, args.min_v, args.max_v, args.timeout, args.seed, out_csv=args.out, allow_duplicates=args.allow_duplicates)
    except Exception as e:
        print("Error:", e)
        sys.exit(1)
