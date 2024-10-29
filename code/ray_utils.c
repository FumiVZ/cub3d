/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:02:42 by vzuccare          #+#    #+#             */
/*   Updated: 2024/10/29 11:39:54 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	get_texture_color(t_texture *tex, double texture_offset, int tex_x)
{
	int	tex_y;
	int	color;

	tex_y = (int)texture_offset;
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= tex->width)
		tex_x = tex->width - 1;
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= tex->height)
		tex_y = tex->height - 1;
	color = *(int *)(tex->addr + (tex_y * tex->line_len + tex_x * (tex->bpp
					/ 8)));
	return (color);
}

void	ft_init_textures(t_game *game)
{
	game->wall_t[0] = malloc(sizeof(t_texture));
	game->wall_t[0] = ft_new_texture(game->mlx->mlx_ptr, game->data->no,
			game->wall_t[0], game);
	if (!game->wall_t[0])
		exit_close_msg(game->fd, ERR_MLX, game, NULL);
	game->wall_t[1] = malloc(sizeof(t_texture));
	game->wall_t[1] = ft_new_texture(game->mlx->mlx_ptr, game->data->so,
			game->wall_t[1], game);
	if (!game->wall_t[1])
		exit_close_msg(game->fd, ERR_MLX, game, NULL);
	game->wall_t[2] = malloc(sizeof(t_texture));
	game->wall_t[2] = ft_new_texture(game->mlx->mlx_ptr, game->data->ea,
			game->wall_t[2], game);
	if (!game->wall_t[2])
		exit_close_msg(game->fd, ERR_MLX, game, NULL);
	game->wall_t[3] = malloc(sizeof(t_texture));
	game->wall_t[3] = ft_new_texture(game->mlx->mlx_ptr, game->data->we,
			game->wall_t[3], game);
	if (!game->wall_t[3])
		exit_close_msg(game->fd, ERR_MLX, game, NULL);
}

void	put_pixel(t_game *game, int x, int y)
{
	char	*dst;

	dst = game->mlx->addr + (y * game->mlx->line_length + x
			* (game->mlx->bits_per_pixel / 8));
	*(unsigned int *)dst = game->color;
}

float	normalize_angle(float angle)
{
	if (angle > 2 * PI)
		angle -= 2 * PI;
	if (angle < 0)
		angle += 2 * PI;
	return (angle);
}
