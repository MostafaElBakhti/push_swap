/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   practice_atol.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bakh <mel-bakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 15:14:59 by mel-bakh          #+#    #+#             */
/*   Updated: 2026/02/05 15:14:59 by mel-bakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <limits.h>




int ft_atoi(char *str)
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

    int result = 0 ;
    while ( str[i] >= '0' && str[i] <= '9' )
    {
        result = result * 10 + (str[i] - '0') ;
        printf("Current result: %d\n", result);
        i++;
    }
    return (result * sign) ;

}
int main(void)
{
    printf("Test 1: '%s' -> %d (expected: 42)\n", "42", ft_atoi("42"));
    printf("Test 2: '%s' -> %d (expected: -42)\n", "-42", ft_atoi("-42"));
    printf("Test 3: '%s' -> %d (expected: 0)\n", "0", ft_atoi("0"));
    printf("Test 4: '%s' -> %d (expected: 123)\n", "  123", ft_atoi("  123"));
    printf("Test 5: '%s' -> %d (expected: -456)\n", "  -456", ft_atoi("  -456"));
    printf("Test 6: '%s' -> %d (expected: 789)\n", "+789", ft_atoi("+789"));
    
    return 0;
}