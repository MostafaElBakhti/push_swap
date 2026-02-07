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

int highest_value(t_stack *stack)
{
    int max = stack->value ;
    while (stack)
    {
        if(stack->value > max)
            max = stack->value ; 
        stack = stack->next ;
    }   
    return max ;
}


void sort_three(t_stack **stack)
{
    int highest ;

    highest =  highest_value(*stack);

    if ( (*stack)->value == highest)
        ra(stack) ;
    else if ((*stack)->next->value == highest)
        rra(stack) ;
    if ((*stack)->value > (*stack)->next->value)
        sa(stack) ;
}