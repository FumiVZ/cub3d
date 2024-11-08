/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 13:07:21 by vzuccare          #+#    #+#             */
/*   Updated: 2024/11/08 16:19:28 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	free_wall(t_texture *wall, t_game *game)
{
	if (wall)
	{
		mlx_destroy_image(game->mlx->mlx_ptr, wall->img);
		free(wall);
	}
}

void	free_map(t_map *map)
{
	if (map)
	{
		if (map->map)
			free_split(map->map, ft_strstrlen(map->map));
		if (map->player)
		{
			if (map->player->pos)
				free(map->player->pos);
			if (map->player->dir)
				free(map->player->dir);
			free(map->player);
		}
		free(map);
	}
}

void	free_data(t_data *data, t_game *game)
{
	if (data)
	{
		if (game->data->wall.xpm_ptr)
			mlx_destroy_image(game->mlx->mlx_ptr, game->data->wall.xpm_ptr);
		if (game->data->floor.xpm_ptr)
			mlx_destroy_image(game->mlx->mlx_ptr, game->data->floor.xpm_ptr);
		if (game->data->player.xpm_ptr)
			mlx_destroy_image(game->mlx->mlx_ptr, game->data->player.xpm_ptr);
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
		free(data);
	}
}

void	ft_free_all(t_game *game)
{
	int	i;

	i = 0;
	free_map(game->map);
	free_data(game->data, game);
	if (game->ray)
		free(game->ray);
	while (i < 4)
		free_wall(game->wall_t[i++], game);
	if (game->mlx)
	{
		mlx_destroy_window(game->mlx->mlx_ptr, game->mlx->win_ptr);
		mlx_destroy_image(game->mlx->mlx_ptr, game->mlx->img_ptr);
		mlx_destroy_display(game->mlx->mlx_ptr);
		free(game->mlx->mlx_ptr);
		free(game->mlx);
	}
	free(game);
}

int	ft_close_game(t_game *game)
{
	ft_free_all(game);
	exit(0);
}
