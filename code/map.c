/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:56:42 by vzuccare          #+#    #+#             */
/*   Updated: 2024/10/29 18:26:46 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	init_player_rot(t_player **player, char c)
{
	if (c == 'N')
	{
		(*player)->dir->x = 0;
		(*player)->dir->y = -1;
		(*player)->angle = PI * 3 / 2;
	}
	else if (c == 'S')
	{
		(*player)->dir->x = 0;
		(*player)->dir->y = 1;
		(*player)->angle = PI / 2;
	}
	else if (c == 'E')
	{
		(*player)->dir->x = 1;
		(*player)->dir->y = 0;
		(*player)->angle = 0;
	}
	else if (c == 'W')
	{
		(*player)->dir->x = -1;
		(*player)->dir->y = 0;
		(*player)->angle = PI;
	}
}

void	init_player(t_player **player, ssize_t x, ssize_t y, char c)
{
	(*player)->up = false;
	(*player)->down = false;
	(*player)->right = false;
	(*player)->left = false;
	(*player)->rotate_left = false;
	(*player)->rotate_right = false;
	(*player)->pos->x = x * 32 + 16;
	(*player)->pos->y = y * 32 + 16;
	init_player_rot(player, c);
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
	(*map)->map = ft_split(tmp, '\n');
	(*map)->map_y = ft_strstrlen((*map)->map);
	*map = fill_with_space(*map, game);
	free(tmp);
	return (close(*fd), check_zero(*map, -1, -1));
}
