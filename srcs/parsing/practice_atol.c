/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   practice_atol.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bakh <mel-bakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 15:40:20 by mel-bakh          #+#    #+#             */
/*   Updated: 2026/02/05 15:40:20 by mel-bakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <limits.h>

long ft_atol(char *str)
{
    int i = 0 ;
    int sign = 1 ;
    while ( str[i] == ' ' || (str[i] >= 9 && str[i] <= 13) )
        i++;

    if ( str[i] == '-' || str[i] == '+' )
    {
        if ( str[i] == '-' )
            sign = -1 ;
        i++;
    }

    long result = 0 ;
    while ( str[i] >= '0' && str[i] <= '9' )
    {
        result = result * 10 + (str[i] - '0') ;
        i++;
    }
    return (result * sign) ;
}


int is_valid_int(long num)
{
    if ( num < INT_MIN || num > INT_MAX )
        return 0 ;
    return 1 ;
}


int main(void)
{
    long result;
    
    // Normal cases
    result = ft_atol("42");
    printf("'42' -> %ld, valid: %d\n", result, is_valid_int(result));
    
    result = ft_atol("-2147483648");
    printf("'-2147483648' (INT_MIN) -> %ld, valid: %d\n", result, is_valid_int(result));
    
    result = ft_atol("2147483647");
    printf("'2147483647' (INT_MAX) -> %ld, valid: %d\n", result, is_valid_int(result));
    
    // Overflow cases
    result = ft_atol("2147483648");
    printf("'2147483648' (overflow) -> %ld, valid: %d\n", result, is_valid_int(result));
    
    result = ft_atol("-2147483649");
    printf("'-2147483649' (underflow) -> %ld, valid: %d\n", result, is_valid_int(result));
    
    return 0;
}
