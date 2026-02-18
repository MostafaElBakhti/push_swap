/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_turk.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bakh <mel-bakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 03:00:00 by mel-bakh          #+#    #+#             */
/*   Updated: 2026/02/18 19:11:53 by mel-bakh         ###   ########.fr       */
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
