/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 10:35:08 by vzuccare          #+#    #+#             */
/*   Updated: 2024/10/26 15:09:04 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	start_game(t_game *game)
{
	print_tab(game->map->map);
	mlx_hook(game->mlx->win_ptr, 2, 1L << 0, key_press, game);
	mlx_hook(game->mlx->win_ptr, 3, 1L << 1, key_release, game);
	mlx_hook(game->mlx->win_ptr, DestroyNotify, ButtonPressMask, ft_close_game,
		game);
	mlx_loop_hook(game->mlx->mlx_ptr, ft_render_map, game);
	mlx_loop(game->mlx->mlx_ptr);
}

int	main(int ac, char **av)
{
	t_game	*game;

	check_error(ac, av);
	game = malloc(sizeof(t_game));
	if (!game)
		ft_exit_error(ERR_MALLOC);
	game->map = NULL;
	game->ray = NULL;
	game->data = NULL;
	game->mlx = NULL;
	game->wall_t[0] = NULL;
	game->wall_t[1] = NULL;
	game->wall_t[2] = NULL;
	game->wall_t[3] = NULL;
	init_game(game, av[1]);
	start_game(game);
	return (0);
}
