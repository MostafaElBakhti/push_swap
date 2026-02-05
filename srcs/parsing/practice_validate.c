/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   practice_validate.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bakh <mel-bakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 15:52:33 by mel-bakh          #+#    #+#             */
/*   Updated: 2026/02/05 15:52:33 by mel-bakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <limits.h>


int is_valid_number(char *str)
{
    int i = 0 ; 
    int sign = 1 ;
    while ( str[i] == ' ' || (str[i] >= 9 && str[i] <= 13) )
        i++;

    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
            sign = -1 ;
        i++;
    }

    while (str[i])
    {
        if ( (str[i]>= 'a' && str[i]>= 'z') || (str[i]>= 'A' && str[i]>= 'Z'))
            return 0; 
        i++;
    }
    
    return 1 ;
}

int main ()
{
    printf("'42' is valid: %d (expected: 1)\n", is_valid_number("42"));
    printf("'-42' is valid: %d (expected: 1)\n", is_valid_number("-42"));
    printf("'+42' is valid: %d (expected: 1)\n", is_valid_number("+42"));
    printf("'  42' is valid: %d (expected: 1)\n", is_valid_number("  42"));
    printf("'0' is valid: %d (expected: 1)\n", is_valid_number("0"));
    
    // Invalid numbers
    printf("'abc' is valid: %d (expected: 0)\n", is_valid_number("abc"));
    printf("'12a' is valid: %d (expected: 0)\n", is_valid_number("12a"));
    printf("'12 34' is valid: %d (expected: 0)\n", is_valid_number("12 34"));
    printf("'' is valid: %d (expected: 0)\n", is_valid_number(""));
    printf("'  ' is valid: %d (expected: 0)\n", is_valid_number("  "));
    printf("'-' is valid: %d (expected: 0)\n", is_valid_number("-"));
    printf("'--42' is valid: %d (expected: 0)\n", is_valid_number("--42"));
}