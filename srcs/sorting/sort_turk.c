/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_turk.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bakh <mel-bakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 03:00:00 by mel-bakh          #+#    #+#             */
/*   Updated: 2026/02/21 00:54:35 by mel-bakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

int get_abs(int n)
{
	if(n < 0)
		return -n;
	return n ; 
}	

t_stack *get_cheapest(t_stack *stack_a)
{
	t_stack *current = stack_a ; 
	t_stack *cheapest = stack_a ; 

	int lowest_cost = INT_MAX ; 
	int total_cost  ; 

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

// static void do_cheapest_move(t_stack **stack_a, t_stack **stack_b)
// {
//     t_stack *cheapest;
    
//     cheapest = get_cheapest(*stack_a);
//     do_rotate(stack_a, cheapest->cost_a, 'a');
//     do_rotate(stack_b, cheapest->cost_b, 'b');
//     pb(stack_a, stack_b);
// }
void push_back_to_a(t_stack **stack_a, t_stack **stack_b)
{
    int target_pos;
    int size_a;
    int cost ; 

    while (*stack_b)
    {
        assign_positions(*stack_a) ; 
        target_pos = find_target_a(*stack_a , (*stack_b)->value) ; 
        size_a = stack_size(*stack_a) ; 

        if(target_pos <= size_a / 2)
            cost = target_pos;
        else
            cost = (size_a - target_pos) * -1;

        do_rotate(stack_a, cost, 'a');
        pa(stack_a, stack_b);
    }
    
	 
}

void shift_stack(t_stack **stack_a)
{

    int lowest_pos ;
    int size_a ; 
    int cost ; 

    assign_positions(*stack_a) ;
    lowest_pos = get_lowest_pos(*stack_a) ;
    size_a = stack_size(*stack_a) ;  

    if (lowest_pos <= size_a / 2 )
        cost = lowest_pos ; 
    else
        cost = (size_a - lowest_pos) * -1;
    
    do_rotate(stack_a, cost, 'a') ; 
}


// void sort_turk(t_stack **stack_a, t_stack **stack_b)
// {
//     while (stack_size(*stack_a) > 3)
//     {
//         assign_positions(*stack_a);
//         assign_positions(*stack_b);
//         assign_targets_b(*stack_a, *stack_b);
//         calculate_costs(*stack_a, *stack_b);
//         do_cheapest_move(stack_a, stack_b);
//     }
    
//     sort_three(stack_a);
    
//     push_back_to_a(stack_a, stack_b);
    
//     shift_stack(stack_a);
// }

void	ft_rotate_both(t_stack **a, t_stack **b, int *ca, int *cb)
{
	while (*ca > 0 && *cb > 0)
	{
		rr(a, b);
		(*ca)--;
		(*cb)--;
	}
	while (*ca < 0 && *cb < 0)
	{
		rrr(a, b);
		(*ca)++;
		(*cb)++;
	}
}
void	ft_rotate_a(t_stack **a, int *ca)
{
	while (*ca > 0)
	{
		ra(a);
		(*ca)--;
	}
	while (*ca < 0)
	{
		rra(a);
		(*ca)++;
	}
}
void	ft_rotate_b(t_stack **b, int *cb)
{
	while (*cb > 0)
	{
		rb(b);
		(*cb)--;
	}
	while (*cb < 0)
	{
		rrb(b);
		(*cb)++;
	}
}


void	sort_turk(t_stack **a, t_stack **b)
{
    int size;
    int mid;

    size = stack_size(*a);
    mid = size / 2;
    ft_index_stack(a);

    while (stack_size(*a) > 3)
    {
        pb(a, b);
        if ((*b)->index < mid)
            rb(b);
    }
    sort_three(a);
	while (*b)
	{
		assign_positions(*a);
		assign_positions(*b);
		assign_target_pos(*a, *b);
		calculate_costs(*a, *b);
		push_cheapest(a, b);
	}
	shift_stack(a);
	// sort_three(a);
	// return_to_a(a, b);
	// finalize(a);
}