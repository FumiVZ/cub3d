/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 16:41:25 by machrist          #+#    #+#             */
/*   Updated: 2024/10/28 16:46:43 by vzuccare         ###   ########lyon.fr   */
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

float	normalize_angle(float angle)
{
	if (angle > 2 * PI)
		angle -= 2 * PI;
	if (angle < 0)
		angle += 2 * PI;
	return (angle);
}

static float	fish_eye_correction(float player_x, float player_y, float ray_x,
		float ray_y, t_game *game)
{
	float	x;
	float	y;
	float	dist;
	float	angle;

	x = ray_x - player_x;
	y = ray_y - player_y;
	angle = normalize_angle(atan2(y, x) - game->map->player->angle);
	dist = get_dist(x, y) * cos(angle);
	return (dist);
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

int	get_texture_color(t_texture *texture, double texture_offset, int tex_x)
{
	int	tex_y;
	int	color;

	tex_y = (int)texture_offset;
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= 32)
		tex_x = 32 - 1;
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= 32)
		tex_y = 32 - 1;
	color = *(int *)(texture->addr + (tex_y * texture->line_len + tex_x
				* (texture->bpp / 8)));
	return (color);
}

void draw_line(t_game *game, float start_x, int i)
{
    t_ray *ray;
    int y;
    int wall_face;
    double texture_offset;
    double wall_x;
    int tex_x;

    ray = game->ray;
    ray->cos_angle = cos(start_x);
    ray->sin_angle = sin(start_x);
    ray->x = game->map->player->pos->x;
    ray->y = game->map->player->pos->y;
    while (!wall_touch(ray->x, ray->y, game))
    {
        ray->x += ray->cos_angle;
        ray->y += ray->sin_angle;
    }
    ray->dist = fish_eye_correction(game->map->player->pos->x,
                                    game->map->player->pos->y, ray->x, ray->y, game);
    ray->line_height = (int)((32 / ray->dist) * (WIDTH / 2));
    ray->draw_start = (HEIGHT - ray->line_height) / 2;
    ray->draw_end = ray->draw_start + ray->line_height;
    if (ray->draw_start < 0)
        ray->draw_start = 0;
    if (ray->draw_end >= HEIGHT)
        ray->draw_end = HEIGHT - 1;
    if (fabs(ray->sin_angle) > fabs(ray->cos_angle))
    {
        wall_x = fmod(ray->x, TILE_SIZE);
        wall_face = (ray->sin_angle > 0) ? NORTH : SOUTH;
    }
    else
    {
        wall_x = fmod(ray->y, TILE_SIZE);
        wall_face = (ray->cos_angle > 0) ? EAST : WEST;
    }
    tex_x = (int)(wall_x * (TEX_WIDTH / TILE_SIZE));
    y = ray->draw_start - 1;
    while (++y < ray->draw_end)
    {
        texture_offset = (y - ray->draw_start) * TEX_HEIGHT / ray->line_height;
        game->ray->texture_color = get_texture_color(game->wall_t[wall_face], texture_offset, tex_x);
        put_pixel(game, i, y, game->ray->texture_color); 
	}
}