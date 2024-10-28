/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 16:41:25 by machrist          #+#    #+#             */
/*   Updated: 2024/10/28 18:42:23 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	ft_init_textures(t_game *game)
{
	game->wall_t[0] = ft_new_texture(game->mlx->mlx_ptr, game->data->no, game->wall_t[0], game);
	if (!game->wall_t[0])
		exit_close_msg(game->fd, ERR_MLX, game, NULL);
	game->wall_t[1] = ft_new_texture(game->mlx->mlx_ptr, game->data->so, game->wall_t[1], game);
	if (!game->wall_t[1])
		exit_close_msg(game->fd, ERR_MLX, game, NULL);
	game->wall_t[2] = ft_new_texture(game->mlx->mlx_ptr, game->data->ea, game->wall_t[2], game);
	if (!game->wall_t[2])
		exit_close_msg(game->fd, ERR_MLX, game, NULL);
	game->wall_t[3] = ft_new_texture(game->mlx->mlx_ptr, game->data->we, game->wall_t[3], game);
	if (!game->wall_t[3])
		exit_close_msg(game->fd, ERR_MLX, game, NULL);
}

void put_pixel(t_game *game, int x, int y, int color)
{
	char	*dst;

	dst = game->mlx->addr + (y * game->mlx->line_length + x
			* (game->mlx->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

static float	fish_eye_correction(float player_x, float player_y, float ray_x,
		float ray_y, t_game *game)
{
	float	dist;
	float	angle;
	float	player_angle;
	float	ray_angle;

	// Calculer l'angle du rayon
	ray_angle = atan2(ray_y - player_y, ray_x - player_x);
	// Convertir l'angle du joueur en radians
	player_angle = game->map->player->angle;
	// Calculer la différence d'angle
	angle = ray_angle - player_angle;
	// Normaliser l'angle entre -PI et PI
	while (angle > PI)
		angle -= 2 * PI;
	while (angle < -PI)
		angle += 2 * PI;
	// Calculer la distance euclidienne
	dist = sqrt((ray_x - player_x) * (ray_x - player_x) + 
		(ray_y - player_y) * (ray_y - player_y));
	// Appliquer la correction fish-eye
	return (dist * cos(angle));
}

bool	wall_touch(float player_x, float player_y, t_game *game)
{
	int	x;
	int	y;

	x = player_x / 32;
	y = player_y / 32;
	if (game->map->map[y][x] == '1')
		return (true);
	return (false);
}

int	get_texture_color(t_texture *tex, double texture_offset, int tex_x)
{
	int	tex_y;
	int	color;

	tex_y = (int)texture_offset;
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= TEX_WIDTH)
		tex_x = TEX_WIDTH - 1;
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= TEX_HEIGHT)
		tex_y = TEX_HEIGHT - 1;
	color = *(int *)(tex->addr + (tex_y * tex->line_len + tex_x
				* (tex->bpp / 8)));
	return (color);
}

void	draw_line(t_game *game, float start_x, int i)
{
	t_ray	*ray;
	int		y;
	double	texture_offset;
	int		tex_x;
	float	prev_x, prev_y;
	int		wall_face;

	ray = game->ray;
	ray->cos_angle = cos(start_x);
	ray->sin_angle = sin(start_x);
	ray->x = game->map->player->pos->x;
	ray->y = game->map->player->pos->y;
	while (!wall_touch(ray->x, ray->y, game))
	{
		prev_x = ray->x;
		prev_y = ray->y;
		ray->x += ray->cos_angle;
		ray->y += ray->sin_angle;
	}
	if (floor(prev_x / TILE_SIZE) != floor(ray->x / TILE_SIZE))
	{
		if (ray->cos_angle > 0)
			wall_face = WEST;
		else
			wall_face = EAST;
		tex_x = (int)(fmod(ray->y, TILE_SIZE) * TEX_WIDTH / TILE_SIZE);
	}
	else
	{
		if (ray->sin_angle > 0)
			wall_face = NORTH;
		else
			wall_face = SOUTH;
		tex_x = (int)(fmod(ray->x, TILE_SIZE) * TEX_WIDTH / TILE_SIZE);
	}
	if (wall_face == WEST || wall_face == SOUTH)
		tex_x = TEX_WIDTH - tex_x - 1;

	ray->dist = fish_eye_correction(game->map->player->pos->x,
			game->map->player->pos->y, ray->x, ray->y, game);
	ray->line_height = (int)((32 / ray->dist) * (WIDTH / 2));
	ray->draw_start = (HEIGHT - ray->line_height) / 2;
	ray->draw_end = ray->draw_start + ray->line_height;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	if (ray->draw_end >= HEIGHT)
		ray->draw_end = HEIGHT - 1;
	y = ray->draw_start - 1;
	while (++y < ray->draw_end)
	{
		// Correction du calcul de texture_offset
		texture_offset = (y - ray->draw_start) * (double)TEX_HEIGHT 
			/ (ray->draw_end - ray->draw_start);
		if (game->wall_t[wall_face] && game->wall_t[wall_face]->addr)
		{
			game->ray->texture_color = get_texture_color(game->wall_t[wall_face],
					texture_offset, tex_x);
			put_pixel(game, i, y, game->ray->texture_color);
		}
	}
}
