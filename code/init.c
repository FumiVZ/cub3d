/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:43:59 by vzuccare          #+#    #+#             */
/*   Updated: 2024/10/30 16:44:26 by vzuccare         ###   ########lyon.fr   */
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
	map->player->pos->x = -2;
	map->player->pos->y = -2;
	map->player->dir->x = 0;
	map->player->dir->y = 0;
}

static void	init_mlx(t_mlx *mlx, t_game *game)
{
	mlx->mlx_ptr = mlx_init();
	if (!mlx->mlx_ptr)
		exit_close_msg(0, ERR_MLX, game, NULL);
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, WIDTH, HEIGHT, "Cub3D");
	if (!mlx->win_ptr)
		exit_close_msg(0, ERR_MLX, game, NULL);
	mlx->img_ptr = mlx_new_image(mlx->mlx_ptr, WIDTH, HEIGHT);
	if (!mlx->img_ptr)
	{
		fprintf(stderr, "Error: Failed to create image\n");
		mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
		exit_close_msg(0, ERR_MLX, game, NULL);
	}
	mlx->addr = mlx_get_data_addr(mlx->img_ptr, &mlx->bits_per_pixel,
			&mlx->line_length, &mlx->endian);
	if (!mlx->addr)
	{
		fprintf(stderr, "Error: Failed to get image address\n");
		exit_close_msg(0, ERR_MLX, game, NULL);
	}
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
		exit_close_msg(game->fd, ERR_MALLOC, game, NULL);
	init_mlx(game->mlx, game);
	game->ray = malloc(sizeof(t_ray));
	if (!game->ray)
		exit_close_msg(game->fd, ERR_MALLOC, game, NULL);
	ft_init_textures(game);
}
