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

#include "../includes/push_swap.h"

// typedef struct s_test 
// {
//     int age ;
//     struct test *next ;
// } my_struct;


my_struct *create_node(int age ){
    
    static int counter = 0 ;
    counter++ ; 
    // printf("Creating node number: %d\n" , counter) ;

    my_struct *node ; 

    node = malloc(sizeof(my_struct)) ; 
    if (!node)
    {
        return NULL;
    }
    
    node->age = age ; 
    node->next = NULL ;
    // printf("adress currect : %p \n" , node) ; 
    return node ; 
    
}


void add_back(my_struct **head , my_struct *new_node)
{
    my_struct *tmp ; 

    if (*head == NULL)
    {
        *head = new_node ; 
        return ; 
    }
    tmp = *head ; 

    while (tmp->next != NULL)
    {
        tmp = tmp->next ;
    }
    
    tmp->next = new_node ;

}


int main(){
    
    my_struct  *head_ptr = NULL ;
    my_struct  *node1 ; 
    my_struct  *node2 ; 
    my_struct  *node3 ;
    printf("adress head ptr before : %p \n" , head_ptr) ;
    node1 = create_node(21) ;
    printf("adress node 1 : %p \n" , node1) ;
    node2 = create_node(25) ;
    printf("adress node 2 : %p \n" , node2) ;
    node3 = create_node(30) ;
    printf("adress node 3 : %p \n" , node3) ;

    add_back(&head_ptr , node1) ;
    add_back(&head_ptr , node2) ;
    add_back(&head_ptr , node3) ;



}
