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
    char *name;
    int age ;
    struct test *next ;
} my_struct; 


my_struct *create_node(int age , char *name , my_struct **last){
    
    static int counter = 0 ;
    counter++ ; 
    printf("Creating node number: %d\n" , counter) ;

    my_struct *node ; 

    node = malloc(sizeof(my_struct)) ; 
    if (!node)
    {
        return NULL;
    }
    
    node->name = malloc(sizeof(char) * (strlen(name) + 1)) ; 
    if (!node->name)
    {
        free(node);
        return NULL;
    }
    
    strcpy(node->name , name) ; 
    node->age = age ; 
    node->next = NULL ;

    if (*last != NULL){
        (*last)->next = node ; 
    }

    *last = node ;
    return node ; 
    
}



int main(){
    char *names[] = {"mostafa" , "mohamad"} ;
    int ages[] = {22 , 15} ;  

    my_struct *person1 ; 
    my_struct *person2 ; 
    my_struct *last = NULL ;

    person1 = create_node(ages[0] , names[0] , &last) ;
    person2 = create_node(ages[1] , names[1] , &last) ;

    printf("Person 1: Name = %s, Age = %d\n", person1->name , person1->age) ;
    printf("Person 2: Name = %s, Age = %d\n", person2->name , person2->age) ;


    free(person1->name) ;
    free(person1) ;
    free(person2->name) ;
    free(person2) ;
    

    return 0;
}































// typedef struct s_stack
// {
//     int				value;
//     int				pos;
//     int				target_pos;
//     int				cost_a;
//     int				cost_b;
//     struct s_stack	*next;
// }	t_stack;

// //create function that create a new node 

// t_stack *stack_new(int value){
//     t_stack *new_node ; 

//     new_node = malloc(sizeof(t_stack));
//     if(!new_node){
//         printf("malloc failed \n") ; 
//         return NULL ;
//     }
    
//     new_node->value = value ; 
//     new_node->pos = 0   ;
//     new_node->target_pos = 0 ;
//     new_node->cost_a = 0 ; 
//     new_node->cost_b = 0 ;
//     new_node->next = NULL ;  

//     return new_node ; 
// }



// int main()
// {
//     t_stack *node1 ;

//     node1 = stack_new(42) ; 

//     printf("Node value: %d\n", node1->value) ;
//     printf("Node pos: %d\n", node1->pos) ;  
//     printf("Node target_pos: %d\n", node1->target_pos) ;
//     printf("Node cost_a: %d\n", node1->cost_a) ;
//     printf("Node cost_b: %d\n", node1->cost_b) ;
//     printf("Node next: %p\n", node1->next) ;

//     free (node1) ;

//     return 0;
// } 