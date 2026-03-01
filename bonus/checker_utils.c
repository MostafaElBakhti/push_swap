/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bakh <mel-bakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 15:36:15 by mel-bakh          #+#    #+#             */
/*   Updated: 2026/02/26 15:36:15 by mel-bakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

static void	pa_checker(t_list **stack_a, t_list **stack_b)
{
	t_list	*tmp;

	if (!stack_b || !*stack_b)
		return ;
	tmp = *stack_b;
	*stack_b = tmp->next;
	tmp->next = *stack_a;
	*stack_a = tmp;
}

static void	pb_checker(t_list **stack_a, t_list **stack_b)
{
	t_list	*tmp;

	if (!stack_a || !*stack_a)
		return ;
	tmp = *stack_a;
	*stack_a = tmp->next;
	tmp->next = *stack_b;
	*stack_b = tmp;
}

int	swap_bonus(t_list **a, t_list **b, char *line)
{
	if (ft_strcmp(line, "sa") == 0)
		swap_stack_bonus(a);
	else if (ft_strcmp(line, "sb") == 0)
		swap_stack_bonus(b);
	else if (ft_strcmp(line, "ss") == 0)
	{
		swap_stack_bonus(a);
		swap_stack_bonus(b);
	}
	else if (ft_strcmp(line, "pa") == 0)
		pa_checker(a, b);
	else if (ft_strcmp(line, "pb") == 0)
		pb_checker(a, b);
	else
		return (0);
	return (1);
}

int	rotate_bonus(t_list **a, t_list **b, char *line)
{
	if (ft_strcmp(line, "ra") == 0)
		ro_bonus(a);
	else if (ft_strcmp(line, "rb") == 0)
		ro_bonus(b);
	else if (ft_strcmp(line, "rr") == 0)
	{
		ro_bonus(a);
		ro_bonus(b);
	}
	else if (ft_strcmp(line, "rra") == 0)
		rro_bonus(a);
	else if (ft_strcmp(line, "rrb") == 0)
		rro_bonus(b);
	else if (ft_strcmp(line, "rrr") == 0)
	{
		rro_bonus(a);
		rro_bonus(b);
	}
	else
		return (0);
	return (1);
}
