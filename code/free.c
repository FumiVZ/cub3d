/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 13:07:21 by vzuccare          #+#    #+#             */
/*   Updated: 2024/09/26 15:25:12 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	ft_destroy_image(t_game *game)
{
	mlx_destroy_image(game->window->mlx_ptr, game->data->wall.xpm_ptr);
	mlx_destroy_image(game->window->mlx_ptr, game->data->floor.xpm_ptr);
	mlx_destroy_image(game->window->mlx_ptr, game->data->player.xpm_ptr);
}

void	free_map(t_map *map)
{
	if (map->map)
		free_split(map->map, ft_strstrlen(map->map));
}

void	free_data(t_data *data)
{
	if (data->no)
		free(data->no);
	if (data->so)
		free(data->so);
	if (data->we)
		free(data->we);
	if (data->ea)
		free(data->ea);
	if (data->c)
		free(data->c);
	if (data->f)
		free(data->f);
}

void	ft_free_all(t_game *game)
{
	ft_destroy_image(game);
	free_map(game->map);
	free_data(game->data);
	mlx_destroy_window(game->window->mlx_ptr, game->window->win_ptr);
	mlx_destroy_display(game->window->mlx_ptr);
	free(game->window->mlx_ptr);
}

int	ft_close_game(t_game *game)
{
	ft_free_all(game);
	exit(0);
}