/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bakh <mel-bakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 13:36:32 by mel-bakh          #+#    #+#             */
/*   Updated: 2026/02/11 13:36:32 by mel-bakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

void	swap_stack(t_stack **stack)
{
	t_stack	*first;
	t_stack	*second;

	if (!stack || !*stack || (*stack)->next == NULL)
		return;

	first = *stack;
	second = first->next;

	first->next = second->next;
	second->next = first;
	*stack = second;
}



void sort_two(t_stack **stack)
{
    if ( (*stack)->value > (*stack)->next->value )
    {
        (*stack)->next->next = (*stack) ;  
        (*stack) = (*stack)->next ;
        (*stack)->next = NULL ; 
    }
}

void ro(t_stack **stack)
{
	t_stack	*first;
	t_stack	*last;

    if (!stack || !*stack || (*stack)->next == NULL)
		return;
    
    first = *stack ;

    (*stack) = first->next ;
    first->next = NULL ;
    
    last = *stack ;
    while (last->next != NULL)
        last = last->next ;
    last->next = first ;
}

void sort_three(t_stack **stack)
{   
    int tmp = 0 ; 
    if((*stack)->value > (*stack)->next->value)
    {
        tmp = (*stack)->next->value ; 
        swap_stack(stack) ; 
    }

    if(tmp > (*stack)->next->next->value)
    {
        ro(stack ) ; 
    }
}