/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bakh <mel-bakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 15:36:52 by mel-bakh          #+#    #+#             */
/*   Updated: 2026/02/10 15:36:52 by mel-bakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/push_swap.h"

t_stack *create_node(int value)
{
    t_stack *node ; 

    node = malloc(sizeof(t_stack));
    if (!node)
        return NULL ;
    node->value = value ; 
    node->next = NULL ; 

    return node ; 
}   

// void rotate_last_nodes(t_stack **stack)
// {
//     t_stack *head;
//     t_stack *last;
//     t_stack *before_last;

//     if (!stack || !*stack || !(*stack)->next)
//         return;

//     head = *stack;
//     last = head;
//     before_last = NULL;

//     while (last->next != NULL)
//     {
//         before_last = last;
//         last = last->next;
//     }

//     before_last->next = NULL;
//     last->next = head;
//     head = last;

//     *stack = head;
// }

void swap_nodes(t_stack **stack)
{
    t_stack *first  ; 
    t_stack *second  ; 

    if (!stack || !*stack || !(*stack)->next)
        return;

    first = *stack ;
    second = (*stack)->next ;

    first->next = second->next ; 
    second->next = first ; 
    *stack = second ; 

}


int main (void)
{
    t_stack *node1 ; 
    t_stack *node2 ; 
    t_stack *node3 ; 
    node1 = create_node(5) ;
    node2 = create_node(8) ;
    node3 = create_node(10) ;

    node1->next = node2 ;
    node2->next = node3 ;
    printf("%p" , node1 ) ;

    playing_with_nodes(&node1);
}