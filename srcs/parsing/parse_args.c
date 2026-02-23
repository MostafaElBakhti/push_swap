/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bakh <mel-bakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 22:05:19 by mel-bakh          #+#    #+#             */
/*   Updated: 2026/02/21 01:00:00 by mel-bakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

static void add_number_to_stack(t_stack **stack, char *str)
{
	long long num;
	t_stack *new_node;
	if (is_valid_number(str) == 0)
	{
		error_exit();
	}

	num = ft_atol(str);
	if (num > INT_MAX || num < INT_MIN)
		error_exit();

	new_node = stack_new((int)num);
	stack_add_back(stack, new_node);
}

t_stack *parse_arguments(int argc, char **argv, t_stack **stack)
{
	int i;
	int j;
	char **split;

	i = 1;
	while (i < argc)
	{
		split = ft_split(argv[i], ' ');
		if (!split || !split[0])
			error_exit();
		j = 0;
		while (split[j])
		{
			add_number_to_stack(stack, split[j]);
			free(split[j]);
			j++;
		}
		free(split) ;
		i++;
	}
    if (has_duplicates(*stack))
    {
        free_stack(stack);
        error_exit();
    }
	return (*stack);
}
