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

int main (int argc , char **argv) 
{
    int i ; 
    i = 1 ; 
    while( i < argc )
    {
        printf("%s\n" , argv[i]);
        i++ ; 
    }
}