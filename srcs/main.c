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



typedef struct test 
{
    int age ;
    struct test *next ;
} my_struct; 


my_struct *create_node(int age ){
    
    static int counter = 0 ;
    counter++ ; 
    printf("Creating node number: %d\n" , counter) ;

    my_struct *node ; 

    node = malloc(sizeof(my_struct)) ; 
    if (!node)
    {
        return NULL;
    }
    
    node->age = age ; 
    node->next = NULL ;
    printf("adress currect : %p \n" , node) ; 
    return node ; 
    
}


void add_back(my_struct **head , my_struct *new_node)
{
    my_struct *temp ;
    if (*head == NULL )
    {
        *head = new_node;
        return ; 
    }

    temp = *head ;
    while (temp->next != NULL)
    {
        temp = temp->next ;
    }
    temp->next = new_node ;
}


int main(){
    
    my_struct  *head = NULL ;
    my_struct  *node1 ; 
    my_struct  *node2 ; 
    my_struct  *node3 ;
    
    node1 = create_node(21) ;
    node2 = create_node(25) ;
    node3 = create_node(30) ;

    add_back(&head , node1) ;
    add_back(&head , node2) ;
    add_back(&head , node3) ;


}
