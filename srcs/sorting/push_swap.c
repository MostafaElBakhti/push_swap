/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bakh <mel-bakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 21:22:09 by mel-bakh          #+#    #+#             */
/*   Updated: 2026/02/18 21:22:09 by mel-bakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

void	push_swap(t_stack **stack_a, t_stack **stack_b)
{
	int	size;

	size = stack_size(*stack_a);
	if (size <= 1 || is_sorted(*stack_a))
		return ;
	if (size == 2)
		sort_two(stack_a);
	else if (size == 3)
		sort_three(stack_a);
	else if (size == 4)
		sort_four(stack_a, stack_b);
	else if (size == 5)
		sort_five(stack_a, stack_b);
	else
		sort_turk(stack_a, stack_b);
}
