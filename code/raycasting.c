/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 16:41:25 by machrist          #+#    #+#             */
/*   Updated: 2024/09/29 00:45:37 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static double	calculate_perp_wall_dist(t_game *game, double ray_angle)
{
	double	ray_x;
	double	ray_y;
	double	t;

	ray_x = game->map->player->pos->x;
	ray_y = game->map->player->pos->y;
	t = 0;
	while (t < RAY_LENGTH)
	{
		ray_x += get_direction_x(ray_angle) * STEP_SIZE;
		ray_y += get_direction_y(ray_angle) * STEP_SIZE;
		if (game->map->map[(int)ray_y][(int)ray_x] == '1')
			break ;
		t += STEP_SIZE;
	}
	return (t);
}

static void	draw_vertical_line(t_game *game, int x, int draw_start,
		int draw_end)
{
	int	y;

	y = draw_start;
	while (y < draw_end)
	{
		mlx_pixel_put(game->mlx->mlx_ptr, game->mlx->win_ptr, x + 400, y,
			0xFF00FF);
		y++;
	}
}

static void	render_3d_projection(t_game *game, int x, double perp_wall_dist)
{
	int	line_height;
	int	draw_start;
	int	draw_end;

	line_height = (int)(HEIGHT / perp_wall_dist);
	draw_start = -line_height / 2 + HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + HEIGHT / 2;
	if (draw_end >= HEIGHT)
		draw_end = HEIGHT - 1;
	draw_vertical_line(game, x, draw_start, draw_end);
}

void	draw_3d_projection(t_game *game)
{
	int		x;
	double	ray_angle;
	double	perp_wall_dist;

	x = 0;
	while (x < HEIGHT)
	{
		ray_angle = (game->map->player->dir->x - FOV / 2.0) + (x * FOV
				/ HEIGHT);
		perp_wall_dist = calculate_perp_wall_dist(game, ray_angle);
		render_3d_projection(game, x, perp_wall_dist);
		x++;
	}
}
