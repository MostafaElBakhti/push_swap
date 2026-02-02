/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bakh <mel-bakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 16:49:45 by mel-bakh          #+#    #+#             */
/*   Updated: 2026/02/02 16:49:45 by mel-bakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h> 

typedef struct s_stack
{
    int				value;
    int				pos;
    int				target_pos;
    int				cost_a;
    int				cost_b;
    struct s_stack	*next;
}	t_stack;

//create function that create a new node 

t_stack *stack_new(int value){
    t_stack *new_node ; 

    new_node = malloc(sizeof(t_stack));
    if(!new_node){
        printf("malloc failed \n") ; 
        return NULL ;
    }
    
    new_node->value = value ; 
    new_node->pos = 0   ;
    new_node->target_pos = 0 ;
    new_node->cost_a = 0 ; 
    new_node->cost_b = 0 ;
    new_node->next = NULL ;  

    return new_node ; 
}



int main()
{
    int stack_a[] = {5 , 3, 8, 1, 2} ; 
    t_stack *node1 ;

    node1 = stack_new(42) ; 

    printf("Node value: %d\n", node1->value) ;
    printf("Node pos: %d\n", node1->pos) ;  
    printf("Node target_pos: %d\n", node1->target_pos) ;
    printf("Node cost_a: %d\n", node1->cost_a) ;
    printf("Node cost_b: %d\n", node1->cost_b) ;
    printf("Node next: %p\n", (void *)node1->next) ;

    free (node1) ;

    return 0;
}