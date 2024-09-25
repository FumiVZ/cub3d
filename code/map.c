/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:56:42 by vzuccare          #+#    #+#             */
/*   Updated: 2024/09/25 18:40:59 by vzuccare         ###   ########lyon.fr   */
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

static char	*ft_strappend(char **s1, const char *s2)
{
	char	*str;

	if (!*s1 || !s2)
		return (NULL);
	str = (char *)ft_calloc((ft_strlen(*s1) + ft_strlen(s2)) + 1, sizeof(char));
	if (!str)
		return (NULL);
	ft_strlcpy(str, *s1, ft_strlen(*s1) + 1);
	ft_strlcat(str, s2, ft_strlen(*s1) + ft_strlen(s2) + 1);
	free(*s1);
	return (str);
}

void	ft_init_map(t_game *game, char *av)
{
	char	*map;
	char	*line;
	int		fd;

	fd = open(av, O_RDONLY);
	if (fd < 0)
		ft_error_msg("Map file not found", game);
	map = ft_strdup("");
	game->map.rows = 0;
	while (true)	
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		map = ft_strappend(&map, line);
		if (!map)
			ft_error_msg("Malloc failed", game);
		free(line);
		game->map.rows++;
	}
	close(fd);
	ft_check_for_empty_lines(map, game);
	game->map.full = ft_split(map, '\n');
	free(map);
}
