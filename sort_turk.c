/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   sort_turk.c										:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: mel-bakh <mel-bakh@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2026/02/07 03:00:00 by mel-bakh		  #+#	#+#			 */
/*   Updated: 2026/02/21 00:54:35 by mel-bakh		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "includes/push_swap.h"

void	push_back_to_a(t_stack **stack_a, t_stack **stack_b)
{
	int	target_pos;
	int	size_a;
	int	cost;

	while (*stack_b)
	{
		assign_positions(*stack_a);
		target_pos = find_target_a(*stack_a, (*stack_b)->value);
		size_a = stack_size(*stack_a);
		if (target_pos <= size_a / 2)
			cost = target_pos;
		else
			cost = (size_a - target_pos) * -1;
		do_rotate(stack_a, cost, 'a');
		pa(stack_a, stack_b);
	}
}

void	shift_stack(t_stack **stack_a)
{
	int	lowest_pos;
	int	size_a;
	int	cost;

	assign_positions(*stack_a);
	lowest_pos = get_lowest_pos(*stack_a);
	size_a = stack_size(*stack_a);
	if (lowest_pos <= size_a / 2)
		cost = lowest_pos;
	else
		cost = (size_a - lowest_pos) * -1;
	ft_rotate_a(stack_a, &cost);
}

void	sort_turk(t_stack **a, t_stack **b)
{
	int	size;
	int	mid;

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
}
