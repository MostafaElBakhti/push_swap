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

int is_sorted_array(int *arr, int size)
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

int has_duplicates(t_stack *stack)
{
    t_stack *current ;
    t_stack *checker ; 

    current = stack ; 

    while (current)
    {
        checker = current->next ; 
        while (checker)
        {
            if ( current->value == checker->value)    
                return 1 ;
            checker = checker->next ; 
        }
        current = current->next ;   
    }
    return (0) ; 
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

	// Check if already sorted (before building stack)
	if (is_sorted_array(numbers, count))
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

	// Check for duplicates using stack-based function
	if (has_duplicates(stack_a))
	{
		printf("Error\n");
		free_stack(&stack_a);
		free_stack(&stack_b);
		free(numbers);
		return (1);
	}

	// Print stack A
	print_stack(stack_a, 'A');

	// Cleanup
	free_stack(&stack_a);
	free_stack(&stack_b);
	free(numbers);

	return (0);
}
