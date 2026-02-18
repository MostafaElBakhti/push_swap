/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_turk.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bakh <mel-bakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 03:00:00 by mel-bakh          #+#    #+#             */
/*   Updated: 2026/02/18 21:22:09 by mel-bakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

int get_abs(int n)
{
	if(n < 0)
		return -n;
	return n ; 
}	

t_stack *get_sheapest(t_stack *stack_a)
{
	t_stack *current = stack_a ; 
	t_stack *cheapest = stack_a ; 

	int lowest_cost = INT_MAX ; 
	int total_cost = 0 ; 

	while (current)
	{
		total_cost = get_abs(current->cost_a) + get_abs(current->cost_b) ;
		if (total_cost  < lowest_cost)	
		{
			lowest_cost = total_cost  ; 
			cheapest = current ; 
		}

		current  = current->next ; 
	}
	return cheapest ; 
}

void do_rotate(t_stack **stack, int cost , char stack_name)
{
	if(cost > 0 )
	{
		while(cost > 0)
		{
			if(stack_name == 'a')
				ra(stack);
			else if(stack_name == 'b')
				rb(stack);
			cost--;
		}
	}else if (cost < 0)
	{
		while (cost < 0)
		{
			if(stack_name == 'a')
				rra(stack);
			else if(stack_name == 'b')
				rrb(stack);
			cost++;
		}
		
	}
}

static void do_cheapest_move(t_stack **stack_a, t_stack **stack_b)
{
    t_stack *cheapest;
    
    cheapest = get_cheapest(*stack_a);
    do_rotate(stack_a, cheapest->cost_a, 'a');
    do_rotate(stack_b, cheapest->cost_b, 'b');
    pb(stack_a, stack_b);
}
void push_back_to_a(t_stack **stack_a, t_stack **stack_b)
{
	int size_a = stack_size(stack_a) ;
	int clos_larger = INT_MAX ; 
	t_stack *current =  stack_b; 

	while (current)
	{


		current = current->next ; 
	}
	 
}

