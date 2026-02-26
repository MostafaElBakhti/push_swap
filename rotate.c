/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bakh <mel-bakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 00:54:20 by mel-bakh          #+#    #+#             */
/*   Updated: 2026/02/05 00:54:20 by mel-bakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ro(t_stack **stack)
{
	t_stack	*first;
	t_stack	*last;

	if (!stack || !*stack || (*stack)->next == NULL)
		return ;
	first = *stack;
	(*stack) = first->next;
	first->next = NULL;
	last = *stack;
	while (last->next != NULL)
		last = last->next;
	last->next = first;
}

void	ra(t_stack **stack_a)
{
	ro(stack_a);
	write(1, "ra\n", 3);
}

void	rb(t_stack **stack_b)
{
	ro(stack_b);
	write(1, "rb\n", 3);
}

void	rr(t_stack **a, t_stack **b)
{
	ro(a);
	ro(b);
	write(1, "rr\n", 3);
}
