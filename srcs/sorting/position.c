/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   position.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bakh <mel-bakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 17:42:16 by mel-bakh          #+#    #+#             */
/*   Updated: 2026/02/18 19:10:11 by mel-bakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

// int get_position(t_stack *stack)
// {
//     int i = 0 ;
//     i = 0 ; 
//     while (stack)
//     {
//         stack->pos = i ;
//         i++ ; 
//         stack = stack->next ; 
//     }
    
//     return i ; 
// }

// int get_lowest_pos(t_stack *stack)
// {
//     int low_value = stack->value ; 
//     int low_pos = stack->pos ; 

//     while (stack)
//     {
//         if ( stack->value < low_value)
//         {
//             low_value = stack->value ; 
//             low_pos = stack->pos ; 
//         }

//         stack = stack->next ; 
//     }
    
//     return (low_pos) ; 

// }

// int get_high_pos(t_stack *stack)
// {
//     int high_value = stack->value ; 
//     int high_pos = stack->pos ; 

//     while (stack)
//     {
//         if ( stack->value > high_value)
//         {
//             high_value = stack->value ; 
//             high_pos = stack->pos ; 
//         }

//         stack = stack->next ; 
//     }
    
//     return (high_pos) ; 

// }

void assign_position(t_stack *stack)
{
	int i = 0 ; 
	while (stack)
	{
		stack->pos = i ; 
		i++;

		stack = stack->next ; 
	}
	
}


int get_lowest_pos(t_stack *stack)
{
	int low_value = stack->value ; 
	int low_pos = stack->pos ; 

	while (stack)
	{
		if (stack->value < low_value)
		{
			low_value = stack->value ; 
			low_pos = stack->pos ; 
		}
		stack = stack->next ; 
	}
	
	return low_pos ; 
}

int get_high_pos(t_stack *stack)
{
	int high_value = stack->value;
	int high_pos = stack->pos ;

	while(stack)
	{
		if (stack->value > high_value)
		{
			high_value = stack->value ; 
			high_pos = stack->pos ; 
		}
		stack = stack->next ; 
	}

	return high_pos ; 
}
