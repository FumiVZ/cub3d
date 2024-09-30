/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 16:45:36 by machrist          #+#    #+#             */
/*   Updated: 2024/09/30 15:52:29 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	ft_handle_rotation(int keycode, t_game *game)
{
	if (keycode == ROTATE_LEFT)
		ft_rotate_player(game, -1.1);
	else if (keycode == ROTATE_RIGHT)
		ft_rotate_player(game, 1.1);
}

static void	ft_handle_movement(int keycode, t_game *game)
{
	if (keycode == FORWARD_W_Z)
		ft_move_player(game, 0.1);
	else if (keycode == BACK_S_S)
		ft_move_player(game, -0.1);
	else if (keycode == RIGHT_D_D)
		ft_strafe_player(game, -0.1);
	else if (keycode == LEFT_A_Q)
		ft_strafe_player(game, 0.1);
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_ESC || keycode == KEY_Q)
		ft_close_game(game);
	else
	{
		ft_handle_rotation(keycode, game);
		ft_handle_movement(keycode, game);
	}
	return (0);
}
