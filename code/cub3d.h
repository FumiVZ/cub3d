/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 10:47:26 by vzuccare          #+#    #+#             */
/*   Updated: 2024/10/09 15:44:22 by vzuccare         ###   ########lyon.fr   */
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
# define HEIGHT 800
# define WIDTH 800

# define ROTATE_LEFT 65361
# define ROTATE_RIGHT 65363
# define FORWARD_W_Z 119
# define BACK_S_S 115
# define RIGHT_D_D 100
# define LEFT_A_Q 97
# define KEY_W 122
# define KEY_S 115
# define KEY_D 100
# define KEY_A 97
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

# define KEY_Q 113
# define KEY_ESC 65307

# ifndef M_PI
#  define M_PI 3.14159265359
# endif
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
# define NB_RAYS 30
# define STEP_SIZE 0.1
# define RAY_LENGTH 35
# define TEX_WIDTH 32
# define TEX_HEIGHT 32
# define ROTATE_SPEED 0.1
# define MOVE_SPEED 0.1

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

typedef struct s_map
{
	char		**map;
	size_t		map_x;
	size_t		map_y;
	t_player	*player;
}				t_map;

typedef struct s_ray
{
	int			x;
	double		ray_angle;
	double		perp_wall_dist;
	void		*image;
	char		*image_data;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
	int			line_height;
	int			draw_start;
	int			draw_end;
	int			texture_x;
}				t_ray;

typedef struct s_game
{
	t_map		*map;
	t_data		*data;
	t_ray		*ray;
	t_mlx		*mlx;
	int			fd;
}				t_game;

//	===== @functions =====
// error.c
void			exit_close_msg(int fd, char *msg, t_game *game);
void			ft_exit_error(char *str);
void			check_error(int ac, char **av);

// floor_cell.c
void			floor_cell(t_game *game);

// free.c
void			free_map(t_map *map);
void			free_data(t_data *data, t_game *game);
void			ft_free_all(t_game *game);
int				ft_close_game(t_game *game);

// game.c
void			ft_init_textures(t_game *game);
void			ft_render_texture(t_game *game, t_image texture, int line,
					int column);
int				ft_render_map(t_game *game);

// init.c
void			init_map(t_game *game, t_map *map);
void			init_game(t_game *game, char *name_file);

// key.c
int				key_press(int keycode, t_game *game);

// main.c
void			start_game(t_game *game);

// map.c
bool			check_adjacent(char **map, size_t i, size_t j, char c);
void			init_player(t_player **player, ssize_t x, ssize_t y, char c);
bool			check_zero(t_map *map, ssize_t i, ssize_t j);
t_map			*fill_with_space(t_map *map, t_game *game);
bool			check_map(t_map **map, t_game *game, int *fd);

// movement.c
void			ft_rotate_player(t_game *game, double direction);
void			ft_move_player(t_game *game, double move_speed);
void			ft_strafe_player(t_game *game, double strafe_speed);

// parse.c
void			print_int_tab(int *tab);
int				parse_textures(char *line, t_data *data, size_t i);
int				check_parse(t_data *data);
int				is_finished(t_data *data);
void			print_tab(char **tab);
void			parse_file(t_game *game);

// raycasting.c
void			draw_3d_projection(t_game *game);

// texture.c
char			*data_texture(char *line, char *search, size_t i);
bool			is_valid(char *str);
char			**erase_space(char **tab);
int				*assign_color(char **tab, int *color);
int				*parse_color(char *line, char *search, size_t i);

// vision.c
double			get_direction_x(double angle);
double			get_direction_y(double angle);
void			draw_vision(t_game *game);

#endif