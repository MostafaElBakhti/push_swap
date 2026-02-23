/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_rotations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bakh <mel-bakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 17:50:00 by mel-bakh          #+#    #+#             */
/*   Updated: 2026/02/23 17:50:00 by mel-bakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/push_swap.h"

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
