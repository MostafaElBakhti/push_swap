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

static int	execute_instruction(char *line, t_list **a, t_list **b)
{
	int	len;

	len = strlen_bonus(line);
	while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r'))
	{
		line[len - 1] = '\0';
		len--;
	}
	if (swap_bonus(a, b, line))
		return (1);
	if (rotate_bonus(a, b, line))
		return (1);
	return (0);
}

static void	read_and_execute(t_list **a, t_list **b)
{
	char	*line;

	line = get_next_line(0);
	while (line)
	{
		if (!execute_instruction(line, a, b))
		{
			free(line);
			free_stack_bonus(a);
			free_stack_bonus(b);
			error_exit_b();
		}
		free(line);
		line = get_next_line(0);
	}
}

int	main(int argc, char **argv)
{
	t_list	*a;
	t_list	*b;

	if (argc < 2)
		return (0);
	a = NULL;
	b = NULL;
	parse_args(argc, argv, &a);
	read_and_execute(&a, &b);
	if (is_sorted_bonus(a) && b == NULL)
		write(1, "OK\n", 3);
	else
		write(1, "KO\n", 3);
	free_stack_bonus(&a);
	free_stack_bonus(&b);
	return (0);
}
