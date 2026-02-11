/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_size.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bakh <mel-bakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 17:04:54 by mel-bakh          #+#    #+#             */
/*   Updated: 2026/02/04 17:04:54 by mel-bakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

// this function calculates the size of the stack by traversing it and counting the nodes until it reaches the end (NULL). It returns the total count, which represents the number of elements in the stack.

int stack_size(t_stack *stack)
{
    t_stack *current  = stack ; 
    int counter = 0 ; 
    while (current != NULL)
    {
        counter ++; 
        current = current->next ;
    }
    return counter ; 
}

