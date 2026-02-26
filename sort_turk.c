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

#include "push_swap.h"

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
