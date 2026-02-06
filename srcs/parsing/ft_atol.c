/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bakh <mel-bakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 21:15:33 by mel-bakh          #+#    #+#             */
/*   Updated: 2026/02/06 21:15:33 by mel-bakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

int	ft_isspace(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
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