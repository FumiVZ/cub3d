/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:48:10 by vzuccare          #+#    #+#             */
/*   Updated: 2024/09/26 15:51:21 by machrist         ###   ########.fr       */
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

static void	ft_init_textures(t_game *game)
{
	game->data->wall = ft_new_texture(game->window->mlx_ptr, WALL_XPM, game);
	game->data->floor = ft_new_texture(game->window->mlx_ptr, FLOOR_XPM, game);
	game->data->player = ft_new_texture(game->window->mlx_ptr, PLAYER_XPM,
			game);
}

static void	ft_render_texture(t_game *game, t_image texture, int line,
		int column)
{
	mlx_put_image_to_window(game->window->mlx_ptr, game->window->win_ptr,
		texture.xpm_ptr, texture.x * column, texture.y * line);
}

static void	ft_identify_texture(t_game *game, int y, int x)
{
	if (game->map->map[y][x] == '1')
		ft_render_texture(game, game->data->wall, y, x);
	else if (game->map->map[y][x] == '0')
		ft_render_texture(game, game->data->floor, y, x);
	else if (game->map->map[y][x] == 'N')
		ft_render_texture(game, game->data->player, y, x);
}

int	ft_render_map(t_game *game)
{
	size_t	x;
	size_t	y;

	ft_init_textures(game);
	y = 0;
	while (y < ft_strstrlen(game->map->map))
	{
		x = 0;
		while (x < ft_strlen(game->map->map[y]))
		{
			ft_identify_texture(game, y, x);
			x++;
		}
		y++;
	}
	return (0);
}
