/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bakh <mel-bakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 01:41:36 by mel-bakh          #+#    #+#             */
/*   Updated: 2026/02/24 01:57:17 by mel-bakh         ###   ########.fr       */
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

static void	execute_instruction(char *line, t_stack **a, t_stack **b)
{
	int len;

	if (!line)
		error_exit();
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
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
	else if (ft_strcmp(line, "ra") == 0)
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

int	main(int argc, char **argv)
{
	t_stack	*a;
	t_stack	*b;
	char	*line;

	if (argc < 2)
		return (0);
	a = NULL;
	b = NULL;
	parse_arguments(argc, argv, &a);
	line = get_next_line(0);
	while (line)
	{
		execute_instruction(line, &a, &b);
		free(line);
		line = get_next_line(0);
	}
	if (is_sorted(a) && b == NULL)
		write(1, "OK\n", 3);
	else
		write(1, "KO\n", 3);
	free_stack(&a);
	free_stack(&b);
	return (0);
}
