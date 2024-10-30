/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 10:59:26 by vzuccare          #+#    #+#             */
/*   Updated: 2024/10/30 14:23:10 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static bool	is_valid_identifier(char *line, size_t i, char *id)
{
	size_t	len;

	len = ft_strlen(id);
	if (ft_strncmp(line + i, id, len) == 0)
	{
		if (line[i + len] && !is_space(line[i + len]))
			return (false);
		return (true);
	}
	return (false);
}

static bool	is_duplicate_texture(t_data *data, char *id)
{
	if (ft_strncmp(id, "NO", 2) == 0 && data->no)
		return (true);
	if (ft_strncmp(id, "SO", 2) == 0 && data->so)
		return (true);
	if (ft_strncmp(id, "WE", 2) == 0 && data->we)
		return (true);
	if (ft_strncmp(id, "EA", 2) == 0 && data->ea)
		return (true);
	if (ft_strncmp(id, "F", 1) == 0 && data->f)
		return (true);
	if (ft_strncmp(id, "C", 1) == 0 && data->c)
		return (true);
	return (false);
}

static int	assign_texture(char *line, t_data *data, size_t i, char *id)
{
	char	*texture_path;

	if (is_duplicate_texture(data, id))
		return (1);
	if (ft_strncmp(id, "NO", 2) == 0)
		data->no = data_texture(line, id, i);
	else if (ft_strncmp(id, "SO", 2) == 0)
		data->so = data_texture(line, id, i);
	else if (ft_strncmp(id, "WE", 2) == 0)
		data->we = data_texture(line, id, i);
	else if (ft_strncmp(id, "EA", 2) == 0)
		data->ea = data_texture(line, id, i);
	else if (ft_strncmp(id, "F", 1) == 0)
		data->f = parse_color(line, id, i);
	else if (ft_strncmp(id, "C", 1) == 0)
		data->c = parse_color(line, id, i);
	texture_path = data_texture(line, id, i);
	if ((ft_strncmp(id, "F", 1) == 0 && !data->f) || (ft_strncmp(id, "C",
				1) == 0 && !data->c) || (ft_strlen(id) == 2 && !texture_path))
	{
		if (texture_path)
			free(texture_path);
		return (1);
	}
	return (free(texture_path), 0);
}

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

void	parse_file(t_game *game)
{
	size_t	i;
	char	*line;

	line = get_next_line(game->fd);
	if (!line)
		exit_close_msg(game->fd, ERR_MALLOC, game, NULL);
	while (line)
	{
		i = 0;
		while (line[i] && is_space(line[i]))
			i++;
		if (is_finished(game->data))
			break ;
		if (parse_textures(line, game->data, i))
			exit_close_msg(game->fd, ERR_PARSE, game, line);
		free(line);
		line = get_next_line(game->fd);
	}
	if (!check_map(&game->map, game, &game->fd))
		exit_close_msg(game->fd, ERR_PARSE, game, line);
	free(line);
}
