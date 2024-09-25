/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 13:07:21 by vzuccare          #+#    #+#             */
/*   Updated: 2024/09/25 16:40:06 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	free_map(t_map *map)
{
	size_t	i;

	i = 0;
	if (!map)
		return ;
	if (!map->map)
		return ;
	if (map->map)
	{
		while (map->map[i])
		{
			if (map->map[i])
				free(map->map[i]);
			i++;
		}
		free(map->map);
	}
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
