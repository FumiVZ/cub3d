NAME = cub3d
CFLAGS = -Wall -Wextra -Werror -g
CC = cc
BUILD_DIR = build
SRCS_DIR = code/

SRC =    $(addprefix $(SRCS_DIR), error.c free.c main.c map.c parse.c texture.c utils.c init_mlx.c game.c)

LIBFT = libft.a
LIBMLX = libmlx.a

LIB_PATH = libft
MLX_PATH = minilibx-linux
LIB_DIR = -Ilibft -Iminilibx-linux -Icode

OBJECTS = $(SRC:%.c=$(BUILD_DIR)/%.o)

all: $(NAME)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)
	mkdir -p $(BUILD_DIR)/code

$(NAME): $(BUILD_DIR) $(LIBFT) $(LIBMLX) $(OBJECTS) code/cub3d.h 
	$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME) libft/libft.a $(MLX_PATH)/$(LIBMLX) -Lmlx -L/usr/lib/X11 -lXext -lX11

$(BUILD_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(LIB_DIR)

$(LIBFT):	
	$(MAKE) -C $(LIB_PATH)

$(LIBMLX):
	$(MAKE) -C $(MLX_PATH)

clean:
	rm -rf $(BUILD_DIR)
	$(MAKE) -C $(LIB_PATH) clean
	$(MAKE) -C $(MLX_PATH) clean

fclean: clean
	rm -rf $(NAME)
	$(MAKE) -C $(LIB_PATH) fclean

re: fclean all

.PHONY: all clean fclean re