/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_stack.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bakh <mel-bakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 17:43:32 by mel-bakh          #+#    #+#             */
/*   Updated: 2026/02/04 17:43:32 by mel-bakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

void	print_stack(t_stack *stack, char stack_name)
{
    printf("\n=== Stack %c ===\n", stack_name);
    if (stack == NULL)
    {
        printf("(empty)");
		printf("\n");
		return;
    }

    while (stack != NULL)
    {
        printf("%d", stack->value);
        if (stack->next != NULL)
            printf(" -> ");
        stack = stack->next ;
    }
    printf("\n");

}