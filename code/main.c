/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 10:35:08 by vzuccare          #+#    #+#             */
/*   Updated: 2024/09/29 16:37:42 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	start_game(t_game *game)
{
	print_tab(game->map->map);
	mlx_hook(game->mlx->win_ptr, KeyPress, KeyPressMask, key_press, game);
	mlx_hook(game->mlx->win_ptr, Expose, ButtonPressMask, ft_render_map, game);
	mlx_hook(game->mlx->win_ptr, DestroyNotify, ButtonPressMask, ft_close_game,
		game);
	mlx_loop(game->mlx->mlx_ptr);
}

int	main(int ac, char **av)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		ft_exit_error(ERR_MALLOC);
	check_error(ac, av);
	game->map = NULL;
	game->ray = NULL;
	game->data = NULL;
	game->mlx = NULL;
	init_game(game, av[1]);
	start_game(game);
	return (0);
}
