/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:56:42 by vzuccare          #+#    #+#             */
/*   Updated: 2024/10/09 17:29:17 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

bool	check_adjacent(char **map, size_t i, size_t j, char c)
{
	if ((j > 0 && map[j - 1][i] == c) || (!map[j + 1] && map[j + 1][i] == c)
		|| (i > 0 && map[j][i - 1] == c) || (!map[j][i + 1] && map[j][i
			+ 1] == c) || (map[j - 1][i - 1] && map[j - 1][i - 1] == c)
		|| (map[j + 1][i + 1] && map[j + 1][i + 1] == c) || (map[j - 1][i + 1]
			&& map[j - 1][i + 1] == c) || (map[j + 1][i - 1] && map[j + 1][i
			- 1] == c))
		return (true);
	return (false);
}

void	init_player(t_player **player, ssize_t x, ssize_t y, char c)
{
	(*player)->pos->x = x;
	(*player)->pos->y = y;
	if (c == 'N')
	{
		(*player)->dir->x = 0;
		(*player)->dir->y = -1;
	}
	else if (c == 'S')
	{
		(*player)->dir->x = 0;
		(*player)->dir->y = 1;
	}
	else if (c == 'E')
	{
		(*player)->dir->x = 1;
		(*player)->dir->y = 0;
	}
	else if (c == 'W')
	{
		(*player)->dir->x = -1;
		(*player)->dir->y = 0;
	}
}

bool	check_zero(t_map *map, ssize_t i, ssize_t j)
{
	while (map->map[++j])
	{
		i = -1;
		while (map->map[j][++i])
		{
			if ((map->map[j][i] == 'N' || map->map[j][i] == 'S'
					|| map->map[j][i] == 'E' || map->map[j][i] == 'W'))
			{
				if (map->player->pos->x == -1)
					init_player(&map->player, i, j, map->map[j][i]);
				else
					return (false);
				map->map[j][i] = '0';
			}
			if (map->map[j][i] == '0')
				if ((j == 0 || j == (ssize_t)map->map_y - 1 || i == 0
						|| i == (ssize_t)map->map_x - 1)
					|| check_adjacent(map->map, i, j, ' '))
					return (false);
			if (map->map[j][i] && !(map->map[j][i] == '1'
					|| map->map[j][i] == '0' || map->map[j][i] == ' '))
				return (false);
		}
	}
	return (map->player->pos->x != -1);
}

t_map	*fill_with_space(t_map *map, t_game *game)
{
	t_map	*new_map;
	ssize_t	x;
	ssize_t	y;

	x = -1;
	y = -1;
	new_map = malloc(sizeof(t_map));
	if (!new_map)
		return (NULL);
	new_map->map = malloc(sizeof(char *) * (map->map_y + 1));
	if (!new_map->map)
	{
		free(new_map);
		return (NULL);
	}
	new_map->player = map->player;
	new_map->player = malloc(sizeof(t_player));
	if (!new_map->player)
		exit_close_msg(game->fd, ERR_MALLOC, game);
	new_map->player->pos = malloc(sizeof(t_position));
	if (!new_map->player->pos)
		exit_close_msg(game->fd, ERR_MALLOC, game);
	new_map->player->dir = malloc(sizeof(t_position));
	if (!new_map->player->dir)
		exit_close_msg(game->fd, ERR_MALLOC, game);
	new_map->player->pos->x = -1;
	new_map->player->pos->y = -1;
	new_map->player->dir->x = 0;
	new_map->player->dir->y = 0;
	new_map->map_x = map->map_x;
	new_map->map_y = map->map_y;
	while (++y < (ssize_t)map->map_y)
	{
		new_map->map[y] = malloc(sizeof(char) * ((ssize_t)map->map_x + 1));
		x = 0;
		if (!new_map->map[y])
		{
			while (++x < y)
				free(new_map->map[x]);
			free(new_map->map);
			free(new_map);
			return (NULL);
		}
		x = 0;
		while (map->map[y][x])
		{
			new_map->map[y][x] = map->map[y][x];
			x++;
		}
		while (x < (ssize_t)map->map_x)
		{
			new_map->map[y][x] = ' ';
			x++;
		}
		new_map->map[y][x] = '\0';
	}
	new_map->map[y] = NULL;
	free_map(map);
	return (new_map);
}

static char	*ft_strappend(char *s1, char *s2)
{
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	str = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	if (!str)
	{
		free(s1);
		free(s2);
		return (NULL);
	}
	ft_strlcpy(str, s1, ft_strlen(s1) + 1);
	ft_strlcat(str, s2, ft_strlen(s1) + ft_strlen(s2) + 1);
	free(s1);
	free(s2);
	return (str);
}

bool	check_map(t_map **map, t_game *game, int *fd)
{
	char	*tmp;
	char	*line;

	if (!*map)
		return (fprintf(stderr, "Map is NULL\n"), false);
	tmp = ft_strdup("");
	if (!tmp)
		return (fprintf(stderr, "Malloc failed\n"), false);
	(*map)->map_x = 0;
	while (true)
	{
		line = get_next_line(*fd);
		if (!line)
			break ;
		if ((*map)->map_x < ft_strlen(line))
			(*map)->map_x = ft_strlen(line) - 1;
		tmp = ft_strappend(tmp, line);
		if (!tmp)
			return (fprintf(stderr, "Malloc failed\n"), false);
	}
	close(*fd);
	(*map)->map = ft_split(tmp, '\n');
	(*map)->map_y = ft_strstrlen((*map)->map);
	*map = fill_with_space(*map, game);
	free(tmp);
	return (check_zero(*map, -1, -1));
}
