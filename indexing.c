/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   indexing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bakh <mel-bakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 14:25:48 by mel-bakh          #+#    #+#             */
/*   Updated: 2026/02/22 14:25:48 by mel-bakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	*copy_stack_to_array(t_stack *stack_a)
{
	int		size;
	int		*arr;
	int		i;

	size = stack_size(stack_a);
	arr = malloc(sizeof(int) * size);
	if (!arr)
		return (NULL);
	i = 0;
	while (stack_a)
	{
		arr[i++] = stack_a->value;
		stack_a = stack_a->next;
	}
	return (arr);
}

static void	sort_array(int *arr, int size)
{
	int	i;
	int	tmp;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 1;
		while (j < size - i)
		{
			if (arr[j] < arr[j - 1])
			{
				tmp = arr[j];
				arr[j] = arr[j - 1];
				arr[j - 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

static void	assign_index(t_stack **stack, int *arr, int size)
{
	t_stack	*temp;
	int		i;

	temp = *stack;
	while (temp)
	{
		i = 0;
		while (i < size)
		{
			if (temp->value == arr[i])
			{
				temp->index = i;
				break ;
			}
			i++;
		}
		temp = temp->next;
	}
}

void	ft_index_stack(t_stack **stack)
{
	int	*arr;
	int	size;

	size = stack_size(*stack);
	arr = copy_stack_to_array(*stack);
	sort_array(arr, size);
	assign_index(stack, arr, size);
	free(arr);
}
