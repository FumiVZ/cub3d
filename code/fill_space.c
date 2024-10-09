/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_space.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:30:41 by vzuccare          #+#    #+#             */
/*   Updated: 2024/10/09 17:57:23 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	fill_space(t_map *new_map, t_map *map, ssize_t y)
{
	ssize_t	x;

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
	if (y == (ssize_t) map->map_y - 1)
		new_map->map[y + 1] = NULL;
}

static void	init_new_map(t_game *game, t_map **new_map, t_map *map)
{
	*new_map = malloc(sizeof(t_map));
	if (!*new_map)
		exit_close_msg(game->fd, ERR_MALLOC, game, NULL);
	(*new_map)->map = malloc(sizeof(char *) * (map->map_y + 1));
	if (!(*new_map)->map)
	{
		free(*new_map);
		exit_close_msg(game->fd, ERR_MALLOC, game, NULL);
	}
}

static void	init_newmap_player(t_game *game, t_map *new_map, t_map *map)
{
	new_map->player = malloc(sizeof(t_player));
	if (!new_map->player)
		exit_close_msg(game->fd, ERR_MALLOC, game, NULL);
	new_map->player->pos = malloc(sizeof(t_position));
	if (!new_map->player->pos)
		exit_close_msg(game->fd, ERR_MALLOC, game, NULL);
	new_map->player->dir = malloc(sizeof(t_position));
	if (!new_map->player->dir)
		exit_close_msg(game->fd, ERR_MALLOC, game, NULL);
	new_map->player->pos->x = -1;
	new_map->player->pos->y = -1;
	new_map->player->dir->x = 0;
	new_map->player->dir->y = 0;
	new_map->map_x = map->map_x;
	new_map->map_y = map->map_y;
}

t_map	*fill_with_space(t_map *map, t_game *game)
{
	t_map	*new_map;
	ssize_t	x;
	ssize_t	y;

	new_map = NULL;
	x = -1;
	y = -1;
	init_new_map(game, &new_map, map);
	init_newmap_player(game, new_map, map);
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
		fill_space(new_map, map, y);
	}
	free_map(map);
	return (new_map);
}
