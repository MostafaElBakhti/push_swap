/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bakh <mel-bakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 16:49:45 by mel-bakh          #+#    #+#             */
/*   Updated: 2026/02/02 16:49:45 by mel-bakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	main(void)
{
    t_stack *node;
    node = stack_new(42);
    
    if (!node)
    {
		printf("❌ Error: malloc failed\n");
		return (1);
    }

    printf("✓ Node created successfully!\n");
	printf("  value: %d\n", node->value);
	printf("  pos: %d\n", node->pos);
	printf("  target_pos: %d\n", node->target_pos);
	printf("  cost_a: %d\n", node->cost_a);
	printf("  cost_b: %d\n", node->cost_b);
	printf("  next: %p\n", (void *)node->next);
    
    free(node) ;
    return 0 ; 
}