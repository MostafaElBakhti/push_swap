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
    // "  -456"
    int i = 0 ; 
    int sign = 1 ;
    int result = 0 ; 
    while (str[i] == ' ' || str[i] == '\t')
        i++; 

    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-' )
            sign = -1 ;
        i++; 
    }

    while (str[i] >= '0' && str[i] <= '9')
    {
        result = result * 10 + str[i] - '0' ; 
        i++;
    }
    return (result * sign) ;

}

int main ()
{
  
    printf("\n------------------------------\n");
    int test = ft_atoi("2147483648");
    printf("%d",test  );
    
}