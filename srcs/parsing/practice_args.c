/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   practice_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bakh <mel-bakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 20:42:52 by mel-bakh          #+#    #+#             */
/*   Updated: 2026/02/05 20:42:52 by mel-bakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int ft_isspace(char c)
{
    return (c == ' ' || (c >= 9 && c <= 13));
}

int is_valid_number(char *str)
{
    int i = 0;

    if (!str || str[0] == '\0')
        return 0;

    while (ft_isspace(str[i]))
        i++;

    if (str[i] == '+' || str[i] == '-')
        i++;

    if (str[i] < '0' || str[i] > '9')
        return 0;

    while (str[i])
    {
        if (str[i] < '0' || str[i] > '9')
            return 0;
        i++;
    }
    return 1;
}

long ft_atol(char *str)
{
    int i = 0;
    int sign = 1;
    long result = 0;

    while (ft_isspace(str[i]))
        i++;

    if (str[i] == '+' || str[i] == '-')
    {
        if (str[i] == '-')
            sign = -1;
        i++;
    }

    while (str[i] >= '0' && str[i] <= '9')
    {
        result = result * 10 + (str[i] - '0');
        i++;
    }
    return result * sign;
}

int is_valid_int(long num)
{
    return (num >= INT_MIN && num <= INT_MAX);
}

int main (int argc , char **argv) 
{
    int i ; 
    long num ; 
    int *numbers ; 
    int count ; 

    if (argc < 2)
    {
        printf("Usage: %s <number1> <number2> ...\n", argv[0]);
        return 1;
    }

    numbers = malloc(sizeof(int) * (argc - 1));
    if (!numbers)
    {
        perror("Failed to allocate memory");
        return 1;
    }
    count = 0 ; 
    i = 1 ;
    while ( i < argc)
    {
        if (!(is_valid_number(argv[i])))
        {
            printf("Invalid number: %s\n", argv[i]);
            free(numbers);
            return 1;
        }
        num = ft_atol(argv[i]);
        if (!is_valid_int(num))
        {
            printf("Number out of int range: %s\n", argv[i]);
            free(numbers);
            return 1;
        }
        numbers[count++] = (int)num ;
        i++;
    }
    
    printf("Successfully parsed %d numbers:\n", count);
    for (i = 0; i < count; i++)
        printf("%d ", numbers[i]);
    printf("\n");
    
    free(numbers);
    return 0;


}