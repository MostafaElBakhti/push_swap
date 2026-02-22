# Push Swap — Turkish Algorithm Explained

## Overview

Push Swap sorts a stack using only two stacks (**A** and **B**) and a limited set of operations.
The **Turkish (Turk) algorithm** is a greedy approach that works in 5 phases:

1. **Index** — normalize values to indices
2. **Push to B** — move elements to B smartly
3. **Sort 3** — sort the remaining 3 in A
4. **Greedy push-back** — push B back to A one by one at minimum cost
5. **Shift** — rotate A so the minimum is on top

---

## Example

```
A = [56, 5478, -56, 1, 36, 78]   (top → bottom)
B = []
```

### Initial State

```
     Stack A              Stack B
  ┌────────────┐       ┌────────────┐
  │   56  [?]  │ ← top │   empty    │
  │ 5478  [?]  │       └────────────┘
  │  -56  [?]  │
  │    1  [?]  │
  │   36  [?]  │
  │   78  [?]  │
  └────────────┘
```

*(indices assigned in Phase 1)*

---

## Phase 1 — Indexing

### Function: `ft_index_stack(&a)`

Instead of working with raw values, we assign each element a **rank index**
(0 = smallest, n−1 = largest). This allows simple integer comparisons throughout the algorithm.

**How it works internally:**
1. `copy_stack_to_array` — copies values into a temp array
2. `sort_array` — bubble-sorts the temp array ascending
3. `assign_index` — for each node, its `index` = its position in the sorted array

**Sorted values → indices:**

| index | value |
|-------|-------|
| 0     | -56   |
| 1     | 1     |
| 2     | 36    |
| 3     | 56    |
| 4     | 78    |
| 5     | 5478  |

**Stack A after indexing (top → bottom):**

| value | index |
|-------|-------|
| 56    | 3     |
| 5478  | 5     |
| -56   | 0     |
| 1     | 1     |
| 36    | 2     |
| 78    | 4     |

Variables set: `size = 6`, `mid = 3`

### Stack A after indexing

```
     Stack A              Stack B
  ┌────────────┐       ┌────────────┐
  │   56  [3]  │ ← top │   empty    │
  │ 5478  [5]  │       └────────────┘
  │  -56  [0]  │
  │    1  [1]  │
  │   36  [2]  │
  │   78  [4]  │
  └────────────┘
```

---

## Phase 2 — Push to B

### Functions: `pb`, `rb` (inside `sort_turk`)

We push elements from A to B until **only 3 remain** in A.

The trick: if the pushed element's index is `< mid` (it's a **small** element),
we call `rb` to sink it to the **bottom** of B.
This keeps **large elements** near the top of B — cheaper to push back to A later.

```c
while (stack_size(A) > 3) {
    pb(a, b);
    if (b->top->index < mid)
        rb(b);
}
```

**Step by step:**

**Step 1 — `pb` (push 56 from A to B)**

> 56 has index 3 → index 3 ≥ mid(3) → **no `rb`** → stays on top of B

```
     Stack A              Stack B
  ┌────────────┐       ┌────────────┐
  │ 5478  [5]  │ ← top │   56  [3]  │ ← top
  │  -56  [0]  │       └────────────┘
  │    1  [1]  │
  │   36  [2]  │
  │   78  [4]  │
  └────────────┘
```

**Step 2 — `pb` (push 5478 from A to B)**

> 5478 has index 5 → index 5 ≥ mid(3) → **no `rb`** → stays on top of B

```
     Stack A              Stack B
  ┌────────────┐       ┌────────────┐
  │  -56  [0]  │ ← top │ 5478  [5]  │ ← top
  │    1  [1]  │       │   56  [3]  │
  │   36  [2]  │       └────────────┘
  │   78  [4]  │
  └────────────┘
```

**Step 3 — `pb` then `rb` (push -56, then sink it)**

> -56 has index 0 → index 0 < mid(3) → **`rb`** → sink -56 to bottom of B

```
  after pb:                      after rb:
     Stack A              Stack B         Stack B
  ┌────────────┐       ┌────────────┐  ┌────────────┐
  │    1  [1]  │ ← top │  -56  [0]  │  │ 5478  [5]  │ ← top
  │   36  [2]  │       │ 5478  [5]  │  │   56  [3]  │
  │   78  [4]  │       │   56  [3]  │  │  -56  [0]  │
  └────────────┘       └────────────┘  └────────────┘
```

**After Phase 2:**

```
     Stack A              Stack B
  ┌────────────┐       ┌────────────┐
  │    1  [1]  │ ← top │ 5478  [5]  │ ← top
  │   36  [2]  │       │   56  [3]  │
  │   78  [4]  │       │  -56  [0]  │
  └────────────┘       └────────────┘
```

---

## Phase 3 — Sort 3

### Function: `sort_three(&a)`

A = [1, 36, 78] — already ascending.
→ **No operations needed.**

```
     Stack A              Stack B
  ┌────────────┐       ┌────────────┐
  │    1  [1]  │ ← top │ 5478  [5]  │ ← top
  │   36  [2]  │       │   56  [3]  │
  │   78  [4]  │       │  -56  [0]  │
  └────────────┘       └────────────┘
       ✓ sorted
```

---

## Phase 4 — Greedy Push-Back

### Functions: `assign_positions` → `assign_target_pos` → `calculate_costs` → `push_cheapest`

This is the **heart of the optimization**.

We push all elements from B back to A one at a time, always picking the element
that requires the **fewest total rotation operations**.

### How target positions are found

### Function: `assign_target_pos` → `find_target_a`

For each element in B, we find **where it belongs in A**:
→ find the element in A with the **smallest index that is still greater** than the B element's index.
→ If none exists (B element is the max), wrap around to the **element with the lowest index** (minimum).

The position of that element in A = `target_pos`.

### How costs are calculated

### Function: `calculate_costs`

For each element in B, we compute two costs:

**`cost_b`** — rotations needed to bring it to the top of B:
- `pos ≤ size_b / 2` → rotate forward: `cost_b = pos` *(positive → use `rb`)*
- `pos > size_b / 2` → rotate backward: `cost_b = pos - size_b` *(negative → use `rrb`)*

**`cost_a`** — rotations needed to bring its target slot to the top of A:
- `target_pos ≤ size_a / 2` → rotate forward: `cost_a = target_pos` *(positive → use `ra`)*
- `target_pos > size_a / 2` → rotate backward: `cost_a = target_pos - size_a` *(negative → use `rra`)*

**Total cost** = `|cost_a| + |cost_b|`

### The `ft_rotate_both` optimization

### Function: `push_cheapest` → `ft_rotate_both`

If both `cost_a` and `cost_b` have the **same sign**
(both need forward or both need backward rotation),
we use `rr` or `rrr` to rotate **both stacks in one operation** instead of two.
This saves one instruction per shared rotation step.

```c
void push_cheapest(t_stack **a, t_stack **b) {
    node = get_cheapest(*b);     // find min |cost_a| + |cost_b|
    ft_rotate_both(a, b, &ca, &cb);  // rr / rrr while same direction
    ft_rotate_a(a, &ca);             // finish remaining A rotations
    ft_rotate_b(b, &cb);             // finish remaining B rotations
    pa(a, b);                        // push to A
}
```

---

### Iteration 1

**A** = [1(idx=1,pos=0), 36(idx=2,pos=1), 78(idx=4,pos=2)]  `size_a=3`
**B** = [5478(idx=5,pos=0), 56(idx=3,pos=1), -56(idx=0,pos=2)]  `size_b=3`

**`assign_target_pos` results:**

| B elem | idx | Smallest idx in A > B's idx      | target_pos |
|--------|-----|----------------------------------|------------|
| 5478   | 5   | none → wrap → min(A) = 1 (idx=1) at pos 0 | **0** |
| 56     | 3   | 78 (idx=4) at pos 2              | **2**      |
| -56    | 0   | 1 (idx=1) at pos 0               | **0**      |

**`calculate_costs` results (size_a=3, size_b=3):**

| B elem | pos | target_pos | cost_b         | cost_a         | total |
|--------|-----|------------|----------------|----------------|-------|
| 5478   | 0   | 0          | 0  (0≤1)       | 0  (0≤1)       | **0** ← cheapest |
| 56     | 1   | 2          | +1 (1≤1)       | −1 (2>1→2−3)   | 2     |
| -56    | 2   | 0          | −1 (2>1→2−3)   | 0  (0≤1)       | 1     |

**Cheapest: 5478** → `cost_a=0`, `cost_b=0`
- `ft_rotate_both` → nothing (both zero)
- `ft_rotate_a` → nothing
- `ft_rotate_b` → nothing
- **`pa`** → push 5478 to top of A

```
     Stack A              Stack B
  ┌────────────┐       ┌────────────┐
  │ 5478  [5]  │ ← top │   56  [3]  │ ← top
  │    1  [1]  │       │  -56  [0]  │
  │   36  [2]  │       └────────────┘
  │   78  [4]  │
  └────────────┘
```

> Why this works: 5478 is the max (idx=5). It goes before the min (idx=1),
> which is A's position 0. Zero rotations needed — free insertion!

---

### Iteration 2

**A** = [5478(5,p0), 1(1,p1), 36(2,p2), 78(4,p3)]  `size_a=4`
**B** = [56(3,p0), -56(0,p1)]  `size_b=2`

**`assign_target_pos` results:**

| B elem | idx | Smallest idx in A > B's idx            | target_pos |
|--------|-----|----------------------------------------|------------|
| 56     | 3   | 78 (idx=4) at pos 3                    | **3**      |
| -56    | 0   | 1 (idx=1) at pos 1                     | **1**      |

**`calculate_costs` results (size_a=4, size_b=2):**

| B elem | pos | target_pos | cost_b       | cost_a         | total |
|--------|-----|------------|--------------|----------------|-------|
| 56     | 0   | 3          | 0  (0≤1)     | −1 (3>2→3−4)   | **1** ← cheapest |
| -56    | 1   | 1          | +1 (1≤1)     | +1 (1≤2)       | 2     |

**Cheapest: 56** → `cost_a=−1`, `cost_b=0`
- `ft_rotate_both` → nothing (different directions)
- `ft_rotate_b` → nothing (cb=0)
- `ft_rotate_a` → ca=−1 → **`rra`** × 1
- **`pa`** → push 56 on top of A

```
  after rra:                       after pa:
     Stack A              Stack B       Stack A              Stack B
  ┌────────────┐       ┌────────────┐  ┌────────────┐    ┌────────────┐
  │   78  [4]  │ ← top │   56  [3]  │  │   56  [3]  │ ←  │  -56  [0]  │ ← top
  │ 5478  [5]  │       │  -56  [0]  │  │   78  [4]  │    └────────────┘
  │    1  [1]  │       └────────────┘  │ 5478  [5]  │
  │   36  [2]  │                       │    1  [1]  │
  └────────────┘                       │   36  [2]  │
                                       └────────────┘
```

> Why before 78? 56 (idx=3) belongs just before 78 (idx=4, the next bigger element).
> After `rra`, 78 is at the top → `pa` places 56 in front of it. ✓

---

### Iteration 3

**A** = [56(3,p0), 78(4,p1), 5478(5,p2), 1(1,p3), 36(2,p4)]  `size_a=5`
**B** = [-56(0,p0)]  `size_b=1`

**`assign_target_pos` result:**

| B elem | idx | Smallest idx in A > B's idx   | target_pos |
|--------|-----|-------------------------------|------------|
| -56    | 0   | 1 (idx=1) at pos 3            | **3**      |

**`calculate_costs` result (size_a=5, size_b=1):**

| B elem | pos | target_pos | cost_b   | cost_a         | total |
|--------|-----|------------|----------|----------------|-------|
| -56    | 0   | 3          | 0 (0≤0)  | −2 (3>2→3−5)   | **2** |

**Only element → must push:**
- `ft_rotate_both` → nothing
- `ft_rotate_b` → nothing (cb=0)
- `ft_rotate_a` → ca=−2 → **`rra`** × 2
- **`pa`** → push -56 on top

```
  after rra × 2:                   after pa:
     Stack A              Stack B       Stack A              Stack B
  ┌────────────┐       ┌────────────┐  ┌────────────┐    ┌────────────┐
  │    1  [1]  │ ← top │  -56  [0]  │  │  -56  [0]  │ ←  │   empty    │
  │   36  [2]  │       └────────────┘  │    1  [1]  │    └────────────┘
  │   56  [3]  │                       │   36  [2]  │
  │   78  [4]  │                       │   56  [3]  │
  │ 5478  [5]  │                       │   78  [4]  │
  └────────────┘                       │ 5478  [5]  │
                                       └────────────┘
                                          ✓ sorted!
```

> Why before 1? -56 (idx=0) is the minimum. It belongs before 1 (idx=1).
> Two `rra` bring 1 to the top → `pa` places -56 before it. ✓

---

## Phase 5 — Shift

### Function: `shift_stack(&a)`

After all elements are back in A, the stack may still be "rotated"
(min element not at the top). We fix this.

```c
assign_positions(*stack_a);
lowest_pos = get_lowest_pos(*stack_a);   // find pos of minimum element
if (lowest_pos <= size_a / 2)
    cost = lowest_pos;                   // rotate forward
else
    cost = (size_a - lowest_pos) * -1;  // rotate backward (cheaper)
do_rotate(stack_a, cost, 'a');
```

A = [-56, 1, 36, 56, 78, 5478]
- `-56` is minimum, at pos **0**
- pos 0 ≤ 3 → cost = 0 → **no rotation needed**

---

## Final Result ✓

```
     Stack A              Stack B
  ┌────────────┐       ┌────────────┐
  │  -56  [0]  │ ← top │   empty    │
  │    1  [1]  │       └────────────┘
  │   36  [2]  │
  │   56  [3]  │
  │   78  [4]  │
  │ 5478  [5]  │
  └────────────┘
     ✓ sorted ascending (top → bottom)
```

**Total operations used:** `pb` × 3 + `rb` × 1 + `rra` × 3 + `pa` × 3 = **10 ops**

---

## Greedy Optimization Summary

```
Total cost per element = |cost_a| + |cost_b|
Algorithm always picks the element with the MINIMUM total cost
```

| Technique              | How it saves ops                                                             |
|------------------------|------------------------------------------------------------------------------|
| `ft_rotate_both` (`rr`/`rrr`) | When A and B both need rotation in the **same direction**, one op does both |
| Backward rotation (`rra`/`rrb`) | Elements closer to the bottom spin backward — may be cheaper than forward  |
| Phase-2 `rb` trick     | Small elements (idx < mid) are pushed to B's bottom, so large elements cluster at the top of B with low `cost_b` |
| `get_cheapest`         | Scanning all B elements every round ensures globally optimal choice per step |

This greedy produces roughly **~700 ops for 100 numbers** and **~5000 ops for 500 numbers**.
