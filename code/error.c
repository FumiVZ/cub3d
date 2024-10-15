/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 10:52:08 by vzuccare          #+#    #+#             */
/*   Updated: 2024/10/15 16:25:51 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	exit_close_msg(int fd, char *msg, t_game *game, char *line)
{
	if (line)
		free(line);
	ft_free_all(game);
	if (fd != -1)
		close(fd);
	ft_putstr_fd(msg, 2);
	exit(1);
}

void	ft_exit_error(char *str)
{
	ft_putstr_fd(str, 2);
	exit(1);
}

void	check_error(int ac, char **av)
{
	if (ac != 2)
	{
		ft_putstr_fd(ERR_ARG, 2);
		exit(1);
	}
	if (ft_strncmp(av[1] + ft_strlen(av[1]) - 4, ".cub", 4))
	{
		ft_putstr_fd(ERR_EXT, 2);
		exit(1);
	}
}
