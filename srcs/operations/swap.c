/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bakh <mel-bakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 00:01:48 by mel-bakh          #+#    #+#             */
/*   Updated: 2026/02/05 00:01:48 by mel-bakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

static void	swap_stack(t_stack **stack)
{
	t_stack	*first;
	t_stack	*second;

	if (!stack || !*stack || (*stack)->next == NULL)
		return;

	first = *stack;
	second = first->next;

	first->next = second->next;
	second->next = first;
	*stack = second;
}
void sa(t_stack **stack_a)
{
	swap_stack(stack_a);
	write(1, "sa\n", 3);
}

void sb(t_stack **stack_b)
{
	swap_stack(stack_b);
	write(1, "sb\n", 3);
}
void ss(t_stack **a, t_stack **b)
{
	swap_stack(a);
	swap_stack(b);
	write(1, "ss\n", 3);
}
