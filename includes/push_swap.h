/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bakh <mel-bakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 20:40:23 by mel-bakh          #+#    #+#             */
/*   Updated: 2026/02/18 00:51:43 by mel-bakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

typedef struct s_stack
{
	int				value;
	int				pos;
	int				index;
	int				target_pos;
	int				cost_a;
	int				cost_b;
	struct s_stack	*next;
}	t_stack;

// Stack utility functions
t_stack	*stack_new(int value);
void	stack_add_back(t_stack **stack, t_stack *new_node);
int		stack_size(t_stack *stack);
t_stack	*stack_last(t_stack *stack);
void	free_stack(t_stack **stack);

// Swap operations
void	swap_stack(t_stack **stack);
void	sa(t_stack **stack_a);
void	sb(t_stack **stack_b);
void	ss(t_stack **a, t_stack **b);

// Push operations
void	pa(t_stack **stack_a, t_stack **stack_b);
void	pb(t_stack **stack_a, t_stack **stack_b);

// Rotate operations
void	ro(t_stack **stack);
void	ra(t_stack **stack_a);
void	rb(t_stack **stack_b);
void	rr(t_stack **a, t_stack **b);

// Reverse rotate operations
void	rro(t_stack **stack);
void	rra(t_stack **stack_a);
void	rrb(t_stack **stack_b);
void	rrr(t_stack **a, t_stack **b);

// Parsing and validation
int			ft_isspace(char c);
long long	ft_atol(char *str);
char		**ft_split(char *str);
int			is_valid_number(char *str);
int			has_duplicates(t_stack *stack);
int			is_sorted(t_stack *stack);
int			is_sorted_array(int *arr, int size);
void		error_exit(void);
t_stack		*parse_arguments(int argc, char **argv);

// Indexing
void		ft_index_stack(t_stack **stack_a);

// Position 
void		assign_positions(t_stack *stack);
int			get_lowest_pos(t_stack *stack);
int			get_highest_pos(t_stack *stack);

// Target 
void		assign_targets_b(t_stack *stack_a, t_stack *stack_b);
void		ft_set_target_pos(t_stack *stack_a, t_stack *stack_b);
int			find_target_a(t_stack *stack_a, int value);
int			find_target_b(t_stack *stack_b, int value);

// Cost 
void		calculate_costs(t_stack *stack_a, t_stack *stack_b);
void		calculate_cost_a(t_stack *stack_a);
void		calculate_cost_b(t_stack *stack_a, t_stack *stack_b);

// Sorting utilities
int			get_abs(int n);
int			get_max_value(t_stack **stack);
t_stack		*get_cheapest(t_stack *stack_a);
void		do_rotate(t_stack **stack, int cost, char stack_name);

// Sorting 
void		sort_two(t_stack **stack);
void		sort_three(t_stack **stack);
void		sort_four(t_stack **stack_a, t_stack **stack_b);
void		sort_five(t_stack **stack_a, t_stack **stack_b);

// Turk algorithm 
void		push_back_to_a(t_stack **stack_a, t_stack **stack_b);
void		shift_stack(t_stack **stack_a);
void sort_turk(t_stack **stack_a, t_stack **stack_b);

#endif


// void	print_stack(t_stack *stack, char stack_name);
