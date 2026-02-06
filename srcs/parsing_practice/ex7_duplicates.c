/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex7_duplicates.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bakh <mel-bakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 20:40:33 by mel-bakh          #+#    #+#             */
/*   Updated: 2026/02/06 20:40:33 by mel-bakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

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

int main ()
{
    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[] = {1, 2, 3, 2, 5};
    int arr3[] = {42};
    int arr4[] = {5, 4, 3, 2, 1};
    int arr5[] = {1, 2, 3, 4, 1};
    
    printf("[1,2,3,4,5] has duplicates: %d (expected: 0)\n", has_duplicates(arr1, 5));
    printf("[1,2,3,2,5] has duplicates: %d (expected: 1)\n", has_duplicates(arr2, 5));
    printf("[42] has duplicates: %d (expected: 0)\n", has_duplicates(arr3, 1));
    printf("[5,4,3,2,1] has duplicates: %d (expected: 0)\n", has_duplicates(arr4, 5));
    printf("[1,2,3,4,1] has duplicates: %d (expected: 1)\n", has_duplicates(arr5, 5));
    
    return 0;
}