/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincent <vincent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:56:42 by vzuccare          #+#    #+#             */
/*   Updated: 2024/09/28 16:00:21 by vincent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	is_empty(char *line)
{
	size_t	i;

	i = 0;
	while (line[i] && is_space(line[i]))
		i++;
	if (!line[i])
		return (1);
	return (0);
}

bool	check_adjacent(char **map, size_t i, size_t j, char c)
{
	if (map[j - 1] && map[j - 1][i] == c)
		return (true);
	if (map[j + 1] && map[j + 1][i] == c)
		return (true);
	if (map[j][i - 1] && map[j][i - 1] == c)
		return (true);
	if (map[j][i + 1] && map[j][i + 1] == c)
		return (true);
	return (false);
}

bool	check_zero(t_map *map)
{
	size_t	i;
	size_t	j;

	j = 0;
	while (map->map[j])
	{
		i = 0;
		while (map->map[j][i])
		{
			if (map->map[j][i] == 'N')
			{
				map->player.pos.x = i;
				map->player.pos.y = j;
			}
			if (map->map[j][i] == '0')
			{
				if (j == 0 || j == map->map_y || i == 0 || i == map->map_x)
					return (false);
				if (check_adjacent(map->map, i, j, ' ')
					&& check_adjacent(map->map, i, j, '1'))
					return (false);
			}
			i++;
		}
		j++;
	}
	return (true);
}

bool	is_space_or_one(char c)
{
	if (c == ' ' || c == '1' || c == '\n')
		return (true);
	return (false);
}

bool	is_correct_map(t_map *map)
{
	ssize_t	i;
	ssize_t	j;

	j = -1;
	i = -1;
	if (!map->map || !map->map[0] || !map->map[0][0])
		return (false);
	map->map_y--;
	while (map->map[0][++i])
		if (!is_space_or_one(map->map[0][i]))
			return (false);
	i = -1;
	while (map->map[map->map_y][++i])
		if (!is_space_or_one(map->map[map->map_y][i]))
			return (false);
	while (map->map[++j])
		if (!is_space_or_one(map->map[j][0]))
			return (false);
	j = -1;
	while (map->map[++j])
	{
		i = -1;
		while (map->map[j][++i])
			;
		if (!is_space_or_one(map->map[j][i - 1]))
			return (false);
	}
	return (check_zero(map));
}

static char	*ft_strappend(char *s1, char *s2)
{
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	str = (char *)ft_calloc((ft_strlen(s1) + ft_strlen(s2)) + 1, sizeof(char));
	if (!str)
	{
		free(s1);
		free(s2);
		return (NULL);
	}
	ft_strlcpy(str, s1, ft_strlen(s1) + 1);
	ft_strlcat(str, s2, ft_strlen(s1) + ft_strlen(s2) + 1);
	free(s1);
	return (str);
}

bool	check_map(t_map *map, int fd)
{
	char	*tmp;
	char	*line;

	if (!map)
		return (fprintf(stderr, "Map is NULL\n"), false);
	tmp = ft_strdup("");
	if (!tmp)
		return (fprintf(stderr, "Malloc failed\n"), false);
	map->map_x = 0;
	while (true)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (map->map_x < ft_strlen(line))
			map->map_x = ft_strlen(line) - 1;
		tmp = ft_strappend(tmp, line);
		if (!tmp)
			return (fprintf(stderr, "Malloc failed\n"), false);
		free(line);
	}
	close(fd);
	map->map = ft_split(tmp, '\n');
	map->map_y = ft_strstrlen(map->map);
	free(tmp);
	return (is_correct_map(map));
}
