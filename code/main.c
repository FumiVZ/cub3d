/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 10:35:08 by vzuccare          #+#    #+#             */
/*   Updated: 2024/09/25 22:08:54 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	test(void)
{
	return (0);
}

void	init_game(t_game *game, char *name_file)
{
	t_data		data;
	t_map		map;
	t_window	window;
	int			fd;

	data = (t_data){0};
	map = (t_map){0};
	init_mlx(&window);
	fd = open(name_file, O_RDONLY);
	if (fd == -1)
		ft_exit_error(ERR_OPEN);
	parse_file(&data, &map, fd);
	if (check_parse(&data))
		exit_close_msg(fd, ERR_PARSE, &data);
	game->data = &data;
	game->map = &map;
	game->window = &window;
	print_tab(map.map);
	print_tab(game->map->map);
	mlx_hook(game->window->win_ptr, DestroyNotify, ButtonPressMask,
		ft_close_game, game);
	mlx_loop(game->window->mlx_ptr);
}

int	main(int ac, char **av)
{
	t_game	game;

	check_error(ac, av);
	init_game(&game, av[1]);
	return (0);
}
