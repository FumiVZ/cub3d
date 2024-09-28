/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 10:35:08 by vzuccare          #+#    #+#             */
/*   Updated: 2024/09/28 22:04:38 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	start_game(t_game *game, char *name_file)
{
	int			fd;

	fd = open(name_file, O_RDONLY);
	if (fd == -1)
		ft_exit_error(ERR_OPEN);
	parse_file(game->data, game->map, fd);
	if (check_parse(game->data))
		exit_close_msg(fd, ERR_PARSE, game->data, game->map);
	print_tab(game->map->map);
	mlx_hook(game->mlx->win_ptr, KeyPress, KeyPressMask,
		key_press, game);
	mlx_hook(game->mlx->win_ptr, Expose, ButtonPressMask,
		ft_render_map, game);
	mlx_hook(game->mlx->win_ptr, DestroyNotify, ButtonPressMask,
		ft_close_game, game);
	mlx_loop(game->mlx->mlx_ptr);
}

int	main(int ac, char **av)
{
	t_game	*game;


	game = malloc(sizeof(t_game));
	if (!game)
		ft_exit_error(ERR_MALLOC);
	check_error(ac, av);
	init_game(game);
	start_game(game, av[1]);
	return (0);
}
