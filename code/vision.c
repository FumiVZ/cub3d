/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vision.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 23:44:49 by machrist          #+#    #+#             */
/*   Updated: 2024/10/25 14:45:58 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

double	get_direction_x(double angle)
{
	return (cos(angle * M_PI / 180.0));
}

double	get_direction_y(double angle)
{
	return (sin(angle * M_PI / 180.0));
}

/* static int	coordinate_to_pixel(double coordinate)
{
	return ((int)(coordinate * TILE_SIZE));
}

static void	render_ray(t_game *game, double angle)
{
	double	ray_x;
	double	ray_y;
	double	t;

	ray_x = game->map->player->pos->x;
	ray_y = game->map->player->pos->y;
	t = 0;
	while (t < RAY_LENGTH)
	{
		ray_x += get_direction_x(angle) * STEP_SIZE;
		ray_y += get_direction_y(angle) * STEP_SIZE;
		if (game->map->map[(int)ray_y][(int)ray_x] == '1')
			break ;
		mlx_pixel_put(game->mlx->mlx_ptr, game->mlx->win_ptr,
			coordinate_to_pixel(ray_x), coordinate_to_pixel(ray_y), 0x00FF00);
		t += STEP_SIZE;
	}
} */

/* void	draw_vision(t_game *game)
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
		render_ray(game, angle);
		i++;
	}
	draw_3d_projection(game);
}
 */