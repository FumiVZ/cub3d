/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 10:52:51 by machrist          #+#    #+#             */
/*   Updated: 2024/06/28 14:29:57 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long int	ft_strtol(const char *nptr)
{
	long int	res;
	int			i;
	int			s;

	res = 0;
	i = 0;
	s = 1;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
		if (nptr[i++] == '-')
			s = -1;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		if (res != (res * 10 + nptr[i] - '0') / 10)
		{
			if (s == -1)
				return (LONG_MIN);
			return (LONG_MAX);
		}
		res = res * 10 + nptr[i++] - '0';
	}
	return (res * s);
}

int	ft_atoi(const char *str)
{
	return ((int)ft_strtol(str));
}

static int	is_min_long_long(const char *nptr)
{
	int			i;
	const char	*min_val;

	min_val = "-9223372036854775808";
	i = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-')
		i++;
	else
		return (0);
	while (nptr[i] == min_val[i])
	{
		i++;
		if (min_val[i] == '\0')
			return (1);
	}
	return (0);
}

int	ft_is_int(const char *nptr)
{
	long long int	res;
	int				i;

	res = 0;
	i = 0;
	if (is_min_long_long(nptr))
		return (1);
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		if (res != (res * 10 + nptr[i] - '0') / 10)
			return (0);
		res = res * 10 + nptr[i++] - '0';
	}
	return (1);
}
