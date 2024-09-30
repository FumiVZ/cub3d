/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 17:27:18 by machrist          #+#    #+#             */
/*   Updated: 2024/09/30 15:53:24 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	ft_rotate_player(t_game *game, double direction)
{
	double	old_dir_x;
	double	old_plane_x;
	double	angle;

	angle = direction * 1;
	old_dir_x = game->map->player->dir->x;
	game->map->player->dir->x = game->map->player->dir->x
		* get_direction_x(angle) - game->map->player->dir->y
		* get_direction_y(angle);
	game->map->player->dir->y = old_dir_x * get_direction_y(angle)
		+ game->map->player->dir->y * get_direction_x(angle);
	old_plane_x = game->map->player->dir->x;
	game->map->player->dir->x = game->map->player->dir->x
		* get_direction_x(angle) - game->map->player->dir->y
		* get_direction_y(angle);
	game->map->player->dir->y = old_plane_x * get_direction_y(angle)
		+ game->map->player->dir->y * get_direction_x(angle);
	ft_render_map(game);
}

void	ft_move_player(t_game *game, double move_speed)
{
	double	new_x;
	double	new_y;

	new_x = game->map->player->pos->x + game->map->player->dir->x * move_speed;
	new_y = game->map->player->pos->y + game->map->player->dir->y * move_speed;
	if (game->map->map[(int)new_y][(int)new_x] == '1')
		return ;
	game->map->player->pos->x = new_x;
	game->map->player->pos->y = new_y;
	ft_render_map(game);
}

void	ft_strafe_player(t_game *game, double strafe_speed)
{
	double	new_x;
	double	new_y;

	new_x = game->map->player->pos->x + game->map->player->dir->y
		* strafe_speed;
	new_y = game->map->player->pos->y - game->map->player->dir->x
		* strafe_speed;
	if (game->map->map[(int)new_y][(int)new_x] != '1')
	{
		game->map->player->pos->x = new_x;
		game->map->player->pos->y = new_y;
		ft_render_map(game);
	}
}
