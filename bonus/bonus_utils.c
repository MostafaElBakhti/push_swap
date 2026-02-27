/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auto-generated                                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 15:00:00 by tool              #+#    #+#             */
/*   Updated: 2026/02/27 15:00:00 by tool             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	is_valid_number_bonus(char *str)
{
    int i;

    i = 0;
    if (str == NULL || str[0] == '\0')
        return (0);
    while (ft_isspace_bonus(str[i]))
        i++;
    if (str[i] == '-' || str[i] == '+')
        i++;
    if (!(str[i] >= '0' && str[i] <= '9'))
        return (0);
    while (str[i])
    {
        if (!(str[i] >= '0' && str[i] <= '9'))
            return (0);
        i++;
    }
    return (1);
}

int	has_duplicates_bonus(t_list *stack)
{
    t_list *current;
    t_list *checker;

    current = stack;
    while (current)
    {
        checker = current->next;
        while (checker)
        {
            if (current->value == checker->value)
                return (1);
            checker = checker->next;
        }
        current = current->next;
    }
    return (0);
}

int	is_sorted_bonus(t_list *stack)
{
    if (!stack)
        return (1);
    while (stack->next)
    {
        if (stack->value > stack->next->value)
            return (0);
        stack = stack->next;
    }
    return (1);
}

void	free_stack_bonus(t_list **stack)
{
    t_list *current;
    t_list *temp;

    if (stack == NULL || *stack == NULL)
        return ;
    current = *stack;
    while (current != NULL)
    {
        temp = current->next;
        free(current);
        current = temp;
    }
    *stack = NULL;
}

void	error_exit_b(void)
{
    write(2, "Error\n", 6);
    exit(1);
}
