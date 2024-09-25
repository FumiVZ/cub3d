/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:33:48 by machrist          #+#    #+#             */
/*   Updated: 2024/09/25 21:51:14 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_word(char const *s, char c)
{
	size_t	i;
	size_t	res;

	if (!s)
		return (0);
	i = 0;
	res = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			++res;
		while (s[i] && s[i] != c)
			i++;
	}
	return (res);
}

static char	*crt_word(char const *s, char c)
{
	size_t	i;
	size_t	len;
	char	*word;

	if (!s)
		return (NULL);
	len = 0;
	while (s[len] && s[len] != c)
		len++;
	word = malloc(sizeof(char) * len + 1);
	if (!word)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

void	free_split(char **str, size_t pos)
{
	size_t	i;

	if (!str)
		return ;
	if (!*str)
		return (free(str));
	i = 0;
	while (i <= pos)
		free(str[i++]);
	free(str);
}

int	init_split(char const *s, char c, char ***str, size_t *i)
{
	if (!s)
		return (1);
	*str = malloc(sizeof(char *) * (count_word(s, c) + 1));
	if (!*str)
		return (1);
	*i = 0;
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	size_t	i;
	size_t	pos;

	if (init_split(s, c, &str, &i))
		return (NULL);
	pos = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			++i;
		if (s[i])
		{
			str[pos] = crt_word(s + i, c);
			if (!str[pos])
				return (free_split(str, pos + 1), NULL);
			pos++;
		}
		while (s[i] && s[i] != c)
			++i;
	}
	str[pos] = NULL;
	return (str);
}
