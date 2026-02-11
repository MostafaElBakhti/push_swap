/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bakh <mel-bakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 00:56:45 by mel-bakh          #+#    #+#             */
/*   Updated: 2026/02/07 00:56:45 by mel-bakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

void sort_two(t_stack **stack)
{
    if((*stack)->value > (*stack)->next->value)
        sa(stack) ;
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