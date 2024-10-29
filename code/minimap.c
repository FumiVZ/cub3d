/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:48:10 by vzuccare          #+#    #+#             */
/*   Updated: 2024/10/29 13:45:38 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_texture	*ft_new_texture(void *mlx, char *path, t_texture *tex, t_game *game)
{
	if (!tex)
		exit_close_msg(game->fd, ERR_MALLOC, game, NULL);
	tex->img = mlx_xpm_file_to_image(mlx, path, &tex->width, &tex->height);
	if (!tex->img)
		exit_close_msg(game->fd, ERR_MLX, game, NULL);
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp, &tex->line_len,
			&tex->endian);
	if (!tex->addr)
		exit_close_msg(game->fd, ERR_MLX, game, NULL);
	return (tex);
}

void	draw_square(int x, int y, int color, t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->size)
	{
		j = 0;
		while (j < game->size)
		{
			game->color = color;
			put_pixel(game, x + j, y + i);
			j++;
		}
		i++;
	}
}

void	draw_mini_map(t_game *game)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < game->map->map_y)
	{
		j = 0;
		while (j < game->map->map_x)
		{
			game->size = 64;
			if (game->map->map[i][j] == '1')
				draw_square(j * 8, i * 8, 0x00FF00, game);
			else if (game->map->map[i][j] == '0')
				draw_square(j * 8, i * 8, 0x000000, game);
			j++;
		}
		i++;
	}
	game->size = 4;
}

int	ft_render_map(t_game *game)
{
	float	frac;
	float	start;
	int		i;
	float	fov_angle;
	float	half_fov;

	fov_angle = PI / 3;
	half_fov = fov_angle / 2;
	ft_move_player(game);
	mlx_clear_window(game->mlx->mlx_ptr, game->mlx->win_ptr);
	floor_cell(game);
	frac = fov_angle / WIDTH;
	start = game->map->player->angle - half_fov;
	i = -1;
	while (++i < WIDTH)
	{
		draw_line(game, start, i);
		start += frac;
	}
	draw_mini_map(game);
	draw_square(game->map->player->pos->x / 4, game->map->player->pos->y / 4,
		0xFF0000, game);
	mlx_put_image_to_window(game->mlx->mlx_ptr, game->mlx->win_ptr,
		game->mlx->img_ptr, 0, 0);
	return (0);
}
