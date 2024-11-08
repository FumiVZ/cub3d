/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 10:59:26 by vzuccare          #+#    #+#             */
/*   Updated: 2024/10/31 05:04:43 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

bool	is_valid_identifier(char *line, size_t i, char *id)
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
	if (ft_strncmp(id, "NO", 2) == 0 && data->no_bool)
		return (true);
	if (ft_strncmp(id, "SO", 2) == 0 && data->so_bool)
		return (true);
	if (ft_strncmp(id, "WE", 2) == 0 && data->we_bool)
		return (true);
	if (ft_strncmp(id, "EA", 3) == 0 && data->ea_bool)
		return (true);
	if (ft_strncmp(id, "F", 1) == 0 && data->f_bool)
		return (true);
	if (ft_strncmp(id, "C", 1) == 0 && data->c_bool)
		return (true);
	return (false);
}

static void	set_data_bool(t_data *data, char *id)
{
	if (ft_strncmp(id, "NO", 2) == 0)
		data->no_bool = true;
	else if (ft_strncmp(id, "SO", 2) == 0)
		data->so_bool = true;
	else if (ft_strncmp(id, "WE", 2) == 0)
		data->we_bool = true;
	else if (ft_strncmp(id, "EA", 2) == 0)
		data->ea_bool = true;
	else if (ft_strncmp(id, "C", 1) == 0)
		data->c_bool = true;
	else if (ft_strncmp(id, "F", 1) == 0)
		data->f_bool = true;
}

int	assign_texture(char *line, t_data *data, size_t i, char *id)
{
	char	*texture_path;

	texture_path = NULL;
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
	set_data_bool(data, id);
	texture_path = data_texture(line, id, i);
	if ((ft_strlen(id) == 2 && !texture_path))
		return (free(texture_path), 1);
	free(texture_path);
	return (0);
}

void	parse_file(t_game *game, char *line)
{
	size_t	i;

	line = get_next_line(game->fd);
	if (!line)
		exit_close_msg(game->fd, ERR_MALLOC, game, NULL);
	while (line)
	{
		i = 0;
		while (line[i] && is_space(line[i]))
			i++;
		if (parse_textures(line, game->data, i))
			exit_close_msg(game->fd, ERR_PARSE, game, line);
		if (is_finished(game->data))
			break ;
		free(line);
		line = get_next_line(game->fd);
	}
	while (line && line[0] == '\n')
	{
		free(line);
		line = get_next_line(game->fd);
	}
	if (!check_map(&game->map, game, &game->fd))
		exit_close_msg(game->fd, ERR_PARSE, game, line);
	free(line);
}
