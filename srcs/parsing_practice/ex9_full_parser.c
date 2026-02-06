/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex9_full_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bakh <mel-bakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 20:54:14 by mel-bakh          #+#    #+#             */
/*   Updated: 2026/02/06 20:54:14 by mel-bakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


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
    {
        i++;
    }
    
    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-' )
            sign = -1 ;
        i++; 
    }
    result = 0 ; 
    while (str[i] >= '0' && str[i] <= '9')
    {
        result = result *10 + str[i] - '0' ; 
        i++ ;
    }
    return (result * sign ) ; 
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

int main ( int argc , char **argv)
{
    int *numbers;
    int count;
    int i;
    long long num;
    int overflow;

    if ( argc < 2) {
        printf("Usage: %s <numbers>\n", argv[0]);
        return 1;
    }

    numbers = malloc((argc - 1) * sizeof(int));
    if (!numbers) {
        perror("Failed to allocate memory");
        return 1;
    }
    i = 1 ;
    count = 0 ;
    while(i < argc ){
        if (!is_valid_number(argv[i])) {
            printf("error") ; 
            return 1;
        }

        if ( ft_atol(argv[i]) > INT_MAX || ft_atol(argv[i]) < INT_MIN )
        {
            printf("error") ; 
            return 1;
        }  
        numbers[count++] = (int)ft_atol(argv[i]) ;
        i++;
    }
    // check for duplicates
    if ( has_duplicates(numbers, count) )
    {
        printf("error") ; 
        return 1;
    }

    printf("Parsed numbers:\n");
    for (i = 0; i < count; i++) {
        printf("%d\n", numbers[i]);
    }
    free(numbers);
    return 0;

}

// list of test cases to try with the final parser
/*
./ex9_full_parser 42 -42 +42 "  42" 0
./ex9_full_parser 42 abc 12a "12 34" "" "  " - --42
./ex9_full_parser 2147483647 2147483648 -2147483648 -2147483649
./ex9_full_parser 1 2 3 4 5
./ex9_full_parser 1 2 3 2 5
./ex9_full_parser 42
./ex9_full_parser 5 4 3 2 1
./ex9_full_parser 1 2 3 4 1
*/ 