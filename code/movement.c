/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 17:27:18 by machrist          #+#    #+#             */
/*   Updated: 2024/10/28 18:25:42 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

bool	check_collision(t_game *game, float dir_x, float dir_y)
{
	t_player	*player;
	float		new_y;
	size_t		map_y;
	float		new_x;
	size_t		map_x;

	player = game->map->player;
	new_x = player->pos->x + dir_x * 0.3;
	new_y = player->pos->y + dir_y * 0.3;
	map_x = (int)(new_x / 32);
	map_y = (int)(new_y / 32);
	if (map_x >= 0 && map_x < game->map->map_x && map_y >= 0
		&& map_y < game->map->map_y)
	{
		if (game->map->map[map_y][map_x] != '1')
			return (true);
	}
	return (false);
}

void	ft_up_and_down(t_game *game, double speed)
{
	float	cos_angle;
	float	sin_angle;

	cos_angle = cos(game->map->player->angle);
	sin_angle = sin(game->map->player->angle);
	if (game->map->player->up && check_collision(game, cos_angle, sin_angle))
	{
		game->map->player->pos->x += cos_angle * speed;
		game->map->player->pos->y += sin_angle * speed;
	}
	if (game->map->player->down && check_collision(game, -cos_angle,
			-sin_angle))
	{
		game->map->player->pos->x -= cos_angle * speed;
		game->map->player->pos->y -= sin_angle * speed;
	}
}

void	ft_strafe_player(t_game *game, double speed)
{
	float	strafe_cos;
	float	strafe_sin;

	strafe_cos = cos(game->map->player->angle + (PI / 2));
	strafe_sin = sin(game->map->player->angle + (PI / 2));
	if (game->map->player->right && check_collision(game, strafe_cos,
			strafe_sin))
	{
		game->map->player->pos->x += strafe_cos * speed;
		game->map->player->pos->y += strafe_sin * speed;
	}
	if (game->map->player->left && check_collision(game, -strafe_cos,
			-strafe_sin))
	{
		game->map->player->pos->x -= strafe_cos * speed;
		game->map->player->pos->y -= strafe_sin * speed;
	}
}

void	ft_move_player(t_game *game)
{
	t_player	*player;
	double		speed;
	float		rot_speed;

	speed = 1;
	rot_speed = 0.05;
	player = game->map->player;
	if (player->rotate_left)
		player->angle -= rot_speed;
	if (player->rotate_right)
		player->angle += rot_speed;
	if (player->angle >= 2 * PI)
		player->angle -= 2 * PI;
	else if (player->angle < 0)
		player->angle += 2 * PI;
	if (player->up)
		ft_up_and_down(game, speed);
	else if (player->down)
		ft_up_and_down(game, speed);
	else if (player->right)
		ft_strafe_player(game, speed);
	else if (player->left)
		ft_strafe_player(game, speed);
}
