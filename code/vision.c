/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vision.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 23:44:49 by machrist          #+#    #+#             */
/*   Updated: 2024/09/28 23:47:07 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static double	calculate_dir_x(double angle)
{
	return (cos(angle * M_PI / 180.0));
}

static double	calculate_dir_y(double angle)
{
	return (sin(angle * M_PI / 180.0));
}

static int	convert_to_pixel(double coordinate)
{
	return ((int)(coordinate * TILE_SIZE));
}

static void	draw_ray(t_game *game, double angle)
{
	double	ray_x;
	double	ray_y;
	double	t;

	ray_x = game->map->player->pos->x;
	ray_y = game->map->player->pos->y;
	t = 0;
	while (t < RAY_LENGTH)
	{
		ray_x += calculate_dir_x(angle) * STEP_SIZE;
		ray_y += calculate_dir_y(angle) * STEP_SIZE;
		if (game->map->map[(int)ray_y][(int)ray_x] == '1')
			break ;
		mlx_pixel_put(game->mlx->mlx_ptr, game->mlx->win_ptr,
			convert_to_pixel(ray_x), convert_to_pixel(ray_y), 0x00FF00);
		t += STEP_SIZE;
	}
}

void	draw_vision(t_game *game)
{
	int		i;
	double	angle;
	double	player_angle;

	i = 0;
	player_angle = atan2(game->map->player->dir->y, game->map->player->dir->x)
		* 180.0 / M_PI;
	while (i < NB_RAYS)
	{
		angle = (player_angle - FOV / 2.0) + (i * FOV / NB_RAYS);
		draw_ray(game, angle);
		i++;
	}
}
