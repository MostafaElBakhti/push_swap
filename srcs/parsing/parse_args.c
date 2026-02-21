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

static void add_number_to_stack(t_stack **stack , char *str)
{   
    long long num ; 
    t_stack *new_node ;
    if (is_valid_number(str) == 0)
    {
        error_exit() ; 
    }

    num = ft_atol(str) ; 
    if (num > INT_MAX || num < INT_MIN)
        error_exit();
        
    new_node = stack_new((int)num) ; 
    stack_add_back(stack , new_node) ; 
}

static void	parse_split_string(t_stack **stack, char *str)
{
	char	**args;
	int		i;

	args = ft_split(str);
	if (!args)
		error_exit();
	i = 0;
	while (args[i])
	{
		add_number_to_stack(stack, args[i]);
		free(args[i]);
		i++;
	}
	free(args);
}

t_stack	*parse_arguments(int argc, char **argv)
{
	t_stack	*stack;
	int		i;

	stack = NULL;

	if (argc == 2)
		parse_split_string(&stack, argv[1]);
	else
	{
		i = 1 ;
		while (i < argc)
		{
			add_number_to_stack(&stack, argv[i]);
			i++;
		}
	}
    
    if ( has_duplicates(stack) == 1 )
    {
        free_stack(&stack);
        error_exit() ;
    }

    return stack ; 
}