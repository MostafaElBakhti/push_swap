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

int get_max_value(t_stack **stack)
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
    return max ; 
}

void sort_three(t_stack **stack)
{   
    int max = get_max_value(stack) ; 

    if((*stack)->value == max)
    {
        ro(stack) ; 
    }else if ((*stack)->next->value == max)
    {
        rro(stack);
    }

    if ((*stack)->value > (*stack)->next->value)
        sa(stack);
}

void sort_four(t_stack **stack_a ,t_stack **stack_b)
{
    t_stack *current ; 
    int     min ;

    current = *stack_a ; 
    min = current->value ;

    while (current)
    {
        if (current->value < min)
            min = current->value ; 
        current = current->next ; 
    }

    while((*stack_a)->value != min)
    {
        ro(stack_a);
    }
    pb(stack_a, stack_b) ; 
    sort_three(stack_a) ; 
    pa(stack_a,stack_b) ;

}

void sort_five(t_stack **stack_a, t_stack **stack_b)
{
        t_stack *current ; 
    int     min ;

    current = *stack_a ; 
    min = current->value ;

    while (current)
    {
        if (current->value < min)
            min = current->value ; 
        current = current->next ; 
    }

    while((*stack_a)->value != min)
    {
        ro(stack_a);
    }   
    pb(stack_a, stack_b) ; 
    sort_four(stack_a , stack_b) ; 
    pa(stack_a,stack_b) ;
}