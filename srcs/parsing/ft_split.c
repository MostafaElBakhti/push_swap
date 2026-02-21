/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bakh <mel-bakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 13:56:36 by mel-bakh          #+#    #+#             */
/*   Updated: 2026/02/21 00:54:02 by mel-bakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"
#include <stdio.h>

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
	return test ;
}



char **get_args(int argc , char **argv)
{
	// char **args ; 
	// if (argc == 2)
	// {
	// 	args = ft_split(argv[1]) ; 
	// }

	char **args = (char **)malloc(sizeof(char *) * argc) ;
	if (!args)
		return 0 ;
	
	for (int i = 0 ; i < argc - 1 ; i++)
	{
		args[i] = (char *)malloc(sizeof(char) * (ft_strlen(argv[i + 1]) + 1)) ;
		if (!args[i])
			return 0 ;
		ft_strlcpy(args[i], argv[i + 1], ft_strlen(argv[i + 1]) + 1) ; 
	}
	args[argc - 1] = NULL ;
	return args ;

}
// test split
int main(int argc , char **argv)
{
	char **args = get_args(argc , argv) ; 
	int i = 0 ; 
	while (args[i])
	{
		printf("%s\n", args[i]) ; 
		i++ ; 
	}
	

}