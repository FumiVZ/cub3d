/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 10:47:26 by vzuccare          #+#    #+#             */
/*   Updated: 2024/11/08 16:21:14 by vzuccare         ###   ########lyon.fr   */
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
# define MINIMAP_SCALE 0.5
# define KEY_Q 113
# define KEY_ESC 65307
# define PI 3.14159265359
# define TILE_SIZE 32
# define WALL_COLOR 0x00FF0000
# define FLOOR_COLOR 0x0000FF00
# define PLAYER_COLOR 0x000000FF

# define FOV 60.0
# define HALF_FOV 30.0
# define NB_RAYS 800
# define STEP_SIZE 0.1
# define RAY_LENGTH 35
# define ROTATE_SPEED 0.1
# define MOVE_SPEED 0.1

enum			e_texture
{
	NORTH,
	SOUTH,
	WEST,
	EAST
};

typedef struct s_position
{
	double		x;
	double		y;
}				t_position;

typedef struct s_texture
{
	void		*img;
	int			width;
	int			height;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
	char		*path;
}				t_texture;

typedef struct s_mlx
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
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
	bool		ea_bool;
	bool		we_bool;
	bool		no_bool;
	bool		so_bool;
	int			*f;
	int			*c;
	bool		f_bool;
	bool		c_bool;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
	int			width;
	int			height;
	void		*addr;
	t_image		wall;
	t_image		floor;
	t_image		player;
}				t_data;

typedef struct s_player
{
	t_position	*pos;
	t_position	*dir;
	double		angle;
	bool		up;
	bool		down;
	bool		left;
	bool		right;
	bool		rotate_left;
	bool		rotate_right;
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
	double		x;
	double		y;
	int			side;
	double		cos_angle;
	double		sin_angle;
	double		dist;
	int			wall_face;
	int			line_height;
	int			draw_start;
	int			draw_end;
	int			texture_color;
	int			tex_x;
	float		texture_offset;
}				t_ray;

typedef struct s_game
{
	t_map		*map;
	t_data		*data;
	t_ray		*ray;
	t_mlx		*mlx;
	t_texture	*wall_t[4];
	int			color;
	int			size;
	int			fd;
}				t_game;

//	===== @functions =====
// error.c
void			exit_close_msg(int fd, char *msg, t_game *game, char *line);
void			ft_exit_error(char *str);
void			check_error(int ac, char **av);

// fill_space.c
t_map			*fill_with_space(t_map *map, t_game *game);

// floor_cell.c
int				attribute_rgb(int *color);
void			floor_cell(t_game *game);

// free.c
void			free_wall(t_texture *wall, t_game *game);
void			free_map(t_map *map);
void			free_data(t_data *data, t_game *game);
void			ft_free_all(t_game *game);
int				ft_close_game(t_game *game);

// init.c
void			init_map(t_game *game, t_map *map);
void			init_game(t_game *game, char *name_file);

// key.c
int				key_press(int keycode, t_game *game);
int				key_release(int keycode, t_game *game);

// main.c
void			start_game(t_game *game);

// map.c
void			init_player_rot(t_player **player, char c);
bool			init_player(t_player **player, ssize_t x, ssize_t y,
					t_map *map);
bool			check_zero(t_map *map, ssize_t i, ssize_t j);
bool			check_map(t_map **map, t_game *game, int *fd);

// minimap.c
t_texture		*ft_new_texture(void *mlx, char *path, t_texture *tex,
					t_game *game);
void			draw_square(int x, int y, int color, t_game *game);
void			draw_mini_map(t_game *game);
int				ft_render_map(t_game *game);

// movement.c
bool			check_collision(t_game *game, float dir_x, float dir_y);
void			ft_up_and_down(t_game *game, double speed);
void			ft_strafe_player(t_game *game, double speed);
void			ft_move_player(t_game *game);

// parse.c
bool			is_valid_identifier(char *line, size_t i, char *id);
int				assign_texture(char *line, t_data *data, size_t i, char *id);
void			parse_file(t_game *game, char *line);

// parse_utils.c
int				parse_textures(char *line, t_data *data, size_t i);
bool			check_adjacent(char **map, size_t i, size_t j, char c);
int				check_parse(t_data *data);
int				is_finished(t_data *data);

// raycasting.c
bool			wall_touch(float player_x, float player_y, t_game *game);
void			init_ray(t_game *game, float start_x, float *prev_x,
					float *prev_y);
void			draw_line(t_game *game, float start_x, int i);

// ray_utils.c
int				get_texture_color(t_texture *tex, double texture_offset,
					int tex_x);
void			ft_init_textures(t_game *game);
void			put_pixel(t_game *game, int x, int y);
float			normalize_angle(float angle);

// texture.c
char			*data_texture(char *line, char *id, size_t i);
bool			is_valid(char *str);
char			**erase_space(char **tab);
int				*assign_color(char **tab, int *color);
int				*parse_color(char *line, char *search, size_t i);

#endif