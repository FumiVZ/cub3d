/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 16:45:36 by machrist          #+#    #+#             */
/*   Updated: 2024/09/28 22:17:17 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <math.h>

void	draw_vision(t_game *game)
{
	double	ray_x, ray_y, dir_x, dir_y, ray_length = 35, step_size = 0.1, fov = 60, angle;
	int		num_rays = 100, prev_x, prev_y, curr_x, curr_y, i = 0;

	while (i < num_rays)
	{
		angle = (game->map->player->dir->x - fov / 2.0) + (i * fov / num_rays);
		ray_x = game->map->player->pos->x;
		ray_y = game->map->player->pos->y;
		dir_x = cos(angle * M_PI / 180.0);
		dir_y = sin(angle * M_PI / 180.0);
		double t = 0;
		while (t < ray_length)
		{
			prev_x = (int)(ray_x * TILE_SIZE);
			prev_y = (int)(ray_y * TILE_SIZE);
			ray_x += dir_x * step_size;
			ray_y += dir_y * step_size;
			curr_x = (int)(ray_x * TILE_SIZE);
			curr_y = (int)(ray_y * TILE_SIZE);
			if (game->map->map[(int)ray_y][(int)ray_x] == '1')
				break ;
			mlx_pixel_put(game->mlx->mlx_ptr, game->mlx->win_ptr, prev_x, prev_y, 0xFF0000);
			mlx_pixel_put(game->mlx->mlx_ptr, game->mlx->win_ptr, curr_x, curr_y, 0xFF0000);
			t += step_size;
		}
		i++;
	}
}

void	ft_rotate_player(t_game *game, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->map->player->dir->x;
	game->map->player->dir->x = game->map->player->dir->x * cos(angle)
		- game->map->player->dir->y * sin(angle);
	game->map->player->dir->y = old_dir_x * sin(angle)
		+ game->map->player->dir->y * cos(angle);
	old_plane_x = game->ray->plane.x;
	game->ray->plane.x = game->ray->plane.x * cos(angle)
		- game->ray->plane.y * sin(angle);
	game->ray->plane.y = old_plane_x * sin(angle)
		+ game->ray->plane.y * cos(angle);
	ft_render_map(game);
	ft_render_texture(game, game->data->player, game->map->player->pos->y,
		game->map->player->pos->x);
	draw_vision(game);
}

void	ft_move_player(t_game *game, double x, double y)
{
	if (game->map->map[(int)(game->map->player->pos->y
			+ y)][(int)(game->map->player->pos->x + x)] == '1')
		return ;
	game->map->player->pos->x += x;
	game->map->player->pos->y += y;
	ft_render_map(game);
	ft_render_texture(game, game->data->player, game->map->player->pos->y,
		game->map->player->pos->x);
	draw_vision(game);
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_ESC || keycode == KEY_Q)
		ft_close_game(game);
	if (keycode == ROTATE_LEFT)
	{
		ft_rotate_player(game, -0.1);
	}
	if (keycode == ROTATE_RIGHT)
	{
		ft_rotate_player(game, 0.1);
	}
	if (keycode == FORWARD_W_Z)
		ft_move_player(game, 0, 0.1);
	if (keycode == BACK_S_S)
		ft_move_player(game, 0, -0.1);
	if (keycode == RIGHT_D_D)
		ft_move_player(game, 0.1, 0);
	if (keycode == LEFT_A_Q)
		ft_move_player(game, -0.1, 0);
	return (0);
}
