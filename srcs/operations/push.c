/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bakh <mel-bakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 00:30:02 by mel-bakh          #+#    #+#             */
/*   Updated: 2026/02/05 00:30:02 by mel-bakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

void    pa(t_stack **stack_a, t_stack **stack_b)
{
    t_stack *tmp ; 

    if ( !stack_b || !*stack_b )
        return ;

    tmp = *stack_b ;
        
    *stack_b = tmp->next ; 
    tmp->next = *stack_a ;
    *stack_a = tmp ;    

    write(1, "pa\n", 3);

}

void    pb(t_stack **stack_a, t_stack **stack_b)
{
    t_stack *tmp ; 

    if ( !stack_a || !*stack_a )
        return ;

    tmp = *stack_a ;
        
    *stack_a = tmp->next ; 
    tmp->next = *stack_b ;
    *stack_b = tmp ;    
    write(1, "pb\n", 3);

}
