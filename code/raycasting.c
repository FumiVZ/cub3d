/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 16:41:25 by machrist          #+#    #+#             */
/*   Updated: 2024/10/29 11:39:19 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

bool	wall_touch(float player_x, float player_y, t_game *game)
{
	int	map_x;
	int	map_y;

	map_x = (int)(player_x / TILE_SIZE);
	map_y = (int)(player_y / TILE_SIZE);
	if (map_x < 0 || map_x >= (int)game->map->map_x || map_y < 0
		|| map_y >= (int)game->map->map_y)
		return (true);
	if (game->map->map[map_y][map_x] == '1')
		return (true);
	return (false);
}

static float	fish_eye_correction(float ray_x, float ray_y, t_game *game)
{
	double	dist;
	float	angle;
	float	player_angle;
	float	ray_angle;

	ray_angle = atan2(ray_y - game->map->player->pos->y, ray_x
			- game->map->player->pos->x);
	player_angle = game->map->player->angle;
	angle = ray_angle - player_angle;
	while (angle > PI)
		angle -= 2 * PI;
	while (angle < -PI)
		angle += 2 * PI;
	dist = sqrt((ray_x - game->map->player->pos->x) * (ray_x
				- game->map->player->pos->x) + (ray_y
				- game->map->player->pos->y) * (ray_y
				- game->map->player->pos->y));
	return (dist * cos(angle));
}

static int	identify_wall_face(t_game *game, float prev_x, float prev_y)
{
	int	tex_x;

	(void)prev_y;
	if (floor(prev_x / TILE_SIZE) != floor(game->ray->x / TILE_SIZE))
	{
		if (game->ray->cos_angle > 0)
			game->ray->wall_face = WEST;
		else
			game->ray->wall_face = EAST;
		tex_x = (int)(fmod(game->ray->y, TILE_SIZE)
				* game->wall_t[game->ray->wall_face]->width / TILE_SIZE);
	}
	else
	{
		if (game->ray->sin_angle > 0)
			game->ray->wall_face = NORTH;
		else
			game->ray->wall_face = SOUTH;
		tex_x = (int)(fmod(game->ray->x, TILE_SIZE)
				* game->wall_t[game->ray->wall_face]->width / TILE_SIZE);
	}
	return (tex_x);
}

void	init_ray(t_game *game, float start_x, float *prev_x, float *prev_y)
{
	game->ray->cos_angle = cos(start_x);
	game->ray->sin_angle = sin(start_x);
	game->ray->x = game->map->player->pos->x;
	game->ray->y = game->map->player->pos->y;
	while (!wall_touch(game->ray->x, game->ray->y, game))
	{
		*prev_x = game->ray->x;
		*prev_y = game->ray->y;
		game->ray->x += game->ray->cos_angle;
		game->ray->y += game->ray->sin_angle;
	}
	game->ray->tex_x = identify_wall_face(game, *prev_x, *prev_y);
	if (game->ray->wall_face == WEST || game->ray->wall_face == SOUTH)
		game->ray->tex_x = game->wall_t[game->ray->wall_face]->width
			- game->ray->tex_x - 1;
	game->ray->dist = fish_eye_correction(game->ray->x, game->ray->y, game);
	game->ray->line_height = (int)((32 / game->ray->dist) * (WIDTH / 2));
	game->ray->draw_start = (HEIGHT - game->ray->line_height) / 2;
	game->ray->draw_end = game->ray->draw_start + game->ray->line_height;
}

void	draw_line(t_game *game, float start_x, int i)
{
	int		y;
	double	texture_offset;
	float	prev_x;
	float	prev_y;

	init_ray(game, start_x, &prev_x, &prev_y);
	if (game->ray->draw_start < 0)
		game->ray->draw_start = 0;
	if (game->ray->draw_end >= HEIGHT)
		game->ray->draw_end = HEIGHT - 1;
	y = game->ray->draw_start - 1;
	while (++y < game->ray->draw_end)
	{
		texture_offset = (y - game->ray->draw_start)
			* (double)game->wall_t[game->ray->wall_face]->width
			/ (game->ray->draw_end - game->ray->draw_start);
		if (game->wall_t[game->ray->wall_face]
			&& game->wall_t[game->ray->wall_face]->addr)
		{
			game->color = get_texture_color(game->wall_t[game->ray->wall_face],
					texture_offset, game->ray->tex_x);
			put_pixel(game, i, y);
		}
	}
}
