/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cost.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bakh <mel-bakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 17:52:49 by mel-bakh          #+#    #+#             */
/*   Updated: 2026/02/18 01:45:42 by mel-bakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	calculate_cost_a(t_stack *stack_a)
{
	int			size_a;

	size_a = stack_size(stack_a);
	while (stack_a)
	{
		stack_a->cost_a = stack_a->pos;
		if (stack_a->pos > size_a / 2)
			stack_a->cost_a = (size_a - stack_a->pos) * -1;
		stack_a = stack_a->next;
	}
}

void	calculate_cost_b(t_stack *stack_a, t_stack *stack_b)
{
	int	size_b;

	size_b = stack_size(stack_b);
	while (stack_a)
	{
		stack_a->cost_b = stack_a->target_pos;
		if (stack_a->target_pos > size_b / 2)
			stack_a->cost_b = (size_b - stack_a->target_pos) * -1;
		stack_a = stack_a->next;
	}
}

void	calculate_costs(t_stack *stack_a, t_stack *stack_b)
{
	int	size_a;
	int	size_b;

	size_a = stack_size(stack_a);
	size_b = stack_size(stack_b);
	while (stack_b)
	{
		if (stack_b->target_pos <= size_a / 2)
			stack_b->cost_a = stack_b->target_pos;
		else
			stack_b->cost_a = stack_b->target_pos - size_a;
		if (stack_b->pos <= size_b / 2)
			stack_b->cost_b = stack_b->pos;
		else
			stack_b->cost_b = stack_b->pos - size_b;
		stack_b = stack_b->next;
	}
}

void	push_cheapest(t_stack **a, t_stack **b)
{
	t_stack	*node;
	int		ca;
	int		cb;

	node = get_cheapest(*b);
	ca = node->cost_a;
	cb = node->cost_b;
	ft_rotate_both(a, b, &ca, &cb);
	ft_rotate_a(a, &ca);
	ft_rotate_b(b, &cb);
	pa(a, b);
}
