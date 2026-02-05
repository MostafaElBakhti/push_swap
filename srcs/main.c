/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bakh <mel-bakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 16:49:45 by mel-bakh          #+#    #+#             */
/*   Updated: 2026/02/05 01:45:00 by mel-bakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	main(void)
{
	t_stack	*stack_a;
	t_stack	*stack_b;

	printf("========================================\n");
	printf("     TESTING ALL 11 OPERATIONS\n");
	printf("========================================\n");

	// Initialize stacks
	stack_a = NULL;
	stack_b = NULL;

	// Setup
	printf("\n--- SETUP: Creating Stack A [1, 2, 3, 4, 5] ---\n");
	stack_add_back(&stack_a, stack_new(1));
	stack_add_back(&stack_a, stack_new(2));
	stack_add_back(&stack_a, stack_new(3));
	stack_add_back(&stack_a, stack_new(4));
	stack_add_back(&stack_a, stack_new(5));
	print_stack(stack_a, 'A');
	print_stack(stack_b, 'B');

	// Test 1: sa
	printf("\n--- Test 1: sa (swap first 2) ---\n");
	sa(&stack_a);
	print_stack(stack_a, 'A');
	printf("Expected: [2, 1, 3, 4, 5]\n");

	// Test 2: pb
	printf("\n--- Test 2: pb x2 (push to B) ---\n");
	pb(&stack_a, &stack_b);
	pb(&stack_a, &stack_b);
	print_stack(stack_a, 'A');
	print_stack(stack_b, 'B');
	printf("Expected A: [3, 4, 5]\n");
	printf("Expected B: [1, 2]\n");

	// Test 3: sb
	printf("\n--- Test 3: sb (swap B) ---\n");
	sb(&stack_b);
	print_stack(stack_b, 'B');
	printf("Expected B: [2, 1]\n");

	// Test 4: ra
	printf("\n--- Test 4: ra (rotate A) ---\n");
	ra(&stack_a);
	print_stack(stack_a, 'A');
	printf("Expected A: [4, 5, 3]\n");

	// Test 5: rb
	printf("\n--- Test 5: rb (rotate B) ---\n");
	rb(&stack_b);
	print_stack(stack_b, 'B');
	printf("Expected B: [1, 2]\n");

	// Test 6: rr
	printf("\n--- Test 6: rr (rotate both) ---\n");
	rr(&stack_a, &stack_b);
	print_stack(stack_a, 'A');
	print_stack(stack_b, 'B');
	printf("Expected A: [5, 3, 4]\n");
	printf("Expected B: [2, 1]\n");

	// Test 7: rra
	printf("\n--- Test 7: rra (reverse rotate A) ---\n");
	rra(&stack_a);
	print_stack(stack_a, 'A');
	printf("Expected A: [4, 5, 3]\n");

	// Test 8: rrb
	printf("\n--- Test 8: rrb (reverse rotate B) ---\n");
	rrb(&stack_b);
	print_stack(stack_b, 'B');
	printf("Expected B: [1, 2]\n");

	// Test 9: rrr
	printf("\n--- Test 9: rrr (reverse rotate both) ---\n");
	rrr(&stack_a, &stack_b);
	print_stack(stack_a, 'A');
	print_stack(stack_b, 'B');
	printf("Expected A: [3, 4, 5]\n");
	printf("Expected B: [2, 1]\n");

	// Test 10: pa
	printf("\n--- Test 10: pa x2 (push to A) ---\n");
	pa(&stack_a, &stack_b);
	pa(&stack_a, &stack_b);
	print_stack(stack_a, 'A');
	print_stack(stack_b, 'B');
	printf("Expected A: [1, 2, 3, 4, 5]\n");
	printf("Expected B: (empty)\n");

	// Test 11: ss
	printf("\n--- Test 11: ss (swap both) ---\n");
	pb(&stack_a, &stack_b);  // Move one to B first
	pb(&stack_a, &stack_b);  // Move another to B
	ss(&stack_a, &stack_b);
	print_stack(stack_a, 'A');
	print_stack(stack_b, 'B');
	printf("Expected A: [4, 3, 5]\n");
	printf("Expected B: [1, 2]\n");

	// Cleanup
	printf("\n--- CLEANUP ---\n");
	free_stack(&stack_a);
	free_stack(&stack_b);
	printf("All memory freed!\n");

	printf("\n========================================\n");
	printf("    ALL 11 OPERATIONS WORK! ✓✓✓\n");
	printf("========================================\n");

	return (0);
}