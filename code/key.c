/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 16:45:36 by machrist          #+#    #+#             */
/*   Updated: 2024/10/25 16:51:51 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

/* static void	ft_handle_rotation(int keycode, t_game *game)
{
	if (keycode == ROTATE_LEFT)
		ft_rotate_player(game, -1.1);
	else if (keycode == ROTATE_RIGHT)
		ft_rotate_player(game, 1.1);
} */

int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_ESC || keycode == KEY_Q)
		ft_close_game(game);
	if (keycode == FORWARD_W_Z)
		game->map->player->up = true;
	if (keycode == BACK_S_S)
		game->map->player->down = true;
	if (keycode == RIGHT_D_D)
		game->map->player->right = true;
	if (keycode == LEFT_A_Q)
		game->map->player->left = true;
	if (keycode == ROTATE_LEFT)
		game->map->player->rotate_left = true;
	if (keycode == ROTATE_RIGHT)
		game->map->player->rotate_right = true;
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == FORWARD_W_Z)
		game->map->player->up = false;
	if (keycode == BACK_S_S)
		game->map->player->down = false;
	if (keycode == RIGHT_D_D)
		game->map->player->right = false;
	if (keycode == LEFT_A_Q)
		game->map->player->left = false;
	if (keycode == ROTATE_LEFT)
		game->map->player->rotate_left = false;
	if (keycode == ROTATE_RIGHT)
		game->map->player->rotate_right = false;
	return (0);
}