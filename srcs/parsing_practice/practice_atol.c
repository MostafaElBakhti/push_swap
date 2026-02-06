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

int ft_isspace(char c)
{
    if (c == ' ' || (c >= 9 && c <= 13))
        return 1 ; 
    return 0 ; 
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

int main(void)
{
    printf("LLONG_MAX = %lld\n", LLONG_MAX);
    printf("\n------------------------------\n");
    printf(" %lld \n", ft_atol("2147483648"));
    
    return 0;
}