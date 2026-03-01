/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_bonus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bakh <mel-bakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 14:43:14 by mel-bakh          #+#    #+#             */
/*   Updated: 2026/02/27 14:43:14 by mel-bakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void	swap_stack_bonus(t_list **stack)
{
	t_list	*first;
	t_list	*second;

	if (!stack || !*stack || (*stack)->next == NULL)
		return ;
	first = *stack;
	second = first->next;
	first->next = second->next;
	second->next = first;
	*stack = second;
}

void	ro_bonus(t_list **stack)
{
	t_list	*first;
	t_list	*last;

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

void	rro_bonus(t_list **stack)
{
	t_list	*last;
	t_list	*before_last;

	if (!stack || !*stack || (*stack)->next == NULL)
		return ;
	before_last = *stack;
	while (before_last->next->next != NULL)
		before_last = before_last->next;
	last = before_last->next;
	before_last->next = NULL;
	last->next = *stack;
	*stack = last;
}
