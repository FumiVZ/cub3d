/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:43:59 by vzuccare          #+#    #+#             */
/*   Updated: 2024/09/29 18:43:36 by vzuccare         ###   ########lyon.fr   */
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

static void	init_map(t_game *game)
{
	game->map->map = NULL;
	game->map->map_x = 0;
	game->map->map_y = 0;
	game->map->player = malloc(sizeof(t_player));
	if (!game->map->player)
		exit_close_msg(game->fd, ERR_MALLOC, game);
	game->map->player->pos = malloc(sizeof(t_position));
	if (!game->map->player->pos)
		exit_close_msg(game->fd, ERR_MALLOC, game);
	game->map->player->dir = malloc(sizeof(t_position));
	if (!game->map->player->dir)
		exit_close_msg(game->fd, ERR_MALLOC, game);
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

void	init_game(t_game *game, char *name_file)
{
	game->fd = open(name_file, O_RDONLY);
	if (game->fd == -1)
		exit_close_msg(game->fd, ERR_OPEN, NULL);
	game->data = malloc(sizeof(t_data));
	if (!game->data)
		exit_close_msg(game->fd, ERR_MALLOC, game);
	init_data(game);
	game->map = malloc(sizeof(t_map));
	if (!game->map)
		exit_close_msg(game->fd, ERR_MALLOC, game);
	init_map(game);
	parse_file(game);
	if (check_parse(game->data))
		exit_close_msg(game->fd, ERR_PARSE, game);
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
