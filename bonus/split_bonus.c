/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_bonus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bakh <mel-bakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 14:43:14 by mel-bakh          #+#    #+#             */
/*   Updated: 2026/02/27 14:43:14 by mel-bakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	len;

	i = 0;
	if (size == 0)
		return (strlen_bonus(src));
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

static size_t	count_words(const char *s, char c)
{
	size_t	count;
	int		in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

static int	allocate_word_memory(char **ptr, size_t idx, int len)
{
	size_t	i;

	ptr[idx] = malloc(len + 1);
	if (!ptr[idx])
	{
		i = 0;
		while (i < idx)
		{
			free(ptr[i]);
			i++;
		}
		return (1);
	}
	return (0);
}

static int	ft_fill_memory(char **result, const char *s, char c)
{
	size_t	idx;
	int		len;

	idx = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		len = 0;
		while (s[len] && s[len] != c)
			len++;
		if (len > 0)
		{
			if (allocate_word_memory(result, idx, len) == 1)
				return (1);
			ft_strlcpy(result[idx], s, len + 1);
			idx++;
			s += len;
		}
	}
	return (0);
}

char	**ft_split_bonus(const char *s, char c)
{
	char	**ptr;
	size_t	words;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	ptr = malloc((words + 1) * sizeof(char *));
	if (!ptr)
		return (NULL);
	if (ft_fill_memory(ptr, s, c) == 1)
	{
		free(ptr);
		return (NULL);
	}
	ptr[words] = NULL;
	return (ptr);
}
