/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 10:47:26 by vzuccare          #+#    #+#             */
/*   Updated: 2024/09/28 23:45:48 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <errno.h>
# include <fcntl.h>
# include <libft.h>
# include <math.h>
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

# define ROTATE_LEFT 65361
# define ROTATE_RIGHT 65363
# define FORWARD_W_Z 119
# define BACK_S_S 115
# define RIGHT_D_D 100
# define LEFT_A_Q 97

# define KEY_Q 113
# define KEY_ESC 65307

# define PI 3.14159265359
# ifndef M_PI_2
#  define M_PI_2 1.57079632679
# endif
# ifndef M_PI_3
#  define M_PI_3 4.71238898038
# endif

# define TILE_SIZE 32
# define WALL_COLOR 0x00FF0000
# define FLOOR_COLOR 0x0000FF00
# define PLAYER_COLOR 0x000000FF

# define FOV 90
# define NB_RAYS 100
# define STEP_SIZE 0.1
# define RAY_LENGTH 35

typedef struct s_position
{
	double		x;
	double		y;
}				t_position;

typedef struct s_mlx
{
	void		*mlx_ptr;
	void		*win_ptr;
}				t_mlx;

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
	t_position	*pos;
	t_position	*dir;
}				t_player;

typedef struct s_ray
{
	t_player	*player;
	t_position	plane;
	t_position	raydir;
	double		camerax;
	int			mapx;
	int			mapy;
	t_position	sidedist;
	t_position	deltadist;
	int			stepx;
	int			stepy;
	int			hit;
	int			side;
	double		perpwalldist;
	int			lineheight;
	int			drawstart;
	int			drawend;
	int			x;
}				t_ray;

typedef struct s_map
{
	char		**map;
	size_t		map_x;
	size_t		map_y;
	t_player	*player;
}				t_map;

typedef struct s_game
{
	t_map		*map;
	t_ray		*ray;
	t_data		*data;
	t_mlx		*mlx;
}				t_game;

//	===== @functions =====
// error.c
void			exit_close_msg(int fd, char *msg, t_data *data, t_map *map);
void			ft_exit_error(char *str);
void			check_error(int ac, char **av);

// map.c
int				is_empty(char *line);
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

int				ft_close_game(t_game *game);
int				ft_render_map(t_game *game);
void			raycasting(t_game *game);
int				key_press(int keycode, t_game *game);
void			init_game(t_game *game);
void			ft_init_textures(t_game *game);
void			ft_render_texture(t_game *game, t_image texture, int line,
					int column);
void			draw_vision(t_game *game);

#endif