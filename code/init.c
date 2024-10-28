/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:43:59 by vzuccare          #+#    #+#             */
/*   Updated: 2024/10/28 18:41:40 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	init_wall_textures(t_texture *tex, t_game *game, int i)
{
	if (i == 0)
		tex->path = game->data->no;
	else if (i == 1)
		tex->path = game->data->so;
	else if (i == 2)
		tex->path = game->data->we;
	else if (i == 3)
		tex->path = game->data->ea;
	tex->addr = NULL;
	tex->img = NULL;
	tex->width = 0;
	tex->height = 0;
	tex->bpp = 0;
	tex->line_len = 0;
	tex->endian = 0;
	
	// Charger d'abord l'image XPM
	tex->img = mlx_xpm_file_to_image(game->mlx->mlx_ptr, tex->path, 
		&tex->width, &tex->height);
	if (!tex->img)
		exit_close_msg(game->fd, ERR_MLX, game, NULL);
		
	// Puis obtenir son adresse
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp, &tex->line_len,
			&tex->endian);
	if (!tex->addr)
		exit_close_msg(game->fd, ERR_MLX, game, NULL);
}

static void	init_data(t_game *game)
{
	game->data->wall.xpm_ptr = NULL;
	game->data->floor.xpm_ptr = NULL;
	game->data->player.xpm_ptr = NULL;
	game->data->no = NULL;
	game->data->so = NULL;
	game->data->we = NULL;
	game->data->ea = NULL;
	game->data->c = NULL;
	game->data->f = NULL;
}

void	init_map(t_game *game, t_map *map)
{
	map->map = NULL;
	map->map_x = 0;
	map->map_y = 0;
	map->player = malloc(sizeof(t_player));
	if (!map->player)
		exit_close_msg(game->fd, ERR_MALLOC, game, NULL);
	map->player->pos = malloc(sizeof(t_position));
	if (!map->player->pos)
		exit_close_msg(game->fd, ERR_MALLOC, game, NULL);
	map->player->dir = malloc(sizeof(t_position));
	if (!map->player->dir)
		exit_close_msg(game->fd, ERR_MALLOC, game, NULL);
	map->player->pos->x = -1;
	map->player->pos->y = -1;
	map->player->dir->x = 0;
	map->player->dir->y = 0;
}

static void	init_mlx(t_mlx *mlx)
{
	mlx->mlx_ptr = mlx_init();
	if (!mlx->mlx_ptr)
		exit_close_msg(0, ERR_MLX, NULL, NULL);
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, WIDTH, HEIGHT, "Cub3D");
	if (!mlx->win_ptr)
		exit_close_msg(0, ERR_MLX, NULL, NULL);
	mlx->img_ptr = mlx_new_image(mlx->mlx_ptr, WIDTH, HEIGHT);
	if (!mlx->img_ptr)
	{
		fprintf(stderr, "Error: Failed to create image\n");
		mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
		exit_close_msg(0, ERR_MLX, NULL, NULL);
	}
	mlx->addr = mlx_get_data_addr(mlx->img_ptr, &mlx->bits_per_pixel,
			&mlx->line_length, &mlx->endian);
	if (!mlx->addr)
	{
		fprintf(stderr, "Error: Failed to get image address\n");
		exit_close_msg(0, ERR_MLX, NULL, NULL);
	}
}

static void	init_wall_textures_array(t_game *game)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		game->wall_t[i] = malloc(sizeof(t_texture));
		if (!game->wall_t[i])
			exit_close_msg(game->fd, ERR_MALLOC, game, NULL);
		init_wall_textures(game->wall_t[i], game, i);
	}
}

static void	init_mlx_components(t_game *game)
{
	game->mlx = malloc(sizeof(t_mlx));
	if (!game->mlx)
		exit_close_msg(game->fd, ERR_MALLOC, game, NULL);
	init_mlx(game->mlx);
}

void	init_game(t_game *game, char *name_file)
{
	game->fd = open(name_file, O_RDONLY);
	if (game->fd == -1)
	{
		free(game);
		ft_exit_error(ERR_OPEN);
	}
	game->data = malloc(sizeof(t_data));
	if (!game->data)
		exit_close_msg(game->fd, ERR_MALLOC, game, NULL);
	init_data(game);
	game->map = malloc(sizeof(t_map));
	if (!game->map)
		exit_close_msg(game->fd, ERR_MALLOC, game, NULL);
	init_map(game, game->map);
	parse_file(game);
	if (check_parse(game->data))
		exit_close_msg(game->fd, ERR_PARSE, game, NULL);
	init_mlx_components(game);
	init_wall_textures_array(game);
	game->ray = malloc(sizeof(t_ray));
	if (!game->ray)
		exit_close_msg(game->fd, ERR_MALLOC, game, NULL);
	ft_init_textures(game);
}
