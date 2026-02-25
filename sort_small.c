/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bakh <mel-bakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 00:56:45 by mel-bakh          #+#    #+#             */
/*   Updated: 2026/02/25 02:29:21 by mel-bakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/push_swap.h"

void	sort_two(t_stack **stack)
{
	if ((*stack)->value > (*stack)->next->value)
		sa(stack);
}

void	sort_three(t_stack **stack)
{
	int	max;

	max = get_max_value(stack);
	if ((*stack)->value == max)
		ra(stack);
	else if ((*stack)->next->value == max)
		rra(stack);
	if ((*stack)->value > (*stack)->next->value)
		sa(stack);
}

void	sort_four(t_stack **stack_a, t_stack **stack_b)
{
	int	size;
	int	min_pos;
	int	min_value;

	assign_positions(*stack_a);
	size = stack_size(*stack_a);
	min_pos = get_lowest_pos(*stack_a);
	min_value = get_min_value(*stack_a);
	if (min_pos <= size / 2)
	{
		while ((*stack_a)->value != min_value)
			ra(stack_a);
	}
	else
	{
		while ((*stack_a)->value != min_value)
			rra(stack_a);
	}
	pb(stack_a, stack_b);
	sort_three(stack_a);
	pa(stack_a, stack_b);
}

void	sort_five(t_stack **stack_a, t_stack **stack_b)
{
	int	size;
	int	min_pos;
	int	min_value;

	assign_positions(*stack_a);
	size = stack_size(*stack_a);
	min_pos = get_lowest_pos(*stack_a);
	min_value = get_min_value(*stack_a);
	if (min_pos <= size / 2)
	{
		while ((*stack_a)->value != min_value)
			ra(stack_a);
	}
	else
	{
		while ((*stack_a)->value != min_value)
			rra(stack_a);
	}
	pb(stack_a, stack_b);
	sort_four(stack_a, stack_b);
	pa(stack_a, stack_b);
}
