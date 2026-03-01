/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bakh <mel-bakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 14:51:27 by mel-bakh          #+#    #+#             */
/*   Updated: 2026/02/27 14:51:27 by mel-bakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

static void	add_number_to_stack_bonus(t_list **stack, char *str)
{
	long long	num;
	t_list		*new_node;

	if (is_valid_number_bonus(str) == 0)
		error_exit_b();
	num = ft_atol_bonus(str);
	if (num > INT_MAX || num < INT_MIN)
		error_exit_b();
	new_node = stack_new_bonus((int)num);
	if (!new_node)
		error_exit_b();
	stack_add_back_bonus(stack, new_node);
}

static void	process_split_bonus(char **split, t_list **stack)
{
	int	j;

	if (!split || !split[0])
		error_exit_b();
	j = 0;
	while (split[j])
	{
		add_number_to_stack_bonus(stack, split[j]);
		free(split[j]);
		j++;
	}
	free(split);
}

t_list	*parse_args(int argc, char **argv, t_list **stack)
{
	int		i;
	char	**split;

	i = 1;
	while (i < argc)
	{
		split = ft_split_bonus(argv[i], ' ');
		process_split_bonus(split, stack);
		i++;
	}
	if (has_duplicates_bonus(*stack))
	{
		free_stack_bonus(stack);
		error_exit_b();
	}
	return (*stack);
}
