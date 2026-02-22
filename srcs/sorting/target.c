/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   target.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bakh <mel-bakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 13:35:16 by mel-bakh          #+#    #+#             */
/*   Updated: 2026/02/18 18:20:27 by mel-bakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

// int find_target_b(t_stack *stack_b , int value)
// {
//     t_stack *current = stack_b ;
//     int     clos_larger ; 
//     int     target_pos = 0 ; 
//     clos_larger = INT_MAX ; 
//     while (current)
//     {
//         if ( current->value > value && current->value < clos_larger)
//         {
//             clos_larger = current->value ; 
//             target_pos = current->pos ; 
//         }
//         current = current->next ; 
//     }
//     if ( clos_larger == INT_MAX)
//         target_pos = get_lowest_pos(stack_b) ; 
    
//     return target_pos ; 
// }   

void assign_targets_b(t_stack *stack_a,t_stack *stack_b)
{

    assign_positions(stack_b) ; 

    while (stack_a)
    {
        stack_a->target_pos = find_target_b(stack_b,stack_a->value);
        stack_a = stack_a->next ;
    }
    
}



int find_target_b(t_stack *stack_b, int index)
{
	t_stack	*head;
	int		closest_smaller;
	int		target_pos;
	
	if (!stack_b)
	return (0);
	head = stack_b;
	closest_smaller = INT_MIN;
	target_pos = 0;
	
	while (stack_b)
	{
		if (stack_b->index < index && stack_b->index > closest_smaller)
		{
			closest_smaller = stack_b->index;
			target_pos = stack_b->pos;
		}
		stack_b = stack_b->next;
	}

	if (closest_smaller == INT_MIN)
	{
		target_pos = get_highest_pos(head);
	}
	
	return target_pos;
}

int	find_target_a(t_stack *stack_a, int index)
{
	int		target_pos;
	t_stack	*current;
	int		smallest_larger;

	smallest_larger = INT_MAX;
	current = stack_a;

	while (current)
	{
		if (current->index > index && current->index < smallest_larger)
		{
			smallest_larger = current->index;
			target_pos = current->pos;
		}
		current = current->next;
	}
	if (smallest_larger == INT_MAX)
		target_pos = get_lowest_pos(stack_a);
	return (target_pos);
}

void assign_target_pos(t_stack *stack_a, t_stack *stack_b)
{
	while (stack_b)
	{
		stack_b->target_pos = find_target_a(stack_a, stack_b->index);
		stack_b = stack_b->next;
	}
}