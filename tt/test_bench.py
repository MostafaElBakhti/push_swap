import subprocess, random

print('=== 100 numbers (limit: 700 ops) ===')
fails = 0
total = 0
for _ in range(100):
    nums = random.sample(range(-500, 500), 100)
    r = subprocess.run(['./push_swap'] + list(map(str, nums)), capture_output=True, text=True)
    ops = len(r.stdout.strip().splitlines()) if r.stdout.strip() else 0
    total += ops
    if ops > 700:
        fails += 1
        print(f'  FAIL: {ops} ops')
print(f'Passed: {100-fails}/100  |  Avg: {total//100} ops  |  Max target: 700')

print()
print('=== 500 numbers (limit: 5500 ops) ===')
fails = 0
total = 0
for _ in range(50):
    nums = random.sample(range(-1000, 1000), 500)
    r = subprocess.run(['./push_swap'] + list(map(str, nums)), capture_output=True, text=True)
    ops = len(r.stdout.strip().splitlines()) if r.stdout.strip() else 0
    total += ops
    if ops > 5500:
        fails += 1
        print(f'  FAIL: {ops} ops')
print(f'Passed: {50-fails}/50  |  Avg: {total//50} ops  |  Max target: 5500')

print()
print('=== Correctness check (10 random 100-num inputs) ===')
for _ in range(10):
    nums = random.sample(range(-500, 500), 100)
    r = subprocess.run(['./push_swap'] + list(map(str, nums)), capture_output=True, text=True)
    ops_list = r.stdout.strip().splitlines()
    # simulate the operations manually
    a = list(nums)
    b = []
    ok = True
    for op in ops_list:
        op = op.strip()
        try:
            if op == 'sa': a[0], a[1] = a[1], a[0]
            elif op == 'sb': b[0], b[1] = b[1], b[0]
            elif op == 'ss':
                a[0], a[1] = a[1], a[0]
                b[0], b[1] = b[1], b[0]
            elif op == 'pa': a.insert(0, b.pop(0))
            elif op == 'pb': b.insert(0, a.pop(0))
            elif op == 'ra': a.append(a.pop(0))
            elif op == 'rb': b.append(b.pop(0))
            elif op == 'rr':
                a.append(a.pop(0))
                b.append(b.pop(0))
            elif op == 'rra': a.insert(0, a.pop())
            elif op == 'rrb': b.insert(0, b.pop())
            elif op == 'rrr':
                a.insert(0, a.pop())
                b.insert(0, b.pop())
        except Exception as e:
            print(f'  ERROR simulating op {op}: {e}')
            ok = False
            break
    if ok:
        sorted_a = sorted(nums)
        if a == sorted_a and len(b) == 0:
            print(f'  OK - {len(ops_list)} ops')
        else:
            print(f'  WRONG SORT! a={a[:5]}... expected={sorted_a[:5]}...')
