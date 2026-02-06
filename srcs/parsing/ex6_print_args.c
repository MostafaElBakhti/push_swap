/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex6_print_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bakh <mel-bakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 20:38:48 by mel-bakh          #+#    #+#             */
/*   Updated: 2026/02/06 20:38:48 by mel-bakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

int main ( int argc , char **argv)
{
    int i = 1 ; 
    while ( i < argc )
    {
        printf("Argument %d: %s\n", i, argv[i]);
        i++;
    }
}