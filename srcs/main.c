/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bakh <mel-bakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 16:49:45 by mel-bakh          #+#    #+#             */
/*   Updated: 2026/02/06 20:54:14 by mel-bakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int ft_isspace(char c)
{
    if (c == ' ' || (c >= 9 && c <= 13))
        return 1 ; 
    return 0 ; 
}

int is_valid_number(char *str)
{
    int i = 0 ; 

    if ( str == NULL || str[0] == '\0' )
        return 0 ; 
    
    while (ft_isspace(str[i]))
        i++;

    if (str[i] == '-' || str[i] == '+')
        i++ ; 
    
    if ( !(str[i] >= '0' && str[i] <= '9') )
        return 0 ;

    while ( str[i] )
    {
        if (!(str[i] >= '0' && str[i] <= '9'))
            return 0 ;
        i++;
    }

    return 1 ;
}

long long ft_atol(char *str)
{
    long long result ; 
    int sign = 1 ; 
    int i = 0 ; 

    while (ft_isspace(str[i]))
        i++;
    
    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-' )
            sign = -1 ;
        i++; 
    }
    result = 0 ; 
    while (str[i] >= '0' && str[i] <= '9')
    {
        result = result * 10 + str[i] - '0' ; 
        i++ ;
    }
    return (result * sign) ; 
}

int has_duplicates(int *arr, int size)
{
    int i = 0 ; 
    int j ;
    while (i < size )
    {
        j = i + 1;
        while (j < size)
        {
            if ( arr[j] == arr[i] )
                return 1 ;
            j++ ;
        }
        i++;
    }
    return 0 ; 
}

int is_sorted(int *arr, int size)
{
    int i = 0;
    while (i < size - 1)
    {
        if (arr[i] > arr[i + 1])
            return 0;
        i++;
    }
    return 1;
}

int	main(int argc, char **argv)
{
	t_stack	*stack_a;
	t_stack	*stack_b;
	int		*numbers;
	int		count;
	int		i;
	long long num;

	// No arguments provided
	if (argc < 2)
		return (0);

	// Allocate memory for numbers
	numbers = malloc((argc - 1) * sizeof(int));
	if (!numbers)
		return (1);

	// Parse and validate arguments
	i = 1;
	count = 0;
	while (i < argc)
	{
		if (!is_valid_number(argv[i]))
		{
			printf("Error\n");
			free(numbers);
			return (1);
		}

		num = ft_atol(argv[i]);
		if (num > INT_MAX || num < INT_MIN)
		{
			printf("Error\n");
			free(numbers);
			return (1);
		}
		
		numbers[count++] = (int)num;
		i++;
	}

	// Check for duplicates
	if (has_duplicates(numbers, count))
	{
		printf("Error\n");
		free(numbers);
		return (1);
	}

	// Check if already sorted
	if (is_sorted(numbers, count))
	{
		free(numbers);
		return (0);
	}

	// Initialize stacks
	stack_a = NULL;
	stack_b = NULL;

	// Add numbers to stack_a
	for (i = 0; i < count; i++)
	{
		stack_add_back(&stack_a, stack_new(numbers[i]));
	}

	// Print stack A
	print_stack(stack_a, 'A');

	// Cleanup
	free_stack(&stack_a);
	free_stack(&stack_b);
	free(numbers);

	return (0);
}
