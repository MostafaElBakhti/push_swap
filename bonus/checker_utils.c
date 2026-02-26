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

#include "get_next_line.h"
#include "../includes/push_swap.h"

static int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

static void	pa_checker(t_stack **stack_a, t_stack **stack_b)
{
	t_stack	*tmp;

	if (!stack_b || !*stack_b)
		return ;
	tmp = *stack_b;
	*stack_b = tmp->next;
	tmp->next = *stack_a;
	*stack_a = tmp;
}

static void	pb_checker(t_stack **stack_a, t_stack **stack_b)
{
	t_stack	*tmp;

	if (!stack_a || !*stack_a)
		return ;
	tmp = *stack_a;
	*stack_a = tmp->next;
	tmp->next = *stack_b;
	*stack_b = tmp;
}

static void checker_swap(t_stack **a, t_stack **b, char *line)
{
	if (ft_strcmp(line, "sa") == 0)
		swap_stack(a);
	else if (ft_strcmp(line, "sb") == 0)
		swap_stack(b);
	else if (ft_strcmp(line, "ss") == 0)
	{
		swap_stack(a);
		swap_stack(b);
	}
	else if (ft_strcmp(line, "pa") == 0)
		pa_checker(a, b);
	else if (ft_strcmp(line, "pb") == 0)
		pb_checker(a, b);
	else
	{
		free(line);
		error_exit();
	}
}
static void rotate_checker(t_stack **a, t_stack **b, char *line)
{
	if (ft_strcmp(line, "ra") == 0)
		ro(a);
	else if (ft_strcmp(line, "rb") == 0)
		ro(b);
	else if (ft_strcmp(line, "rr") == 0)
	{
		ro(a);
		ro(b);
	}
	else if (ft_strcmp(line, "rra") == 0)
		rro(a);
	else if (ft_strcmp(line, "rrb") == 0)
		rro(b);
	else if (ft_strcmp(line, "rrr") == 0)
	{
		rro(a);
		rro(b);
	}
	else
	{
		free(line);
		error_exit();
	}
}
