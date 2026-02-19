/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_turk.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bakh <mel-bakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 03:00:00 by mel-bakh          #+#    #+#             */
/*   Updated: 2026/02/18 21:22:09 by mel-bakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

int	get_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

t_stack	*get_cheapest(t_stack *stack_a)
{
	t_stack	*current;
	t_stack	*cheapest;
	int		lowest_cost;
	int		total_cost;

	current = stack_a;
	cheapest = stack_a;
	lowest_cost = INT_MAX;
	while (current)
	{
		total_cost = get_abs(current->cost_a) + get_abs(current->cost_b);
		if (total_cost < lowest_cost)
		{
			lowest_cost = total_cost;
			cheapest = current;
		}
		current = current->next;
	}
	return (cheapest);
}

void	do_rotate(t_stack **stack, int cost, char stack_name)
{
	if (cost > 0)
	{
		while (cost > 0)
		{
			if (stack_name == 'a')
				ra(stack);
			else if (stack_name == 'b')
				rb(stack);
			cost--;
		}
	}
	else if (cost < 0)
	{
		while (cost < 0)
		{
			if (stack_name == 'a')
				rra(stack);
			else if (stack_name == 'b')
				rrb(stack);
			cost++;
		}
	}
}

void	push_back_to_a(t_stack **stack_a, t_stack **stack_b)
{
	int	target_pos;
	int	size_a;

	while (*stack_b)
	{
		assign_positions(*stack_a);
		/*
		** find_target_a returns the position of the largest element in
		** stack_a that is smaller than the value being pushed back.
		** Adding 1 (mod size_a) gives the position of the element that
		** should sit just below the new node after pa.  When the result
		** wraps to 0 the new element belongs at the top – no rotation.
		*/
		target_pos = find_target_a(*stack_a, (*stack_b)->value);
		size_a = stack_size(*stack_a);
		target_pos = (target_pos + 1) % size_a;
		if (target_pos <= size_a / 2)
		{
			while (target_pos-- > 0)
				ra(stack_a);
		}
		else
		{
			target_pos = size_a - target_pos;
			while (target_pos-- > 0)
				rra(stack_a);
		}
		pa(stack_a, stack_b);
	}
}

static void	rotate_to_min(t_stack **stack_a)
{
	int	min_pos;
	int	size;

	assign_positions(*stack_a);
	min_pos = get_lowest_pos(*stack_a);
	size = stack_size(*stack_a);
	if (min_pos <= size / 2)
	{
		while (min_pos-- > 0)
			ra(stack_a);
	}
	else
	{
		min_pos = size - min_pos;
		while (min_pos-- > 0)
			rra(stack_a);
	}
}

void	sort_turk(t_stack **stack_a, t_stack **stack_b)
{
	if (stack_size(*stack_a) > 5)
	{
		pb(stack_a, stack_b);
		pb(stack_a, stack_b);
	}
	while (stack_size(*stack_a) > 3)
	{
		calculate_costs(*stack_a, *stack_b);
		execute_cheapest(stack_a, stack_b);
	}
	sort_three(stack_a);
	push_back_to_a(stack_a, stack_b);
	rotate_to_min(stack_a);
}

