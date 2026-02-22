# Push_Swap Algorithm Explanation

## Project Overview

**Push_Swap** is a sorting algorithm optimization project that sorts numbers using a limited set of stack operations. The goal is to sort a list of random integers using two stacks (A and B) with the minimum number of operations.

---

## The Problem

Given:
- A list of random integers
- Two stacks (A and B)
- A limited set of operations (push, rotate, swap, reverse rotate)

**Objective:** Sort stack A in ascending order using the minimum number of operations.

---

## The Custom Data Structure: `t_list`

The core of this algorithm's efficiency lies in the customized `t_list` struct:

```c
typedef struct s_list
{
    int             index;          // Normalized value (0 to n-1)
    int             pos;            // Current position in stack (0 = top)
    int             target_pos;     // Where this element should be placed in other stack
    int             cost_a;         // Moves needed to reach target in stack A
    int             cost_b;         // Moves needed to reach target in stack B
    long            content;        // The actual integer value
    struct s_list   *next;          // Pointer to next node
}   t_list;
```

### Why This Special Structure?

1. **`index` Field**
   - **Purpose:** Normalized rank of the value (0 = smallest, n-1 = largest)
   - **Why:** Allows comparison between stacks without knowing actual values
   - **Example:** Input `[5, 3, 1, 4]` → indices `[3, 1, 0, 2]`
   - **Benefit:** Makes finding insertion positions and comparisons O(1) after indexing

2. **`pos` Field**
   - **Purpose:** Track current position in the stack (index from top)
   - **Why:** Needed to calculate rotation costs efficiently
   - **Updated:** During each operation, recalculated with `ft_set_pos()`

3. **`target_pos` Field**
   - **Purpose:** Where the element should go when pushed back to stack A
   - **Why:** Helps determine the optimal insertion point for maximum efficiency
   - **Calculated:** For each element in B, find where it fits in A based on indices

4. **`cost_a` and `cost_b` Fields**
   - **Purpose:** Calculate the cost (number of moves) to position elements
   - **Why:** Implement a greedy algorithm by finding the "cheapest" element to move
   - **Formula:** 
     - `cost_a/b = position` if position ≤ stack_size/2 (rotate forward)
     - `cost_a/b = position - stack_size` if position > stack_size/2 (rotate backward)

5. **`content` Field**
   - **Purpose:** Store the actual integer value
   - **Type:** `long` to handle large numbers and overflow detection

---

## Algorithm Strategy

The algorithm uses a **size-based approach** with different strategies for different input sizes:

```
Input Size
    ↓
    ├─ Size = 2 → Sort with 1 swap (if needed)
    ├─ Size = 3 → 6 possible arrangements, 2-3 operations max
    ├─ Size = 4-5 → Push 2 smallest to B, sort A, insert back
    └─ Size > 5 → Push Swap Large Algorithm
```

### Stage 1: Indexing

**Function:** `ft_index_stack()`

```
Original: [5, 3, 1, 4]
           ↓
Copy to array
           ↓
[5, 3, 1, 4] → Sort → [1, 3, 4, 5]
           ↓
Map indices: 5→3, 3→1, 1→0, 4→2
           ↓
Indexed: [3, 1, 0, 2]
```

**Helper Functions:**
- `ft_copy_to_arr()` - Copies stack values to array
- `ft_sort_arr()` - Sorts array using bubble sort
- `ft_assign_index_to_each_node()` - Assigns normalized index to each node

---

### Stage 2: Small Stacks (2, 3, 4-5 elements)

#### Sort Two
Simply swap if needed: `sa()`

#### Sort Three
Pattern matching for all 6 possible orderings:
```c
// All 6 possible states with 2-3 operations needed:
[a,b,c] if b<a && a<c → sa
[a,b,c] if c<b && b<a → sa + rra
[a,b,c] if a<c && c<b → rra + sa
// ... etc
```

#### Sort Five
```
1. Find and push 2 smallest to stack B
2. Sort remaining 3 in stack A
3. Push back elements from B (naturally sorted due to indices)
```

---

### Stage 3: Large Stacks (> 5 elements)

**Algorithm: Push Swap Large (Greedy Cost-Based)**

#### Step 1: Initial Partitioning
```c
size = ft_lstsize(*a);
mid = size / 2;

// Push all elements except top 3 to B
while (ft_lstsize(*a) > 3)
{
    pb(&a, &b);
    // If element is in lower half, bring it to top
    if ((*b)->index < mid)
        rb(b);
}
```

#### Step 2: Iterative Insertion (Main Loop)

For each element in B, calculate costs and insert it optimally:

```c
while (*b)
{
    ft_set_pos(*a);          // Update positions
    ft_set_pos(*b);
    ft_set_target_pos(*a, *b); // Where each B element should go
    ft_set_costs(*a, *b);       // Calculate rotation costs
    ft_excute_all(&a, &b);      // Execute optimal moves
}
```

#### Step 3: Target Position Calculation

**Key Concept:** For each element in B, find where it belongs in A

```c
void ft_set_target_pos(t_list *a, t_list *b)
{
    // For each element in B:
    // Find the smallest element in A that is LARGER than it
    // That's where it should be inserted
    
    // Example:
    // A indices: [0, 2, 4, 6]
    // B element with index 3
    // → Find smallest A index > 3 → target_pos of element with index 4
}
```

#### Step 4: Cost Calculation

Two types of costs calculated:

1. **Cost to position in A** (`cost_a`)
   - How many rotations to place the target element at the top
   - Can rotate forward (positive) or backward (negative)

2. **Cost to position in B** (`cost_b`)
   - How many rotations to bring current element to top
   - Can rotate forward (positive) or backward (negative)

```c
// Optimize by considering rotation direction
if (pos <= size / 2)
    cost = pos;        // Rotate forward
else
    cost = pos - size; // Rotate backward (fewer moves)
```

#### Step 5: Greedy Selection

Select the element with minimum total cost:

```c
t_list *ft_get_cheapest(t_list *b)
{
    // Calculate: |cost_a| + |cost_b| for each element
    // Return element with minimum total cost
}
```

#### Step 6: Optimized Rotation Execution

```c
void ft_excute_all(t_list **a, t_list **b)
{
    // 1. Rotate both simultaneously (same direction, reduces cost)
    ft_rotate_both(&a, &b, &ca, &cb);
    
    // 2. Rotate A the remaining amount
    ft_rotate_a(&a, &ca);
    
    // 3. Rotate B the remaining amount
    ft_rotate_b(&b, &cb);
    
    // 4. Push element to A
    pa(&b, &a);
}
```

**Example:**
```
If cost_a = 3, cost_b = 2:
→ Do 2 simultaneous rotations (rr)
→ Do 1 more rotation on A (ra)
→ Push to A (pa)
Total: 4 operations instead of 5
```

#### Step 7: Final Rotation

After all elements are in A, rotate to ensure the smallest element is at position 0:

```c
ft_final_rotation(&a)
// Brings the minimum element to top of stack A
```

---

## Why This Approach Is Efficient

### 1. **Indexing Optimization**
- Converts problem to comparing indices (0-n) instead of actual values
- Eliminates need for value comparison in insertion logic
- O(n log n) once at start, not O(n²) during sorting

### 2. **Cost-Based Greedy Strategy**
- Always selects globally optimal move (minimum cost)
- Two-stack approach allows parallel consideration of moves
- Simultaneous rotations (`rr`, `rrr`) reduce operation count

### 3. **Partitioning Strategy**
- Large stacks pre-partitioned by median to maintain cache locality
- Elements in "good" positions pushed first
- Reduces average number of rotations needed

### 4. **Position Tracking**
- Real-time position tracking avoids O(n) search for each operation
- Positions recalculated only after operations (O(n) worst case)
- Cost calculations are O(n) per element, but done optimally

---

## Helper Functions Summary

### Comparison & Assignment Helpers

| Function | Purpose | Time Complexity |
|----------|---------|-----------------|
| `ft_copy_to_arr()` | Copy stack values to array | O(n) |
| `ft_sort_arr()` | Bubble sort array (for indexing) | O(n²) |
| `ft_assign_index_to_each_node()` | Assign normalized indices | O(n²) |
| `ft_index_stack()` | Orchestrate indexing process | O(n²) |

### Position & Cost Helpers

| Function | Purpose | Time Complexity |
|----------|---------|-----------------|
| `ft_set_pos()` | Update position field for all nodes | O(n) |
| `ft_get_min_pos()` | Find position of minimum element | O(n) |
| `ft_set_target_pos()` | Calculate target positions | O(n²) |
| `ft_set_costs()` | Calculate rotation costs | O(n) |
| `ft_get_cheapest()` | Find minimum cost element | O(n) |

### Rotation Helpers

| Function | Purpose | Optimization |
|----------|---------|---------------|
| `ft_rotate_both()` | Rotate both stacks simultaneously | Reduces operations by 50% when possible |
| `ft_rotate_a()` | Rotate only stack A | Handles remaining cost_a |
| `ft_rotate_b()` | Rotate only stack B | Handles remaining cost_b |
| `ft_excute_all()` | Execute all moves for one element | Orchestrates the optimization |

### Validation Helpers

| Function | Purpose |
|----------|---------|
| `check_dup()` | Detect duplicate values |
| `is_sorted()` | Check if stack is already sorted |
| `find_min()` | Find node with minimum value |
| `find_index()` | Find position of specific value |

---

## Complexity Analysis

### Time Complexity
- **Indexing Phase:** O(n²) - bubble sort
- **Sorting Phase:** O(n²) - for large stacks with n iterations, each costing O(n)
- **Overall:** O(n²)

### Space Complexity
- **O(n)** - one linked list plus one auxiliary array

### Operation Count (Empirical)
- **Small (≤5):** 2-3 operations
- **Medium (6-100):** ~5n operations
- **Large (100+):** ~11n operations for optimal implementations

---

## Complete Example Walkthrough with Visualization

Let me show you a detailed step-by-step example: **Input:** `[21 5 8 2 34]`

---

### PHASE 1: INDEXING (NORMALIZATION)

This is the crucial first step that transforms the problem.

#### Step 1.1: Create Array and Sort

```
Original Stack A:
┌─────────┬─────────┬─────────┬─────────┬─────────┐
│   21    │    5    │    8    │    2    │   34    │
├─────────┼─────────┼─────────┼─────────┼─────────┤
│ value   │ value   │ value   │ value   │ value   │
└─────────┴─────────┴─────────┴─────────┴─────────┘
  pos 0     pos 1     pos 2     pos 3     pos 4

Copy to array:  [21, 5, 8, 2, 34]
                  ↓
              Bubble Sort
                  ↓
Sorted array:   [2, 5, 8, 21, 34]
```

#### Step 1.2: Assign Indices

Map each original value to its position in sorted array:

```
21 → position 3 in [2,5,8,21,34] → index = 3
 5 → position 1 in [2,5,8,21,34] → index = 1
 8 → position 2 in [2,5,8,21,34] → index = 2
 2 → position 0 in [2,5,8,21,34] → index = 0
34 → position 4 in [2,5,8,21,34] → index = 4
```

#### Step 1.3: Create Indexed Stack

```
Stack A (AFTER INDEXING):
┌──────────────┐
│ 21, idx=3    │ ← pos 0 (top)
├──────────────┤
│ 5,  idx=1    │ ← pos 1
├──────────────┤
│ 8,  idx=2    │ ← pos 2
├──────────────┤
│ 2,  idx=0    │ ← pos 3
├──────────────┤
│ 34, idx=4    │ ← pos 4
└──────────────┘

Representation: [21(3), 5(1), 8(2), 2(0), 34(4)]
                where format: value(index)
```

---

### PHASE 2: INITIAL PARTITIONING

**Goal:** Push all but top 3 elements to stack B

```
Size = 5, so push until 3 remain in A
```

#### Step 2.1: First Push (pb)

```
BEFORE: A = [21(3), 5(1), 8(2), 2(0), 34(4)]
        B = []

ACTION: pb (push top of A to B)

AFTER:  A = [5(1), 8(2), 2(0), 34(4)]
        B = [21(3)]
           pos 0
```

#### Step 2.2: Second Push

```
Check: Is 5(1) < mid (size/2 = 2.5)?
       1 < 2.5 → YES, so rotate B to put it at bottom for now

ACTION: pb, then rb

BEFORE: A = [5(1), 8(2), 2(0), 34(4)]
        B = [21(3)]

AFTER pb:  A = [8(2), 2(0), 34(4)]
           B = [5(1), 21(3)]

AFTER rb:  A = [8(2), 2(0), 34(4)]
           B = [21(3), 5(1)]  ← 21 rotated to bottom
```

#### Step 2.3: Final Push to B (only 3 left in A)

```
BEFORE: A = [8(2), 2(0), 34(4)]
        B = [21(3), 5(1)]

Check: Is 8(2) < 2.5? YES
ACTION: pb then rb

AFTER pb:  A = [2(0), 34(4)]
           B = [8(2), 21(3), 5(1)]

AFTER rb:  B = [21(3), 5(1), 8(2)]
```

**STATE AFTER PARTITIONING:**
```
Stack A (to be sorted, size=3):
┌──────────┬──────────┬──────────┐
│ 2(0)     │ 34(4)    │          │
├──────────┼──────────┤          │
│ pos 0    │ pos 1    │ (pos 2)  │
└──────────┴──────────┴──────────┘

Stack B (to be inserted back):
┌──────────┬──────────┬──────────┐
│ 21(3)    │ 5(1)     │ 8(2)     │
├──────────┼──────────┼──────────┤
│ pos 0    │ pos 1    │ pos 2    │
└──────────┴──────────┴──────────┘
```

---

### PHASE 3: SORT TOP 3 IN STACK A

```
A = [2(0), 34(4)]

Call sort_three() → Already sorted! (2 < 34)
Result: A = [2(0), 34(4)]
```

---

### PHASE 4: INTELLIGENT INSERTION (Main Loop)

This is where the magic happens with cost calculation.

#### 4th ITERATION 1: Insert 21(3)

**Steps 1-2: Update Positions**

```
ft_set_pos(A): Updates each node's position field
A = [2(0), 34(4)]
    pos=0  pos=1

ft_set_pos(B): Updates each node's position field
B = [21(3), 5(1), 8(2)]
    pos=0  pos=1  pos=2
```

**Step 3: Find Target Position for B's Elements**

For element 21(3) in B:
- Need to find where it goes in A
- Find smallest element in A with index > 3
- 34(4) has index 4, which is > 3 ✓
- So target_pos = 1 (position of 34)

```
B element: 21(3)
A: [2(0), 34(4)]
        
Looking for: smallest index > 3 → found 34(4) at pos 1
target_pos = 1
```

**Step 4: Calculate Costs**

For 21(3):
```
Current position in B: pos = 0
Stack B size: 3

cost_b = 0 (0 ≤ 3/2, so 0 moves needed)

Target position in A: pos = 1
Stack A size: 2

cost_a = 1 (1 ≤ 2/2, so 1 forward rotate needed)

Total cost = |1| + |0| = 1
```

**Step 5: Select Cheapest Element**

Only one element available (21 at top), so it's selected by default.

**Step 6: Execute Moves**

```
cost_a = 1, cost_b = 0

ft_rotate_both: Both costs not in same direction, skip
ft_rotate_a: Need 1 forward rotate
    ┌──────────────┬──────────────┐
    │ 2(0)         │ 34(4)        │
    ├──────────────┼──────────────┤
    │ pos=0        │ pos=1        │
    └──────────────┴──────────────┘
    
    ra (rotate A up)
    
    ┌──────────────┬──────────────┐
    │ 34(4)        │ 2(0)         │
    ├──────────────┼──────────────┤
    │ pos=0        │ pos=1        │
    └──────────────┴──────────────┘

ft_rotate_b: No rotates needed

pa (push from B to A)
    Before: B = [21(3), 5(1), 8(2)]
    After:  B = [5(1), 8(2)]
            A = [21(3), 34(4), 2(0)]
```

**STATE AFTER ITERATION 1:**
```
A = [21(3), 34(4), 2(0)]
    pos=0  pos=1  pos=2

B = [5(1), 8(2)]
    pos=0  pos=1

Operations output: pb, rb, ra, pa
```

---

#### ITERATION 2: Insert 5(1)

**Find Target**

```
B element: 5(1)
A: [21(3), 34(4), 2(0)]

Looking for: smallest index > 1 → found 21(3) at pos 0
target_pos = 0
```

**Calculate Costs**

```
B = [5(1), 8(2)]
    pos=0  pos=1

5 is at pos 0
cost_b = 0

A = [21(3), 34(4), 2(0)]
    pos=0  pos=1  pos=2

Target pos = 0
cost_a = 0

Total cost = |0| + |0| = 0 ← CHEAPEST!
```

**Execute**

```
Already at right positions, just:

pa (push from B to A)
    Before: A = [21(3), 34(4), 2(0)]
            B = [5(1), 8(2)]
    After:  A = [5(1), 21(3), 34(4), 2(0)]
            B = [8(2)]
```

**STATE AFTER ITERATION 2:**
```
A = [5(1), 21(3), 34(4), 2(0)]
B = [8(2)]

Operations output: pb, rb, ra, pa, [skip], pa
```

---

#### ITERATION 3: Insert 8(2)

**Find Target**

```
B element: 8(2)
A: [5(1), 21(3), 34(4), 2(0)]

Looking for: smallest index > 2 → found 21(3) at pos 1
target_pos = 1
```

**Calculate Costs**

```
B = [8(2)]
    pos=0

cost_b = 0

A = [5(1), 21(3), 34(4), 2(0)]
    pos=0  pos=1  pos=2  pos=3

Target pos = 1
Size A = 4
cost_a = 1 (1 ≤ 4/2, forward rotate)

Total cost = |1| + |0| = 1
```

**Execute**

```
ra (rotate A once)
    [5(1), 21(3), 34(4), 2(0)] → [21(3), 34(4), 2(0), 5(1)]

pa (push)
    After: A = [8(2), 21(3), 34(4), 2(0), 5(1)]
           B = []
```

**STATE AFTER ITERATION 3:**
```
A = [8(2), 21(3), 34(4), 2(0), 5(1)]
B = []

All elements from B are back in A!
```

---

### PHASE 5: FINAL ROTATION

The minimum element (2 with index 0) needs to be at the top.

```
ft_set_pos(A):
A = [8(2), 21(3), 34(4), 2(0), 5(1)]
    pos=0  pos=1  pos=2  pos=3  pos=4

ft_get_min_pos(A): Find position of element with min index
    Scanning: 2→3, 21→3, 34→4, 2→0 ✓ (minimum index=0)
    Position of min: 3

min_pos = 3
stack size = 5

if (3 ≤ 5/2)? → 3 ≤ 2.5? → NO
else: use reverse rotations

rra 3 times: (5 - 3 = 2, but we do it from back)
Actually: min_pos - size = 3 - 5 = -2, so 2 reverse rotations

rra:
[8(2), 21(3), 34(4), 2(0), 5(1)] → [5(1), 8(2), 21(3), 34(4), 2(0)]
                                
rra:
[5(1), 8(2), 21(3), 34(4), 2(0)] → [2(0), 5(1), 8(2), 21(3), 34(4)]
```

**FINAL RESULT:**
```
┌────────┬────────┬────────┬────────┬────────┐
│ 2(0)   │ 5(1)   │ 8(2)   │ 21(3)  │ 34(4)  │
├────────┼────────┼────────┼────────┼────────┤
│ idx=0  │ idx=1  │ idx=2  │ idx=3  │ idx=4  │
└────────┴────────┴────────┴────────┴────────┘

✓ SORTED! Minimum to Maximum (indices 0→1→2→3→4)
         Values:      2 < 5 < 8 < 21 < 34
```

---

## Complete Example Walkthrough (Simple Case)

**Input:** `4 2 1 3`

### Step 1: Indexing
```
Original:  4 2 1 3
Sorted:    1 2 3 4 → Indices: [3, 1, 0, 2]
Stack A:   4(3) → 2(1) → 1(0) → 3(2)
```

### Step 2: Push to B (size > 3)
```
Push 3(2) → B:    3(2) → NULL
Push 1(0) → B:    1(0) → 3(2)
Push 2(1) → B:    2(1) → 1(0) → 3(2)
```
A remaining: `4(3)`

### Step 3: Insert back optimally
```
// For 2(1): target is before 3(2), cost = minimal rotation
// For 1(0): target is before 2(1), cost = minimal rotation
// For 3(2): target is after 4(3), cost = minimal rotation
```

### Step 4: Final result
```
A: 1(0) → 2(1) → 3(2) → 4(3)
```

---

## Visual Cost Calculation Example

Let me show exactly how costs are calculated for rotation optimization:

### Scenario: 6 Elements

```
Stack A (size=6):
Top  ┌─────────┐
  0  │ 1(0)    │
  1  │ 5(2)    │
  2  │ 8(3)    │
  3  │ 3(1)    │
  4  │ 2(0)    │  ← This element needs to be inserted
  5  │ 9(5)    │
     └─────────┘
Bottom

Stack B (size=7):
Top  ┌─────────┐
  0  │ 4(2) ◄─ We want to insert this element here
  1  │ 6(4)    │
  2  │ 7(5)    │
  3  │ 2(1)    │
  4  │ 1(0)    │
  5  │ 3(1)    │
  6  │ 5(3)    │
     └─────────┘
Bottom
```

### Cost Calculation Step-by-Step

#### For element 4(2) in stack B (pos=0):

**1. Find Target Position in Stack A:**
- Element has index=2
- Scan A looking for smallest index > 2
- 5(2) has index 2 (not > 2)
- 8(3) has index 3 (> 2) ← FOUND! pos=2
- Target position = 2

**2. Calculate cost_b (cost to bring element to top of B):**
```
Element position: 0
Stack size B: 7

if (0 ≤ 7/2 = 3.5)? → YES
    cost_b = 0 positions (already at top!)

Interpretation: rb × 0 = no rotations needed
```

**3. Calculate cost_a (cost to position A's target at top):**
```
Target position: 2
Stack size A: 6

if (2 ≤ 6/2 = 3)? → YES
    cost_a = 2 (forward rotation)

Interpretation: ra × 2 positions
    [1(0), 5(2), 8(3), 3(1), 2(0), 9(5)]
    
    After ra:  [5(2), 8(3), 3(1), 2(0), 9(5), 1(0)]
    After ra:  [8(3), 3(1), 2(0), 9(5), 1(0), 5(2)] ← target now at top
```

**4. Total Cost:**
```
Total = |cost_a| + |cost_b|
      = |2| + |0|
      = 2 moves
```

---

#### For element 6(4) in stack B (pos=1):

**1. Find Target Position:**
- Index = 4
- Scan A: 8(3) has index 3 (not > 4), 9(5) has index 5 (> 4) ✓
- Target position = 5

**2. Calculate cost_b:**
```
Position: 1
Size B: 7

if (1 ≤ 3.5)? → YES
    cost_b = 1 (forward rotation)

Interpretation: rb × 1
    [4(2), 6(4), 7(5), 2(1), 1(0), 3(1), 5(3)]
    After rb: [6(4), 7(5), 2(1), 1(0), 3(1), 5(3), 4(2)]
```

**3. Calculate cost_a:**
```
Position: 5
Size A: 6

if (5 ≤ 3)? → NO
    cost_a = 5 - 6 = -1 (backward rotation!)

Interpretation: rra × 1 (more optimal than ra × 5)
    [1(0), 5(2), 8(3), 3(1), 2(0), 9(5)]
    After rra: [9(5), 1(0), 5(2), 8(3), 3(1), 2(0)] ← target now at top
```

**4. Total Cost:**
```
Total = |cost_a| + |cost_b|
      = |-1| + |1|
      = 2 moves
```

---

#### For element 7(5) in stack B (pos=2):

**1. Find Target Position:**
- Index = 5
- Scan A: No element has index > 5
- Wrap around: target = position of minimum index = 0 (1(0))

**2. Calculate cost_b:**
```
Position: 2
Size B: 7

if (2 ≤ 3.5)? → YES
    cost_b = 2 (forward rotation)
```

**3. Calculate cost_a:**
```
Position: 0 (minimum is already at top!)
Size A: 6

if (0 ≤ 3)? → YES
    cost_a = 0
```

**4. Total Cost:**
```
Total = |0| + |2| = 2 moves
```

---

#### For element 2(1) in stack B (pos=3):

**1. Find Target Position:**
- Index = 1
- 5(2) has index 2 (> 1) ✓
- Target position = 1

**2. Calculate cost_b:**
```
Position: 3
Size B: 7

if (3 ≤ 3.5)? → YES (borderline!)
    cost_b = 3 (forward rotation)
```

**3. Calculate cost_a:**
```
Position: 1
Size A: 6

if (1 ≤ 3)? → YES
    cost_a = 1
```

**4. Total Cost:**
```
Total = |1| + |3| = 4 moves ← EXPENSIVE!
```

---

### Cost Summary & Selection

```
┌─────────────────────┬──────────┬──────────┬───────────┐
│ Element             │ cost_a   │ cost_b   │ Total     │
├─────────────────────┼──────────┼──────────┼───────────┤
│ 4(2) at pos 0       │ 2        │ 0        │ 2 ◄ BEST  │
│ 6(4) at pos 1       │ -1       │ 1        │ 2 ◄ BEST  │
│ 7(5) at pos 2       │ 0        │ 2        │ 2 ◄ BEST  │
│ 2(1) at pos 3       │ 1        │ 3        │ 4 (skip)  │
│ 1(0) at pos 4       │ varies   │ varies   │ varies    │
│ 3(1) at pos 5       │ varies   │ varies   │ varies    │
│ 5(3) at pos 6       │ varies   │ varies   │ varies    │
└─────────────────────┴──────────┴──────────┴───────────┘

ALGORITHM SELECTS: 4(2) (first minimum found)
```

---

### Execution of Selected Element: 4(2)

```
Current state:
A = [1(0), 5(2), 8(3), 3(1), 2(0), 9(5)]
B = [4(2), 6(4), 7(5), 2(1), ...]

cost_a = 2 (ra × 2)
cost_b = 0 (no rotation)

Step 1: ft_rotate_both()
  Check if both costs same sign:
    2 > 0 and 0 > 0? → NO
  Skip simultaneous rotation

Step 2: ft_rotate_a()
  While cost_a > 0:
    ra() → A = [5(2), 8(3), 3(1), 2(0), 9(5), 1(0)]
    cost_a = 1
    ra() → A = [8(3), 3(1), 2(0), 9(5), 1(0), 5(2)]
    cost_a = 0

Step 3: ft_rotate_b()
  While cost_b != 0: (skip, already 0)

Step 4: pa()
  Push 4(2) from B to A:
  A = [4(2), 8(3), 3(1), 2(0), 9(5), 1(0), 5(2)]
  B = [6(4), 7(5), 2(1), ...]

Operations printed: ra, ra, pa
```

---

## Understanding the Optimization

### Why Negative Costs (Reverse Rotation)?

```
Consider moving element to position 5 in stack of size 6:

Option 1 (Forward):  ra × 5 = 5 operations
    [a, b, c, d, e, TARGET]
    After 5 forward rotations → TARGET moves to front

Option 2 (Backward): rra × 1 = 1 operation
    [a, b, c, d, e, TARGET]
    After 1 backward rotation → TARGET moves to front

cost_a = 5 - 6 = -1 ← NEGATIVE means "use reverse instead"
Total actual cost = |−1| = 1 operation (better!)
```

### Why Simultaneous Rotations Matter

```
If cost_a = 3 and cost_b = 2:

Without optimization:
  ra × 3 = 3 operations
  rb × 2 = 2 operations
  Total = 5 operations

With simultaneous rotations:
  rr × 2 = 2 operations (both stacks rotate together)
  ra × 1 = 1 operation (A alone)
  Total = 3 operations ← SAVED 2 OPERATIONS!

The algorithm:
  1. Do rr while both > 0: 2 times
  2. Do ra while cost_a > 0: 1 time
  Saves ~40% of moves!
```

---

## Visual Reference: Stack Operations

Understanding how each operation transforms the stacks:

### Push Operations (pa, pb)

#### pb: Push top of A to B
```
Before:         After pb:
A = [3, 5, 8]   A = [5, 8]
B = [2, 4]      B = [3, 2, 4]
                   ↑ element 3 pushed

Mechanics:
1. Save top of A: tmp = A (points to node with value 3)
2. Remove from A: A = tmp->next (now points to 5)
3. Link to B: tmp->next = B (3 now points to 2)
4. Make B point to new top: B = tmp (B now starts with 3)
```

#### pa: Push top of B to A
```
Before:         After pa:
A = [5, 8]      A = [3, 5, 8]
B = [3, 2, 4]   B = [2, 4]
                   ↑ element 3 pushed back

Same mechanics as pb, just different stacks
```

---

### Rotate Operations (ra, rb, rr)

#### ra: Rotate A (first element goes to last)
```
Before:
┌─────────┐
│ 3 ◄─ Top
├─────────┤
│ 5
├─────────┤
│ 8
├─────────┤
│ 1 ◄─ Bottom
└─────────┘

After ra:
┌─────────┐
│ 5 ◄─ Top (moved up)
├─────────┤
│ 8
├─────────┤
│ 1
├─────────┤
│ 3 ◄─ Bottom (wrapped around)
└─────────┘

Visual: [3, 5, 8, 1] → [5, 8, 1, 3]

Mechanics:
1. Save first: first = *stack (3)
2. Move pointer: *stack = first->next (now points to 5)
3. Find last: last = ft_lstlast(*stack) (points to 1)
4. Link: last->next = first (1 points to 3)
5. Clear: first->next = NULL (3 points nowhere)

Time: O(n) to find last, but very fast in practice
```

---

### Reverse Rotate Operations (rra, rrb, rrr)

#### rra: Reverse Rotate A (last element goes to first)
```
Before:
┌─────────┐
│ 3 ◄─ Top
├─────────┤
│ 5
├─────────┤
│ 8
├─────────┤
│ 1 ◄─ Bottom
└─────────┘

After rra:
┌─────────┐
│ 1 ◄─ Top (moved to front)
├─────────┤
│ 3
├─────────┤
│ 5
├─────────┤
│ 8 ◄─ Bottom
└─────────┘

Visual: [3, 5, 8, 1] → [1, 3, 5, 8]

More efficient than ra × 3 for moving last to first
Time: O(n) to traverse but still faster than multiple ra
```

---

### Swap Operations (sa, sb, ss)

#### sa: Swap top 2 of A
```
Before:         After sa:
┌─────────┐     ┌─────────┐
│ 3       │     │ 5       │
├─────────┤     ├─────────┤
│ 5       │     │ 3       │
├─────────┤     ├─────────┤
│ 8       │     │ 8       │
└─────────┘     └─────────┘

Mechanics:
1. Swap nodes: 
   - tmp = A->next (5)
   - A->next = tmp->next (8)
   - tmp->next = A (5 points to 3)
   - A = tmp (A now points to 5)

Visual: [3, 5, 8] → [5, 3, 8]
Time: O(1) - constant time!
```

---

## Complete Mini-Example: Sorting [3, 2, 1]

Let's trace through the smallest non-trivial case:

### Initial State
```
Input: 3 2 1

AFTER INDEXING:
A = [3(2), 2(1), 1(0)]  (format: value(index))
```

### Sort Three Algorithm

```
Call sort_three() function:

Current state:
a = 3(2) ← first node
b = 2(1) ← second node  
c = 1(0) ← third node

Check patterns:
  b < a && a < c?  → 2<3 && 3<1? → NO
  c < b && b < a?  → 1<2 && 2<3? → YES ✓

Execute: sa, then rra

Step 1: sa (swap top 2)
    Before: A = [3(2), 2(1), 1(0)]
    After:  A = [2(1), 3(2), 1(0)]

Step 2: rra (rotate down)
    Before: A = [2(1), 3(2), 1(0)]
    After:  A = [1(0), 2(1), 3(2)]
    
    Explanation:
    - Last element (1(0)) moves to front
    - Result is sorted: 1 < 2 < 3 ✓
```

---

## Memory Layout Visualization

Understanding how the linked list is arranged in memory:

```
Linked List Structure:

Stack A = [8(3), 5(1), 2(0)]

Memory Layout:
┌─────────────────────────────────────┐
│ Node 1 (8)                          │
├─────────────────────────────────────┤
│ index: 3                            │
│ pos: 0                              │
│ content: 8                          │
│ next: ───────────┐                  │
└─────────────────┼──────────────────┘
                  │
                  ▼
┌─────────────────────────────────────┐
│ Node 2 (5)                          │
├─────────────────────────────────────┤
│ index: 1                            │
│ pos: 1                              │
│ content: 5                          │
│ next: ───────────┐                  │
└─────────────────┼──────────────────┘
                  │
                  ▼
┌─────────────────────────────────────┐
│ Node 3 (2)                          │
├─────────────────────────────────────┤
│ index: 0                            │
│ pos: 2                              │
│ content: 2                          │
│ next: NULL                          │
└─────────────────────────────────────┘

Traversal: A → Node1(8) → Node2(5) → Node3(2) → NULL
```

---

## Algorithm Performance Timeline

For input size n = 12:

```
┌──────────────────────────────────────────────────┐
│ PHASE 1: INDEXING                               │
├──────────────────────────────────────────────────┤
│ Time: O(n²)                                     │
│ - Copy to array: O(n)                           │
│ - Bubble sort: O(n²)                            │
│ - Assign indices: O(n²)                         │
│ Operations output: 0                            │
└──────────────────────────────────────────────────┘
                    ↓
┌──────────────────────────────────────────────────┐
│ PHASE 2: INITIAL PUSH                           │
├──────────────────────────────────────────────────┤
│ Time: O(n)                                      │
│ - Push 9 elements to B: 9 pb               │
│ - Conditional rb based on index: ~4 rb         │
│ Operations output: ~13 operations               │
└──────────────────────────────────────────────────┘
                    ↓
┌──────────────────────────────────────────────────┐
│ PHASE 3: SORT TOP 3                             │
├──────────────────────────────────────────────────┤
│ Time: O(1)                                      │
│ - Maximum 2-3 operations for any arrangement    │
│ Operations output: 0-3 operations               │
└──────────────────────────────────────────────────┘
                    ↓
┌──────────────────────────────────────────────────┐
│ PHASE 4: INTELLIGENT INSERTION (Main Loop)      │
├──────────────────────────────────────────────────┤
│ Time: O(n²) - n iterations, each O(n) analysis │
│ - Loop 9 times (B has 9 elements)               │
│ - Each iteration:                                │
│   - ft_set_pos: O(n)                            │
│   - ft_set_target_pos: O(n²)  ← bottleneck     │
│   - ft_set_costs: O(n)                          │
│   - Execute: O(n) rotations avg                 │
│ Operations output: ~5n operations (greedy opt)  │
└──────────────────────────────────────────────────┘
                    ↓
┌──────────────────────────────────────────────────┐
│ PHASE 5: FINAL ROTATION                         │
├──────────────────────────────────────────────────┤
│ Time: O(n)                                      │
│ - Set positions: O(n)                           │
│ - Find minimum: O(n)                            │
│ - Final rotation: O(n) moves                    │
│ Operations output: 0-5 operations               │
└──────────────────────────────────────────────────┘

Total Operations for n=12: ~60 operations (optimal ~12*5 = 60)
```

---

## Key Insights

1. **Index Normalization** is crucial - it allows universal comparison regardless of value range
2. **Dual Cost Tracking** (cost_a, cost_b) enables optimization across two stacks
3. **Simultaneous Operations** (rr, rrr) are the secret to efficiency
4. **Greedy Approach** works because each element insertion is independent
5. **Lazy Position Updates** (only after changes) balances accuracy with performance

---

## Operation Set (Push Swap Commands)

```
sa - Swap top 2 of A
sb - Swap top 2 of B
ss - Swap both
pa - Push top of B to A
pb - Push top of A to B
ra - Rotate A up (first → last)
rb - Rotate B up
rr - Rotate both
rra - Rotate A down (last → first)
rrb - Rotate B down
rrr - Rotate both down
```

Each operation costs **1 move**.

---

## Debugging Guide: Common Issues and Solutions

### Issue 1: Understanding Why Negative Costs

**Question:** Why is cost_a = -2 for some positions?

**Answer:** 
```
Negative cost = use REVERSE rotation instead of forward

Example: Stack of size 6, need element at position 5
- Forward approach: ra × 5 = 5 operations  
- Backward approach: rra × 1 = 1 operation

cost_a = 5 - 6 = -1 (encode as -1, execute as |−1| = 1 rra)
```

---

### Issue 2: Target Position Confusion

**Question:** How does `ft_set_target_pos()` decide where an element goes?

**Answer:**
```
Algorithm for element B[i] finding target in A:

1. SCAN all elements in A
2. FIND: smallest index in A that is GREATER than index of B[i]
3. PLACE IT: target_pos = position of that found element
4. IF NONE FOUND: wrap around to position of minimum element in A

Example:
A indices: [0, 2, 4, 6]       A indices: [0, 2, 4, 6]
B element index: 3            B element index: 5

Find > 3: found 4 ✓           Find > 5: NOT FOUND
Target = pos of 4 (pos=2)     Wrap to min = pos of 0 (pos=0)
```

---

### Issue 3: Why Index Duplication in Sort

**Question:** In `ft_assign_index_to_each_node()`, why scan all n² pairs?

**Answer:**
```
The function assigns indices by matching content with sorted array.
For each node in the stack, search the entire sorted array:

for each node in stack:
  for each position in sorted_array:
    if node->content == sorted_array[position]:
      node->index = position
      break

This is O(n²) but:
- Happens ONCE at the beginning
- Very simple comparison logic
- Alternative approach (hash table) might be overkill for this project
```

---

### Issue 4: Position Recalculation

**Question:** When do positions change? Do we need to recalculate every iteration?

**Answer:**
```
Positions CHANGE after every operation that modifies stacks:
- pb/pa: changes both A and B positions
- ra/rb/rr: changes positions in that stack
- sa/sb: does NOT change positions (swap maintains sequence)

SOLUTION: Call ft_set_pos() at start of each main loop iteration
- This is O(n) but necessary for correctness
- Some implementations cache, but this is clearer

THE PATTERN:
while (*b)
{
    ft_set_pos(*a);            // ← Update positions
    ft_set_pos(*b);             // ← Required!
    ft_set_target_pos(*a, *b); // ← Uses current positions
    ft_set_costs(*a, *b);      // ← Uses positions and target
    ft_excute_all(&a, &b);     // ← Modifies stack
}
```

---

### Issue 5: Cheapest Element Selection

**Question:** What if multiple elements have the same minimum cost?

**Answer:**
```c
t_list *ft_get_cheapest(t_list *b)
{
    t_list *cheapest = b;
    int min_cost = abs(b->cost_a) + abs(b->cost_b);
    
    b = b->next;
    while (b)
    {
        int cost = abs(b->cost_a) + abs(b->cost_b);
        if (cost < min_cost)  // ← Strict <, not <=
        {
            min_cost = cost;
            cheapest = b;
        }
        b = b->next;
    }
    return (cheapest);
}

Result: Returns FIRST element with minimum cost
- Not random, deterministic
- Good enough for this algorithm
```

---

### Issue 6: Final Rotation Logic

**Question:** Why sometimes do we use ra instead of rra at the end?

**Answer:**
```c
int min_pos = ft_get_min_pos(a);

if (min_pos <= size / 2)
    // Forward is cheaper: ra × min_pos
else
    // Backward is cheaper: rra × (size - min_pos)
    // Encoded as: 0 - (size - min_pos) when using signed rotation

Example: [5, 8, 9, 1, 2] (1 is at position 3, size=5)
- Forward: ra × 3 = 3 operations
- Backward: rra × 2 = 2 operations (better!)
- We use backward
```

---

## Tracing the Algorithm Step-by-Step

### Minimal Example: Sorting [2, 1]

```
INPUT: 2 1

INDEXING:
  Sorted: [1, 2]
  2 → index 1
  1 → index 0
  Stack A: [2(1), 1(0)]

SIZE CHECK:
  size = 2, so call sort_two()

SORT_TWO:
  Stack A: [2(1), 1(0)]
  
  Is sorted? 
    2 > 1? Yes, not sorted
  
  Execute: sa (swap)
  
  Stack A: [1(0), 2(1)] ✓ SORTED!

OUTPUT: sa
```

---

### Another Example: Sorting [1, 3, 2]

```
INPUT: 1 3 2

INDEXING:
  Sorted: [1, 2, 3]
  1 → index 0
  3 → index 2
  2 → index 1
  Stack A: [1(0), 3(2), 2(1)]

SIZE CHECK:
  size = 3, so call sort_three()

SORT_THREE:
  a = 1(0)
  b = 3(2)
  c = 2(1)
  
  Check patterns:
    b < a && a < c?  → 3<1? NO
    c < b && b < a?  → 2<3 && 3<1? NO
    a < c && c < b?  → 1<2 && 2<3? YES ✓
  
  Execute: rra (rotate down), then sa (swap)
  
  After rra:
    Stack: [2(1), 1(0), 3(2)]
  
  After sa:
    Stack: [1(0), 2(1), 3(2)] ✓ SORTED!

OUTPUT: rra, sa
```

---

## Visual Comparison: Different Input Sizes

### Size 2
```
Pattern: Already sorted or 1 swap (sa)
Example: [3, 1]
         → sa → [1, 3]
Operations: 0-1
```

### Size 3  
```
Pattern: 6 possible arrangements, each needs 0-3 operations
Example: [3, 2, 1]
         → Pattern matching in sort_three()
         → Optimal sequence of 2-3 ops
Operations: 0-3
```

### Size 4-5
```
Pattern: Push smallest(s) to B, sort remaining 3, push back
Example: [5, 4, 3, 2, 1]
         pb → B=[5], A=[4,3,2,1]
         pb → B=[5,4], A=[3,2,1]
         sort_three(A)
         pa, pa → back to A
Operations: ~5-10
```

### Size 6-100
```
Pattern: Partition at median, push half to B
         Sort top 3 in A
         Intelligently insert from B one by one
         Final rotation
         
Example with n=8:
- Push 5 to B: ~5 pb
- Sort 3 in A: 0-3 ops
- Insert 5 greedily: ~25 ops
- Final rotation: 0-4 ops
Total: ~30-40 operations
Operations: ~5n
```

### Size 100+
```
Pattern: Same as above, but with larger cache effects
Optimization: Larger partition coefficient beneficial
         
Example with n=100:
- Push cards intelligently: ~50 pb
- Sort top 3: 0-3 ops  
- Insert 97 greedily: ~500 ops
- Final rotation: 0-50 ops
Total: ~550 operations (~5.5n)
Operations: ~5-11n (depending on initial distribution)
```

---

## Summary of Each Helper Function's Role

```
┌─────────────────────────────────────────────────────┐
│            INDEXING PHASE                           │
├─────────────────────────────────────────────────────┤
│ ft_copy_to_arr()          → Extract values to array │
│ ft_sort_arr()             → Sort array (bubble)     │
│ ft_assign_index_to_each   → Map value → index       │
│ ft_index_stack()          → Orchestrate 3 above    │
└─────────────────────────────────────────────────────┘

┌─────────────────────────────────────────────────────┐
│            POSITIONING PHASE                        │
├─────────────────────────────────────────────────────┤
│ ft_set_pos()              → Update pos field        │
│ ft_get_min_pos()          → Find pos of min index   │
│ ft_set_target_pos()       → Find insertion points   │
└─────────────────────────────────────────────────────┘

┌─────────────────────────────────────────────────────┐
│            COST CALCULATION PHASE                   │
├─────────────────────────────────────────────────────┤
│ ft_set_costs()            → Calculate cost_a/b      │
│ ft_get_cheapest()         → Find min cost element   │
└─────────────────────────────────────────────────────┘

┌─────────────────────────────────────────────────────┐
│            EXECUTION PHASE                          │
├─────────────────────────────────────────────────────┤
│ ft_rotate_both()          → Optimize simultaneous   │
│ ft_rotate_a()             → Handle stack A          │
│ ft_rotate_b()             → Handle stack B          │
│ ft_excute_all()           → Unified execution       │
│ ft_final_rotation()       → Position minimum       │
│ ft_sort_large()           → Main orchestrator      │
└─────────────────────────────────────────────────────┘

┌─────────────────────────────────────────────────────┐
│            VALIDATION PHASE                         │
├─────────────────────────────────────────────────────┤
│ check_dup()               → Detect duplicates       │
│ is_sorted()               → Verify sorted state     │
│ find_min()                → Locate min element      │
│ find_index()              → Locate specific value   │
└─────────────────────────────────────────────────────┘
```

---

## Conclusion

This push_swap implementation uses a sophisticated combination of:
- **Data structure augmentation** (custom t_list with metadata)
- **Index normalization** (reducing comparison complexity)
- **Cost-based greedy algorithm** (optimal local decision making)
- **Operation optimization** (simultaneous moves)

The result is an efficient O(n²) sorting algorithm that produces near-optimal operation sequences for the push_swap problem.

The key to understanding this algorithm:
1. **Metadata fields** in nodes enable efficient decision-making
2. **Position tracking** allows pre-calculation of rotation costs
3. **Greedy selection** works because moves are independent
4. **Simultaneous operations** compound the savings
5. **Index normalization** makes comparisons universal

Now you understand not just *what* the algorithm does, but *why* each helper function exists and *how* it contributes to the overall efficiency!
