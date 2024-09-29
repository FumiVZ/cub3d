/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:43:59 by vzuccare          #+#    #+#             */
/*   Updated: 2024/09/29 00:46:11 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	init_data(t_data *data)
{
	data->no = NULL;
	data->so = NULL;
	data->we = NULL;
	data->ea = NULL;
	data->c = NULL;
	data->f = NULL;
}

static void	init_map(t_map *map)
{
	map->map = NULL;
	map->map_x = 0;
	map->map_y = 0;
	map->player = malloc(sizeof(t_player));
	if (!map->player)
		ft_exit_error(ERR_MALLOC);
	map->player->pos = malloc(sizeof(t_position));
	if (!map->player->pos)
		ft_exit_error(ERR_MALLOC);
	map->player->dir = malloc(sizeof(t_position));
	if (!map->player->dir)
		ft_exit_error(ERR_MALLOC);
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

static void	init_ray(t_ray *ray, t_game *game)
{
	ray->player = game->map->player;
	ray->plane.x = 0;
	ray->plane.y = 0.66;
	ray->x = 0;
	ray->camerax = 0;
	ray->raydir.x = 0;
	ray->raydir.y = 0;
	ray->mapx = 0;
	ray->mapy = 0;
	ray->deltadist.x = 0;
	ray->deltadist.y = 0;
	ray->sidedist.x = 0;
	ray->sidedist.y = 0;
	ray->hit = 0;
	ray->stepx = 0;
	ray->stepy = 0;
	ray->side = 0;
	ray->perpwalldist = 0;
	ray->lineheight = 0;
	ray->drawstart = 0;
	ray->drawend = 0;
}

void	init_game(t_game *game)
{
	game->data = malloc(sizeof(t_data));
	if (!game->data)
		ft_exit_error(ERR_MALLOC);
	init_data(game->data);
	game->map = malloc(sizeof(t_map));
	if (!game->map)
		ft_exit_error(ERR_MALLOC);
	init_map(game->map);
	game->mlx = malloc(sizeof(t_mlx));
	if (!game->mlx)
		ft_exit_error(ERR_MALLOC);
	init_mlx(game->mlx);
	game->ray = malloc(sizeof(t_ray));
	if (!game->ray)
		ft_exit_error(ERR_MALLOC);
	init_ray(game->ray, game);
	ft_init_textures(game);
}