/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:43:59 by vzuccare          #+#    #+#             */
/*   Updated: 2024/09/25 16:17:16 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	init_mlx(t_window *window)
{
	window->size_x = 640;
	window->size_y = 480;
	window->mlx_ptr = mlx_init();
	if (!window->mlx_ptr)
		ft_exit_error("Error\nmlx_init failed\n");
	window->win_ptr = mlx_new_window(window->mlx_ptr, window->size_x, window->size_y, "cub3d");
	if (!window->win_ptr)
		ft_exit_error("Error\nmlx_new_window failed\n");
}
