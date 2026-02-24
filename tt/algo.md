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

## Example Walkthrough

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

## Conclusion

This push_swap implementation uses a sophisticated combination of:
- **Data structure augmentation** (custom t_list with metadata)
- **Index normalization** (reducing comparison complexity)
- **Cost-based greedy algorithm** (optimal local decision making)
- **Operation optimization** (simultaneous moves)

The result is an efficient O(n²) sorting algorithm that produces near-optimal operation sequences for the push_swap problem.
