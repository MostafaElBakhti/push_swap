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

void rro(t_stack **stack)
{
    t_stack *last ;
    t_stack *before_last ;
    

    if (!stack || !*stack || (*stack)->next == NULL)
		return;

    before_last = *stack ; 

    while (before_last->next->next != NULL )
        before_last = before_last->next ;
    
    last = before_last->next ; 
    before_last->next = NULL ; 
    last->next = *stack ;
    *stack = last ;
}

void maxValue_to_bottom(t_stack **stack)
{
    int max ; 
        
    max = (*stack)->value;
    t_stack *current = *stack ;
    while (current)
    {
        if (current->value > max)
            max = current->value ; 
        current = current->next ; 
    }
    
    if((*stack)->value == max)
    {
        ro(stack) ; 
    }else if ((*stack)->next->value == max)
    {
        rro(stack) ; 
    }

}

void sort_three(t_stack **stack)
{   
    maxValue_to_bottom(stack) ; 

    if((*stack)->value > (*stack)->next->value)
    {
        swap_stack(stack) ; 
    }

}
