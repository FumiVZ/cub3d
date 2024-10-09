/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 10:59:26 by vzuccare          #+#    #+#             */
/*   Updated: 2024/10/08 17:00:20 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	print_int_tab(int *tab)
{
	size_t	i;

	i = 0;
	while (tab[i] != -1)
	{
		printf("%d\n", tab[i]);
		i++;
	}
}

int	parse_textures(char *line, t_data *data, size_t i)
{
	if (!data->no && ft_strncmp(line + i, "NO", 2) == 0 && ft_strlen(line) > 2)
		data->no = data_texture(line, "NO", i);
	else if (!data->so && ft_strncmp(line + i, "SO", 2) == 0
		&& ft_strlen(line) > 2)
		data->so = data_texture(line, "SO", i);
	else if (!data->we && ft_strncmp(line + i, "WE", 2) == 0
		&& ft_strlen(line) > 2)
		data->we = data_texture(line, "WE", i);
	else if (!data->ea && ft_strncmp(line + i, "EA", 2) == 0
		&& ft_strlen(line) > 2)
		data->ea = data_texture(line, "EA", i);
	else if (!data->c && ft_strncmp(line + i, "C", 1) == 0
		&& ft_strlen(line) > 1)
		data->c = parse_color(line, "C", i);
	else if (!data->f && ft_strncmp(line + i, "F", 1) == 0
		&& ft_strlen(line) > 1)
		data->f = parse_color(line, "F", i);
	else if (ft_strncmp(line + i, "NO", 2) || ft_strncmp(line + i, "SO", 2)
		|| ft_strncmp(line + i, "WE", 2) || ft_strncmp(line + i, "EA", 2)
		|| ft_strncmp(line + i, "C", 1) || ft_strncmp(line + i, "F", 1))
		return (1);
	return (0);
}

int	check_parse(t_data *data)
{
	if (!data->no || !data->so || !data->we || !data->ea || !data->c
		|| !data->f)
		return (1);
	if (open(data->no, O_RDONLY) == -1)
		return (1);
	if (open(data->so, O_RDONLY) == -1)
		return (1);
	if (open(data->we, O_RDONLY) == -1)
		return (1);
	if (open(data->ea, O_RDONLY) == -1)
		return (1);
	return (0);
}

int	is_finished(t_data *data)
{
	if (data->no && data->so && data->we && data->ea && data->c && data->f)
		return (1);
	return (0);
}

void	print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		fprintf(stderr, "%s\n", tab[i]);
		i++;
	}
}

void	parse_file(t_game *game)
{
	size_t	i;
	char	*line;

	line = get_next_line(game->fd);
	if (!line)
		exit_close_msg(game->fd, ERR_MALLOC, game);
	while (line)
	{
		i = 0;
		while (line[i] && is_space(line[i]))
			i++;
		if (is_finished(game->data))
			break ;
		if (parse_textures(line, game->data, i))
		{
			free(line);
			exit_close_msg(game->fd, ERR_PARSE, game);
		}
		free(line);
		line = get_next_line(game->fd);
	}
	if (!check_map(&game->map, game, &game->fd))
	{
		free(line);
		exit_close_msg(game->fd, ERR_PARSE, game);
	}
	free(line);
}
