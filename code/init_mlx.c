/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:43:59 by vzuccare          #+#    #+#             */
/*   Updated: 2024/09/26 15:18:49 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	init_mlx(t_window *window)
{
	window->size_x = WIDTH;
	window->size_y = HEIGHT;
	window->mlx_ptr = mlx_init();
	if (!window->mlx_ptr)
		ft_exit_error("Error\nmlx_init failed\n");
	window->win_ptr = mlx_new_window(window->mlx_ptr, window->size_x,
			window->size_y, "cub3d");
	if (!window->win_ptr)
		ft_exit_error("Error\nmlx_new_window failed\n");
}
