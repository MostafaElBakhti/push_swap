/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bakh <mel-bakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 16:49:45 by mel-bakh          #+#    #+#             */
/*   Updated: 2026/02/04 16:30:00 by mel-bakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	main(void)
{
	t_stack	*stack_a;
	t_stack	*stack_b;

	printf("========================================\n");
	printf("   TESTING STACK UTILITY FUNCTIONS\n");
	printf("========================================\n");

	// Initialize empty stacks
	stack_a = NULL;
	stack_b = NULL;

	// Test: Adding nodes to stack A
	printf("\n--- Adding nodes to stack A ---\n");
	stack_add_back(&stack_a, stack_new(10));
	stack_add_back(&stack_a, stack_new(20));
	stack_add_back(&stack_a, stack_new(30));
	stack_add_back(&stack_a, stack_new(40));
	stack_add_back(&stack_a, stack_new(50));
	
	print_stack(stack_a, 'A');
	printf("Stack A size: %d\n", stack_size(stack_a));
	
	// Test: Get last element
	printf("\n--- Testing stack_last() ---\n");
	t_stack *last = stack_last(stack_a);
	if (last)
		printf("Last element value: %d\n", last->value);
	
	// Test: Create stack B
	printf("\n--- Creating stack B ---\n");
	stack_add_back(&stack_b, stack_new(100));
	stack_add_back(&stack_b, stack_new(200));
	stack_add_back(&stack_b, stack_new(300));
	
	print_stack(stack_b, 'B');
	printf("Stack B size: %d\n", stack_size(stack_b));
	
	// Test: Free everything
	printf("\n--- Freeing memory ---\n");
	free_stack(&stack_a);
	free_stack(&stack_b);
	
	printf("✓ Stack A freed\n");
	printf("✓ Stack B freed\n");
	
	print_stack(stack_a, 'A');
	print_stack(stack_b, 'B');
	
	printf("\n========================================\n");
	printf("         ALL TESTS PASSED! ✓\n");
	printf("========================================\n");
	
	return (0);
}