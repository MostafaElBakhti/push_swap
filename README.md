*This project has been created as part of the 42 curriculum by mostafa.*

## Description
**Push_swap** is a 42 algorithm project whose goal is to sort data on a stack, with a limited set of instructions, using the lowest possible number of operations. 

### The Algorithm (Turk Algorithm)
This project is powered by the **Turk Algorithm**, designed to be highly efficient by calculating the cheapest moves. Here is a clean overview of how it works:

1. **Push to Stack B**: We continuously push nodes from Stack A to Stack B until only 3 remain in A. For every move, we calculate the "cost" (number of rotations required) to move each node from A into its correct descending spot in B. We always execute the cheapest move.
2. **Sort Stack A**: The remaining 3 elements in Stack A are sorted using a simple, hardcoded minimum-operation sort.
3. **Push back to Stack A**: We push nodes from Stack B back to Stack A. For each node in B, we find its correct target position in A, rotate A accordingly, and push it on top.
4. **Final Alignment**: We rotate Stack A one last time to ensure the absolute smallest number ends up at the very top, completing the sort.

## Instructions
### Compilation
To compile the program, run the `make` command at the root of the repository:
```bash
make
```
*(Optionally, use `make bonus` to compile the checker program if available).*

### Execution
Run the compiled executable by passing a list of integers as arguments:
```bash
./push_swap 4 67 3 87 23
```

To verify the output using the checker (if compiled):
```bash
ARG="4 67 3 87 23"; ./push_swap $ARG | ./checker $ARG
```

## Resources
- [Push_swap - 42 Docs](https://harm-smits.github.io/42docs/projects/push_swap)
- [The Turk Algorithm (A. Yogun)](https://medium.com/@ayogun/push-swap-c1f5d2d41e97)

### AI Usage Statement
AI tools were used during the development of this project for the following tasks:
- **Algorithm Optimization**: Debugging the Turk algorithm's rotation costs to ensure the lowest possible number of operations.
- **Code Formatting**: Refactoring project files and assisting with strict 42 Norminette compliance (fixing indentation, variable alignment, and function length limits).
- **Understanding Concepts**: Explaining implications of file descriptors in C and how `stderr` is utilized for standard error handling within the 42 school requirements.
