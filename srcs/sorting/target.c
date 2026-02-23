/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   target.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bakh <mel-bakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 13:35:16 by mel-bakh          #+#    #+#             */
/*   Updated: 2026/02/18 18:20:27 by mel-bakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

int	find_target_a(t_stack *stack_a, int index)
{
	int		target_pos;
	t_stack	*current;
	int		smallest_larger;

	smallest_larger = INT_MAX;
	current = stack_a;


	while (current)
	{
		if (current->index > index && current->index < smallest_larger)
		{
			smallest_larger = current->index;
			target_pos = current->pos;
		}
		current = current->next;
	}
	if (smallest_larger == INT_MAX)
		target_pos = get_lowest_pos(stack_a);
	return (target_pos);
}

void assign_target_pos(t_stack *stack_a, t_stack *stack_b)
{
	while (stack_b)
	{
		stack_b->target_pos = find_target_a(stack_a, stack_b->index);
		stack_b = stack_b->next;
	}
}
