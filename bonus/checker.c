/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bakh <mel-bakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 01:41:36 by mel-bakh          #+#    #+#             */
/*   Updated: 2026/02/24 01:55:48 by mel-bakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include "../includes/push_swap.h"    
#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>   

void trim_newline(char *s)
{
    size_t len = strlen(s);
    if (len > 0 && s[len - 1] == '\n')
        s[len - 1] = '\0';
}


static int valid_instruction(char *line)
{
    return (!strcmp(line, "sa") || !strcmp(line, "sb") || !strcmp(line, "ss") ||
            !strcmp(line, "pa") || !strcmp(line, "pb") ||
            !strcmp(line, "ra") || !strcmp(line, "rb") || !strcmp(line, "rr") ||
            !strcmp(line, "rra") || !strcmp(line, "rrb") || !strcmp(line, "rrr"));
}

// Execute the instruction on stacks
static void execute_instruction(char *line, t_stack **a, t_stack **b)
{
	trim_newline(line);
    if (!strcmp(line, "sa"))
        sa(a);
    else if (!strcmp(line, "sb"))
        sb(b);
    else if (!strcmp(line, "ss"))
        ss(a, b);
    else if (!strcmp(line, "pa"))
        pa(a, b);
    else if (!strcmp(line, "pb"))
        pb(a, b);
    else if (!strcmp(line, "ra"))
        ra(a);
    else if (!strcmp(line, "rb"))
        rb(b);
    else if (!strcmp(line, "rr"))
        rr(a, b);
    else if (!strcmp(line, "rra"))
        rra(a);
    else if (!strcmp(line, "rrb"))
        rrb(b);
    else if (!strcmp(line, "rrr"))
        rrr(a, b);
}

int main(int argc, char **argv)
{
    t_stack *stack_a = NULL;
    t_stack *stack_b = NULL;
    char *line;

    if (argc < 2)
        return (0);  // No args, do nothing

    stack_a = parse_arguments(argc, argv, &stack_a);

    while ((line = get_next_line(0)))
    {
        if (!valid_instruction(line))
        {
            write(2, "Error\n", 6);
            free(line);
            free_stack(&stack_a);
            free_stack(&stack_b);
            return (1);
        }
        execute_instruction(line, &stack_a, &stack_b);
        free(line);
    }

    if (is_sorted(stack_a) && stack_b == NULL)
        write(1, "OK\n", 3);
    else
        write(1, "KO\n", 3);

    free_stack(&stack_a);
    free_stack(&stack_b);
    return (0);
}