/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bakh <mel-bakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 20:40:23 by mel-bakh          #+#    #+#             */
/*   Updated: 2026/02/01 20:41:10 by mel-bakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>

typedef struct s_stack
{
	int				value;
	int				pos;
	int				target_pos;
	int				cost_a;
	int				cost_b;
	struct s_stack	*next;
}	t_stack;

t_stack	*stack_new(int value);
void	stack_add_back(t_stack **stack, t_stack *new_node);
int	stack_size(t_stack *stack) ;
t_stack	*stack_last(t_stack *stack);
void	print_stack(t_stack *stack, char stack_name);
void	free_stack(t_stack **stack);

void	sa(t_stack **stack_a);
void	sb(t_stack **stack_b);
void	ss(t_stack **a, t_stack **b);
void	pa(t_stack **stack_a, t_stack **stack_b);
void	pb(t_stack **stack_a, t_stack **stack_b);
void	ra(t_stack **stack_a);
void	rb(t_stack **stack_b);
void	rr(t_stack **a, t_stack **b);
void	rra(t_stack **stack_a);
void	rrb(t_stack **stack_b);
void	rrr(t_stack **a, t_stack **b);


int	ft_isspace(char c);
long long ft_atol(char *str);
int	is_valid_number(char *str);
int	has_duplicates(t_stack *stack);
int	is_sorted(t_stack *stack);


#endif


