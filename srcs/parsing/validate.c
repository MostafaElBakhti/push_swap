/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bakh <mel-bakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 21:17:25 by mel-bakh          #+#    #+#             */
/*   Updated: 2026/02/06 21:17:25 by mel-bakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

int is_valid_number(char *str)
{
    int i = 0 ; 

    if ( str == NULL || str[0] == '\0' )
        return 0 ; 
    
    while (ft_isspace(str[i]))
        i++;

    if (str[i] == '-' || str[i] == '+')
        i++ ; 
    
    if ( !(str[i] >= '0' && str[i] <= '9') )
        return 0 ;

    while ( str[i] )
    {
        if (!(str[i] >= '0' && str[i] <= '9'))
            return 0 ;
        i++;
    }

    return 1 ;
    
}

// current  checker
//    |        |
//   [3] ->   [1] -> [7] -> [1] -> NULL

int has_duplicates(t_stack *stack)
{
    t_stack *current ;
    t_stack *checker ; 

    current = stack ; 

    while (current)
    {
        checker = current->next ; 
        while (checker)
        {
            if ( current->value == checker->value)    
                return 1 ;
            checker = checker->next ; 
        }
        current = current->next ;   
    }
    return (0) ; 

}
int	is_sorted(t_stack *stack)
{
	if (!stack)
		return (1);
	
	while (stack->next)
	{
		if (stack->value > stack->next->value)
			return (0);
		stack = stack->next;
	}
	return (1);
}
void	error_exit(void)
{
	write(2, "Error\n", 6);
	exit(1);
}