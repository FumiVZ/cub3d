/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:48:10 by vzuccare          #+#    #+#             */
/*   Updated: 2024/10/09 17:28:09 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static t_image	ft_new_texture(void *mlx, char *path, t_game *game)
{
	t_image	texture;

	texture.xpm_ptr = mlx_xpm_file_to_image(mlx, path, &texture.x, &texture.y);
	if (!texture.xpm_ptr)
	{
		ft_printf_fd(2, "Error: Failed to load %s\n", path);
		ft_close_game(game);
	}
	return (texture);
}

void	ft_init_textures(t_game *game)
{
	game->data->wall = ft_new_texture(game->mlx->mlx_ptr, WALL_XPM, game);
	game->data->floor = ft_new_texture(game->mlx->mlx_ptr, FLOOR_XPM, game);
	game->data->player = ft_new_texture(game->mlx->mlx_ptr, PLAYER_XPM, game);
}

void	ft_render_texture(t_game *game, t_image texture, int line, int column)
{
	mlx_put_image_to_window(game->mlx->mlx_ptr, game->mlx->win_ptr,
		texture.xpm_ptr, texture.x * column, texture.y * line);
}

static void	ft_identify_texture(t_game *game, int y, int x)
{
	if (game->map->map[y][x] == '1')
		ft_render_texture(game, game->data->wall, y, x);
	else if (game->map->map[y][x] == '0')
		ft_render_texture(game, game->data->floor, y, x);
}

int	ft_render_map(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (game->map->map[y])
	{
		x = 0;
		while (game->map->map[y][x])
		{
			ft_identify_texture(game, y, x);
			x++;
		}
		y++;
	}
	ft_render_texture(game, game->data->player, game->map->player->pos->y,
		game->map->player->pos->x);
	draw_vision(game);
	return (0);
}
