/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex5_check_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bakh <mel-bakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 20:34:25 by mel-bakh          #+#    #+#             */
/*   Updated: 2026/02/06 20:34:25 by mel-bakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <limits.h>

int is_valid_int(long long num)
{
    if (num >= INT_MIN && num <= INT_MAX)
        return 1 ;
    return 0 ;
}

int main(void)
{
    printf("42 fits in int: %d (expected: 1)\n", is_valid_int(42));
    printf("2147483647 fits: %d (expected: 1)\n", is_valid_int(2147483647));
    printf("-2147483648 fits: %d (expected: 1)\n", is_valid_int(-2147483648));
    printf("2147483648 fits: %d (expected: 0)\n", is_valid_int(2147483648));
    printf("-2147483649 fits: %d (expected: 0)\n", is_valid_int(-2147483649));
    
    return 0;
}