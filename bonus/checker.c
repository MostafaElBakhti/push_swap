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

static void	execute_instruction(char *line, t_stack **a, t_stack **b)
{
	int len;

	if (!line)
		error_exit();
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	checker_swap(a, b, line);
	rotate_checker(a, b, line);
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
