/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:21:03 by vzuccare          #+#    #+#             */
/*   Updated: 2024/10/30 23:11:07 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	parse_textures(char *line, t_data *data, size_t i)
{
	const char	*identifiers[] = {"NO", "SO", "WE", "EA", "F", "C"};
	int			j;

	j = 0;
	while (j < 6)
	{
		if (is_valid_identifier(line, i, (char *)identifiers[j]))
			return (assign_texture(line, data, i, (char *)identifiers[j]));
		j++;
	}
	while (line[i] && is_space(line[i]))
		i++;
	if (line[i] && !is_space(line[i]))
		return (1);
	return (0);
}

bool	check_adjacent(char **map, size_t i, size_t j, char c)
{
	if ((j > 0 && map[j - 1][i] == c) || (!map[j + 1] && map[j + 1][i] == c)
		|| (i > 0 && map[j][i - 1] == c) || (!map[j][i + 1] && map[j][i
			+ 1] == c) || (map[j - 1][i - 1] && map[j - 1][i - 1] == c)
		|| (map[j + 1][i + 1] && map[j + 1][i + 1] == c) || (map[j - 1][i + 1]
			&& map[j - 1][i + 1] == c) || (map[j + 1][i - 1] && map[j + 1][i
			- 1] == c))
		return (true);
	return (false);
}

int	check_parse(t_data *data)
{
	const char	*files[] = {data->no, data->so, data->we, data->ea};
	int			fd;
	int			i;

	i = 0;
	if (!data->no || !data->so || !data->we || !data->ea || !data->c
		|| !data->f)
		return (1);
	while (i < 4)
	{
		fd = open(files[i], O_RDONLY);
		if (fd == -1)
		{
			fprintf(stderr, "file %s not found\n", files[i]);
			return (1);
		}
		close(fd);
		i++;
	}
	return (0);
}

int	is_finished(t_data *data)
{
	if (data->no && data->so && data->we && data->ea && data->c && data->f)
		return (1);
	return (0);
}
