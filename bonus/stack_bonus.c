/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bakh <mel-bakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 16:55:28 by mel-bakh          #+#    #+#             */
/*   Updated: 2026/02/27 16:55:28 by mel-bakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*stack_new_bonus(int value)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->value = value;
	new->next = NULL;
	return (new);
}
void	stack_add_back_bonus(t_list **stack, t_list *new_node)
{
	t_list	*tmp;

	if (!stack || !new_node)
		return ;
	if (*stack == NULL)
	{
		*stack = new_node;
		return ;
	}
	tmp = *stack;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
}
// void	swap_stack(t_list **stack)
// {
// 	t_list	*first;
// 	t_list	*second;

// 	if (!stack || !*stack || (*stack)->next == NULL)
// 		return ;
// 	first = *stack;
// 	second = first->next;
// 	first->next = second->next;
// 	second->next = first;
// 	*stack = second;
// }
void	error_exit_bonus(t_list **a, t_list **b)
{
	if (a)
		free_stack_bonus(a);
	if (b)
		free_stack_bonus(b);
	write(2, "Error\n", 6);
	exit(1);
}