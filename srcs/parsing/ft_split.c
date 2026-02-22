/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bakh <mel-bakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 13:56:36 by mel-bakh          #+#    #+#             */
/*   Updated: 2026/02/21 01:00:00 by mel-bakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

int ft_count_words(char *str)
{
	int flag = 0 ; 
	int i = 0 ; 
	int count = 0 ;

	while (str[i])
	{
		if (str[i] != ' ' && flag == 0)
		{
			flag = 1 ; 
			count++;
		}else if (str[i] == ' ')
			flag = 0 ; 
		i++ ; 
	}

	return count ;
}

int	ft_word_len(char *str)
{
	int len = 0 ; 
	while (str[len] && str[len] != ' ')
		len++ ; 
	return len ;
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (*s)
	{
		i++;
		s++;
	}
	return (i);
}

int	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	len;

	i = 0;
	if (size == 0)
		return (ft_strlen(src));
	if (size > 0)
	{
		while (src[i] && i < size - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	len = 0;
	while (src[len])
		len++;
	return (len);
}

char **ft_split(char *str)
{
	int i = 0 ; 
	if(!str)
		return 0 ; 
	char **test ; 
	int count_words ; 

	count_words = ft_count_words(str) ;

	test = (char **)malloc(sizeof(char *) * (count_words + 1)) ;
	if(!test)
		return 0 ;

	while(*str)
	{
		while (*str == ' ')
			str++ ; 
		if (*str)
		{
			int word_len = ft_word_len(str) ; 
			test[i] = (char *)malloc(sizeof(char) * (word_len + 1)) ;
			if (!test[i])
				return 0 ;
			ft_strlcpy(test[i], str, word_len + 1) ; 
			str += word_len ; 
			i++ ; 
		}
	}
	test[i] = NULL ;
	return test ;
}


