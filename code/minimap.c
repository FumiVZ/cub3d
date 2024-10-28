/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:48:10 by vzuccare          #+#    #+#             */
/*   Updated: 2024/10/28 18:23:10 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_texture *ft_new_texture(void *mlx, char *path, t_texture *tex, t_game *game)
{
	tex->img = mlx_xpm_file_to_image(mlx, path, &tex->width, &tex->height);
	if (!tex->img)
		exit_close_msg(game->fd, ERR_MLX, game, NULL);
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp,
			&tex->line_len, &tex->endian);
	if (!tex->addr)
		exit_close_msg(game->fd, ERR_MLX, game, NULL);
	return (tex);
}

static void	clear_window(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			put_pixel(game, j, i, 0x000000);
			j++;
		}
		i++;
	}
}

void	draw_square(int x, int y, int color, int size, t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			put_pixel(game, x + j, y + i, color);
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
			if (game->map->map[i][j] == '1')
				draw_square(j * 8, i * 8, 0x00FF00, 64, game);
			else if (game->map->map[i][j] == '0')
				draw_square(j * 8, i * 8, 0x000000, 64, game);
			j++;
		}
		i++;
	}
}

float	get_dist(float x, float y)
{
	return (sqrt(x * x + y * y));
}

int	ft_render_map(t_game *game)
{
	float	frac;
	float	start;
	int		i;

	ft_move_player(game);
	clear_window(game);
	floor_cell(game);
	frac = PI / 3 / WIDTH;
	start = game->map->player->angle - PI / 6;
	i = -1;
	while (++i < WIDTH)
	{
		draw_line(game, start, i);
		start += frac;
	}
	draw_mini_map(game);
	draw_square(game->map->player->pos->x / 4, game->map->player->pos->y / 4,
		0xFF0000, 2, game);
	mlx_put_image_to_window(game->mlx->mlx_ptr, game->mlx->win_ptr,
		game->mlx->img_ptr, 0, 0);
	return (0);
}
