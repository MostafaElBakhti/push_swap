/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   position.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bakh <mel-bakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 17:42:16 by mel-bakh          #+#    #+#             */
/*   Updated: 2026/02/18 19:10:11 by mel-bakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	assign_positions(t_stack *stack)
{
	int	i;

	i = 0;
	while (stack)
	{
		stack->pos = i;
		i++;
		stack = stack->next;
	}
}

int	get_lowest_pos(t_stack *stack)
{
	int	low_index;
	int	low_pos;

	low_index = INT_MAX;
	low_pos = 0;
	while (stack)
	{
		if (stack->index < low_index)
		{
			low_index = stack->index;
			low_pos = stack->pos;
		}
		stack = stack->next;
	}
	return (low_pos);
}

int	get_highest_pos(t_stack *stack)
{
	int	high_value;
	int	high_pos;

	high_value = stack->value;
	high_pos = stack->pos;
	while (stack)
	{
		if (stack->value > high_value)
		{
			high_value = stack->value;
			high_pos = stack->pos;
		}
		stack = stack->next;
	}
	return (high_pos);
}
