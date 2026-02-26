/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bakh <mel-bakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 17:50:00 by mel-bakh          #+#    #+#             */
/*   Updated: 2026/02/23 17:50:00 by mel-bakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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

int	get_min_value(t_stack *stack)
{
	int	min;

	min = stack->value;
	while (stack)
	{
		if (stack->value < min)
			min = stack->value;
		stack = stack->next;
	}
	return (min);
}

int	get_max_value(t_stack **stack)
{
	int		max;
	t_stack	*current;

	max = (*stack)->value;
	current = *stack;
	while (current)
	{
		if (current->value > max)
			max = current->value;
		current = current->next;
	}
	return (max);
}
