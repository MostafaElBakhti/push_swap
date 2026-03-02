/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bakh <mel-bakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 01:37:52 by mel-bakh          #+#    #+#             */
/*   Updated: 2026/03/02 00:29:50 by mel-bakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

typedef struct list
{
	int				value;
	struct list		*next;
}	t_list;

char		*get_next_line(int fd);
char		*ft_strchr(const char *s, int c);
size_t		strlen_bonus(const char *s);
char		*ft_strjoin(char *s1, char *s2);
t_list		*parse_args(int argc, char **argv, t_list **stack);
char		**ft_split_bonus(const char *s, char c);
int			has_duplicates_bonus(t_list *stack);
int			is_valid_number_bonus(char *str);
void		error_exit_b(void);
long long	ft_atol_bonus(char *str);
t_list		*stack_new_bonus(int value);
void		stack_add_back_bonus(t_list **stack, t_list *new_node);
int			swap_bonus(t_list **a, t_list **b, char *line);
int			rotate_bonus(t_list **a, t_list **b, char *line);
int			is_sorted_bonus(t_list *stack);
void		free_stack_bonus(t_list **stack);
void		ro_bonus(t_list **stack);
void		rro_bonus(t_list **stack);
void		swap_stack_bonus(t_list **stack);
int			ft_isspace_bonus(char c);

#endif
