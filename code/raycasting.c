/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 16:41:25 by machrist          #+#    #+#             */
/*   Updated: 2024/09/30 15:53:35 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static int	get_texture_color(void *texture_ptr, int x, int y)
{
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	char	*pixel_data;

	pixel_data = mlx_get_data_addr(texture_ptr, &bits_per_pixel, &size_line,
			&endian);
	return (*(unsigned int *)(pixel_data + (y * size_line + x * (bits_per_pixel
					/ 8))));
}

static double	calculate_perpendicular_wall_distance(t_game *game,
		double ray_angle)
{
	double	ray_x;
	double	ray_y;
	double	distance;

	ray_x = game->map->player->pos->x;
	ray_y = game->map->player->pos->y;
	distance = 0;
	while (distance < RAY_LENGTH)
	{
		ray_x += get_direction_x(ray_angle) * STEP_SIZE;
		ray_y += get_direction_y(ray_angle) * STEP_SIZE;
		if (game->map->map[(int)ray_y][(int)ray_x] == '1')
			break ;
		distance += STEP_SIZE;
	}
	return (distance);
}

static void	draw_vertical_line(t_game *game, int x, int draw_start,
		int draw_end, int texture_x, char *image_data)
{
	int	y;
	int	texture_y;
	int	color;
	int	line_height;

	line_height = draw_end - draw_start;
	y = draw_start;
	while (y < draw_end)
	{
		texture_y = (int)(((double)(y - draw_start) / line_height)
				* TEX_HEIGHT);
		color = get_texture_color(game->data->wall.xpm_ptr, texture_x,
				texture_y);
		*(unsigned int *)(image_data + (y * WIDTH + (WIDTH - x - 1))
				* 4) = color;
		y++;
	}
}

static void	render_3d_projection(t_game *game, int x,
		double perpendicular_wall_distance, char *image_data)
{
	int	line_height;
	int	draw_start;
	int	draw_end;
	int	texture_x;

	line_height = (int)(HEIGHT / perpendicular_wall_distance);
	draw_start = -line_height / 2 + HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + HEIGHT / 2;
	if (draw_end >= HEIGHT)
		draw_end = HEIGHT - 1;
	texture_x = (int)(game->map->player->pos->x * TEX_WIDTH) % TEX_WIDTH;
	draw_vertical_line(game, x, draw_start, draw_end, texture_x, image_data);
}

void	draw_3d_projection(t_game *game)
{
	game->ray->image = mlx_new_image(game->mlx->mlx_ptr, WIDTH, HEIGHT);
	game->ray->image_data = mlx_get_data_addr(game->ray->image,
			&game->ray->bits_per_pixel, &game->ray->size_line,
			&game->ray->endian);
	game->ray->x = 0;
	while (game->ray->x < WIDTH)
	{
		game->ray->ray_angle = atan2(game->map->player->dir->y,
				game->map->player->dir->x) * 180.0 / M_PI + FOV / 2.0
			- game->ray->x * FOV / WIDTH;
		game->ray->perp_wall_dist = calculate_perpendicular_wall_distance(game,
				game->ray->ray_angle);
		game->ray->line_height = (int)(HEIGHT / game->ray->perp_wall_dist);
		game->ray->draw_start = -game->ray->line_height / 2 + HEIGHT / 2;
		if (game->ray->draw_start < 0)
			game->ray->draw_start = 0;
		game->ray->draw_end = game->ray->line_height / 2 + HEIGHT / 2;
		if (game->ray->draw_end >= HEIGHT)
			game->ray->draw_end = HEIGHT - 1;
		game->ray->texture_x = (int)(game->map->player->pos->x * TEX_WIDTH)
			% TEX_WIDTH;
		render_3d_projection(game, game->ray->x, game->ray->perp_wall_dist,
			game->ray->image_data);
		game->ray->x++;
	}
	mlx_put_image_to_window(game->mlx->mlx_ptr, game->mlx->win_ptr,
		game->ray->image, 600, 0);
	mlx_destroy_image(game->mlx->mlx_ptr, game->ray->image);
}
