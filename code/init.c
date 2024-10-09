/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:43:59 by vzuccare          #+#    #+#             */
/*   Updated: 2024/10/09 17:58:58 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	init_data(t_game *game)
{
	game->data->wall.xpm_ptr = NULL;
	game->data->floor.xpm_ptr = NULL;
	game->data->player.xpm_ptr = NULL;
	game->data->no = NULL;
	game->data->so = NULL;
	game->data->we = NULL;
	game->data->ea = NULL;
	game->data->c = NULL;
	game->data->f = NULL;
}

void	init_map(t_game *game, t_map *map)
{
	map->map = NULL;
	map->map_x = 0;
	map->map_y = 0;
	map->player = malloc(sizeof(t_player));
	if (!map->player)
		exit_close_msg(game->fd, ERR_MALLOC, game, NULL);
	map->player->pos = malloc(sizeof(t_position));
	if (!map->player->pos)
		exit_close_msg(game->fd, ERR_MALLOC, game, NULL);
	map->player->dir = malloc(sizeof(t_position));
	if (!map->player->dir)
		exit_close_msg(game->fd, ERR_MALLOC, game, NULL);
	map->player->pos->x = -1;
	map->player->pos->y = -1;
	map->player->dir->x = 0;
	map->player->dir->y = 0;
}

static void	init_mlx(t_mlx *mlx)
{
	mlx->mlx_ptr = mlx_init();
	if (!mlx->mlx_ptr)
		ft_exit_error("Error\nmlx_init failed\n");
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, 1920, 1080, "cub3d");
	if (!mlx->win_ptr)
		ft_exit_error("Error\nmlx_new_window failed\n");
}

void	init_game(t_game *game, char *name_file)
{
	game->fd = open(name_file, O_RDONLY);
	if (game->fd == -1)
	{
		free(game);
		ft_exit_error(ERR_OPEN);
	}
	game->data = malloc(sizeof(t_data));
	if (!game->data)
		exit_close_msg(game->fd, ERR_MALLOC, game, NULL);
	init_data(game);
	game->map = malloc(sizeof(t_map));
	if (!game->map)
		exit_close_msg(game->fd, ERR_MALLOC, game, NULL);
	init_map(game, game->map);
	parse_file(game);
	if (check_parse(game->data))
		exit_close_msg(game->fd, ERR_PARSE, game, NULL);
	game->mlx = malloc(sizeof(t_mlx));
	if (!game->mlx)
		ft_exit_error(ERR_MALLOC);
	init_mlx(game->mlx);
	game->ray = malloc(sizeof(t_ray));
	if (!game->ray)
		ft_exit_error(ERR_MALLOC);
	ft_init_textures(game);
}
