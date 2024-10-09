/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_cell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:41:50 by vzuccare          #+#    #+#             */
/*   Updated: 2024/10/09 15:44:53 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	attribute_rgb(int *color)
{
	int	rgb;

	rgb = 0;
	rgb += color[0] << 16;
	rgb += color[1] << 8;
	rgb += color[2];
	return (rgb);
}

void	floor_cell(t_game *game)
{
	int x;
	int y;
	int pixel_index; 	
	int color;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			pixel_index = (y * game->ray->size_line) + (x
					* (game->ray->bits_per_pixel / 8));
			if (y < HEIGHT / 2)
				color = attribute_rgb(game->data->c);
			else
				color = attribute_rgb(game->data->f);
			game->ray->image_data[pixel_index] = color & 0xFF;
			game->ray->image_data[pixel_index + 1] = (color >> 8) & 0xFF;
			game->ray->image_data[pixel_index + 2] = (color >> 16) & 0xFF;
		}
	}
}
