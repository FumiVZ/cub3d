/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 13:22:23 by vzuccare          #+#    #+#             */
/*   Updated: 2024/10/31 05:12:03 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

char	*data_texture(char *line, char *id, size_t i)
{
	char	*path;
	size_t	start;
	size_t	len;

	i += ft_strlen(id);
	while (line[i] && is_space(line[i]))
		i++;
	start = i;
	len = 0;
	while (line[i + len] && line[i + len] != '\n')
		len++;
	path = ft_substr(line, start, len);
	if (!path)
		return (NULL);
	if (access(path, F_OK) == -1)
	{
		free(path);
		return (NULL);
	}
	return (path);
}

bool	is_valid(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	if (ft_strlen(str) > 3)
		return (false);
	return (true);
}

char	**erase_space(char **tab)
{
	char	**new;
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	new = malloc(sizeof(char *) * (ft_tablen(tab) + 1));
	if (!new)
		return (free_tab(tab), NULL);
	while (tab[i])
	{
		j = 0;
		while (tab[i][j] && is_space(tab[i][j]))
			j++;
		k = j;
		while (tab[i][j] && !is_space(tab[i][j]))
			j++;
		new[i] = ft_substr(tab[i], k, j - k);
		if (!new[i])
			return (free_tab(tab), free_tab(new), NULL);
		i++;
	}
	new[i] = NULL;
	return (free_tab(tab), new);
}

int	*assign_color(char **tab, int *color)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		color[i] = ft_atoi(tab[i]);
		if (color[i] > 255)
			return (free(color), NULL);
		i++;
	}
	color[i] = -1;
	return (color);
}

int	*parse_color(char *line, char *search, size_t i)
{
	ssize_t	j;
	int		*color;
	char	**tab;

	i += ft_strlen(search);
	if (ft_strlen(line) <= i)
		return (NULL);
	while (line[i] && is_space(line[i]))
		i++;
	tab = erase_space(ft_split(line + i, ','));
	if (!tab)
		return (NULL);
	if (ft_tablen(tab) != 3)
		return (free_tab(tab), NULL);
	j = -1;
	while (tab[++j])
		if (!is_valid(tab[j]))
			return (free_tab(tab), NULL);
	color = malloc(sizeof(int) * 4);
	if (!color)
		return (free_tab(tab), NULL);
	color = assign_color(tab, color);
	return (free_tab(tab), color);
}
