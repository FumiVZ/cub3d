/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincent <vincent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 10:47:26 by vzuccare          #+#    #+#             */
/*   Updated: 2024/09/28 15:58:23 by vincent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <errno.h>
# include <fcntl.h>
# include <libft.h>
# include <mlx.h>
# include <mlx_int.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>

# define ERR_ARG "Error: Wrong number of arguments\n"
# define ERR_EXT "Error: Wrong file extension\n"
# define ERR_MALLOC "Error: Malloc failed\n"
# define ERR_OPEN "Error: Open failed\n"
# define ERR_PARSE "Error: Parse failed\n"
# define ERR_READ "Error: Read failed\n"
# define ERR_MLX "Error: Mlx failed\n"

# define WALL_XPM "textures/wall.xpm"
# define FLOOR_XPM "textures/floor.xpm"
# define PLAYER_XPM "textures/player.xpm"
# define HEIGHT 1080
# define WIDTH 1080

typedef struct s_position
{
	double		x;
	double		y;
}				t_position;

typedef struct s_window
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			size_x;
	int			size_y;
}				t_window;

typedef struct s_image
{
	void		*xpm_ptr;
	int			x;
	int			y;
}				t_image;

typedef struct s_data
{
	int			res_x;
	int			res_y;
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	int			*f;
	int			*c;
	t_image		wall;
	t_image		floor;
	t_image		player;
}				t_data;

typedef struct s_player
{
	t_position	pos;
	float		dir;
}				t_player;

typedef struct s_map
{
	char		**map;
	size_t		map_x;
	size_t		map_y;
	t_player	player;
}				t_map;

typedef struct s_game
{
	t_map		*map;
	t_data		*data;
	t_window	*window;
}				t_game;

//	===== @functions =====
// error.c
void exit_close_msg(int fd, char *msg, t_data *data, t_map *map);
void ft_exit_error(char *str);
void check_error(int ac, char **av);

// free.c
void			free_map(t_map *map);
void			free_data(t_data *data);

// main.c
int				test(void);

// map.c
int				is_empty(char *line);
t_map			*ft_remap(t_map *map, char *line);
bool			check_zero(t_map *map);
bool			is_space_or_one(char c);
bool			is_correct_map(t_map *map);
bool			check_map(t_map *map, int fd);

// parse.c
void			parse_res(char *line, t_data *data, size_t i);
void			print_int_tab(int *tab);
int				parse_textures(char *line, t_data *data, size_t i);
int				check_parse(t_data *data);
int				is_finished(t_data *data);
void			print_tab(char **tab);
void			parse_file(t_data *data, t_map *map, int fd);

// texture.c
char			*data_texture(char *line, char *search, size_t i);
bool			is_valid(char *str);
char			**erase_space(char **tab);
int				*assign_color(char **tab, int *color);
int				*parse_color(char *line, char *search, size_t i);

// utils.c
bool			zero_check(char c);
bool			is_player(char c);

void			init_mlx(t_window *window);
int				ft_close_game(t_game *game);
int				ft_render_map(t_game *game);

#endif