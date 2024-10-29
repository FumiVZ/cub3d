NAME = cub3d
CFLAGS = -Wall -Wextra -Werror -g
CC = cc
BUILD_DIR = build
SRCS_DIR = code/
HEADERS = $(addprefix $(SRCS_DIR), cub3d.h)

SRC = $(addprefix $(SRCS_DIR), free.c init.c main.c  parse.c texture.c error.c  minimap.c  key.c map.c raycasting.c vision.c movement.c floor_cell.c fill_space.c ray_utils.c)

LIBFT = libft.a
LIBMLX = libmlx.a

LIB_PATH = libft
MLX_PATH = minilibx-linux
LIB_DIR = -Ilibft -Iminilibx-linux -Icode

OBJECTS = $(SRC:$(SRCS_DIR)%.c=$(BUILD_DIR)/%.o)

all: $(LIBFT) $(LIBMLX) $(NAME)

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BUILD_DIR)/code

$(NAME): $(BUILD_DIR) $(OBJECTS) $(HEADERS) 
	@$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME) $(LIB_PATH)/$(LIBFT) $(MLX_PATH)/$(LIBMLX) -Lmlx -L/usr/lib/X11 -lXext -lX11 -lm
	@echo "Build complete: $(NAME)"

$(BUILD_DIR)/%.o: $(SRCS_DIR)%.c $(HEADERS)
	@$(CC) $(CFLAGS) -c $< -o $@ $(LIB_DIR)
	@echo "Compiled: $<"

$(LIBFT):	
	@$(MAKE) -C $(LIB_PATH) -s

$(LIBMLX):
	@$(MAKE) -C $(MLX_PATH) -s

clean:
	@rm -rf $(BUILD_DIR)
	@$(MAKE) -C $(LIB_PATH) clean -s
	@$(MAKE) -C $(MLX_PATH) clean -s
	@echo "Clean complete"

fclean: clean
	@rm -rf $(NAME)
	@$(MAKE) -C $(LIB_PATH) fclean -s
	@echo "Full clean complete"

re: fclean all

.PHONY: all clean fclean re