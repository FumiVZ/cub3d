/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 10:59:26 by vzuccare          #+#    #+#             */
/*   Updated: 2024/09/26 13:42:28 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	parse_res(char *line, t_data *data, size_t i)
{
	return ;
	data->res_x = ft_atoi(line + i);
	while (line[i] && ft_isdigit(line[i]))
		i++;
	while (line[i] && is_space(line[i]))
		i++;
	data->res_y = ft_atoi(line + i);
}

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
	if (is_finished(data))
		return (0);
	if (!data->no && ft_strncmp(line + i, "NO", 2) && ft_strlen(line) > 2)
		data->no = data_texture(line, "NO", i);
	else if (!data->so && ft_strncmp(line + i, "SO", 2) && ft_strlen(line) > 2)
		data->so = data_texture(line, "SO", i);
	else if (!data->we && ft_strncmp(line + i, "WE", 2) && ft_strlen(line) > 2)
		data->we = data_texture(line, "WE", i);
	else if (!data->ea && ft_strncmp(line + i, "EA", 2) && ft_strlen(line) > 2)
		data->ea = data_texture(line, "EA", i);
	else if (!data->c && ft_strncmp(line + i, "C", 1) && ft_strlen(line) > 1)
		data->c = parse_color(line, "C", i);
	else if (!data->f && ft_strncmp(line + i, "F", 1) && ft_strlen(line) > 1)
		data->f = parse_color(line, "F", i);
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

void	parse_file(t_data *data, t_map *map, int fd)
{
	size_t	i;
	char	*line;

	line = get_next_line(fd);
	if (!line)
		exit_close_msg(fd, ERR_MALLOC, NULL, NULL);
	while (line)
	{
		i = 0;
		while (line[i] && is_space(line[i]))
			i++;
		if (is_finished(data))
			break ;
		parse_textures(line, data, i);
		free(line);
		line = get_next_line(fd);
	}
	if (!check_map(map, fd))
	{
		free(line);
		exit_close_msg(fd, ERR_PARSE, data, map);
	}
	free(line);
}
