/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 16:45:36 by machrist          #+#    #+#             */
/*   Updated: 2024/09/28 23:47:43 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	ft_rotate_player(t_game *game, int direction)
{
	double	old_dir_x;
	double	old_plane_x;
	double	angle;

	angle = direction * 5;
	old_dir_x = game->map->player->dir->x;
	game->map->player->dir->x = game->map->player->dir->x * cos(angle * M_PI
			/ 180.0) - game->map->player->dir->y * sin(angle * M_PI / 180.0);
	game->map->player->dir->y = old_dir_x * sin(angle * M_PI / 180.0)
		+ game->map->player->dir->y * cos(angle * M_PI / 180.0);
	old_plane_x = game->map->player->dir->x;
	game->map->player->dir->x = game->map->player->dir->x * cos(angle * M_PI
			/ 180.0) - game->map->player->dir->y * sin(angle * M_PI / 180.0);
	game->map->player->dir->y = old_plane_x * sin(angle * M_PI / 180.0)
		+ game->map->player->dir->y * cos(angle * M_PI / 180.0);
	ft_render_map(game);
}

static void	ft_move_player(t_game *game, double x, double y)
{
	if (game->map->map[(int)(game->map->player->pos->y
			+ y)][(int)(game->map->player->pos->x + x)] == '1')
		return ;
	game->map->player->pos->x += x;
	game->map->player->pos->y += y;
	ft_render_map(game);
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_ESC || keycode == KEY_Q)
		ft_close_game(game);
	if (keycode == ROTATE_LEFT)
	{
		ft_rotate_player(game, 1.1);
	}
	if (keycode == ROTATE_RIGHT)
	{
		ft_rotate_player(game, -1.1);
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
