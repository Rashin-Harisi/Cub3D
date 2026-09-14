RED     = \033[31m
GREEN   = \033[32m
MAGENTA = \033[35m
CYAN    = \033[36m
RESET   = \033[0m


NAME		= cub3d
CC		= cc
CFLAGS	= -Wall -Wextra -Werror -g -std=gnu17

LIBFT_PATH	= ./libft
LIBFT		= $(LIBFT_PATH)/libft.a

MLX_PATH 	= ./minilibx-linux
MLX			= $(MLX_PATH)/libmlx.a
MLX_FLAGS 	= -L$(MLX_PATH) -lmlx -lXext -lX11 -lm -lz

INCLUDES 	= -I. -I$(LIBFT_PATH) -I$(MLX_PATH)

HEADER      = cub3d.h libft/libft.h minilibx-linux/mlx.h

MANDATORY_SRC	= main.c \
				print.c \
				get_next_line.c \
				utils_reading_extracting.c \
				./src/parsing/character_validation_map.c \
				./src/parsing/extract_map.c \
				./src/parsing/extract_rgb.c \
				./src/parsing/extract_textures_utils.c \
				./src/parsing/extract_textures.c \
				./src/parsing/map_validation.c \
 				./src/parsing/normalized_map.c \
				./src/parsing/playable_validation_map.c \
				./src/parsing/rgb_validation.c \
				./src/parsing/textures_validation.c \
				./src/parsing/utils.c \
				./src/parsing/validation.c \
				./src/parsing/wall_validation_map.c 
				
MANDATORY_OBJ	= $(MANDATORY_SRC:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(MANDATORY_OBJ)
	@printf "$(GREEN)Linking $(NAME)...$(RESET)\n"
	@$(CC) $(CFLAGS) $(MANDATORY_OBJ) $(LIBFT) $(MLX_FLAGS) -o $(NAME)
	@printf "$(GREEN)Mandatory part is built.$(RESET)\n"

$(LIBFT):
	@printf "$(CYAN)Building libft...$(RESET)\n"
	@$(MAKE) --no-print-directory -s -C $(LIBFT_PATH)

$(MLX):
	@printf "$(CYAN)Building MiniLibX...$(RESET)\n"
	@$(MAKE) --no-print-directory -s -C $(MLX_PATH)

%.o: %.c $(HEADER)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@printf "$(RED)Removing object files... $(RESET)\n"
	@rm -f $(MANDATORY_OBJ)
	@$(MAKE) clean --no-print-directory -s -C $(LIBFT_PATH)
	@$(MAKE) clean --no-print-directory -s -C $(MLX_PATH)

fclean: clean
	@printf "$(MAGENTA)Removing $(NAME) ... $(RESET)\n"
	@rm -f $(NAME)
	@$(MAKE) fclean --no-print-directory -s -C $(LIBFT_PATH)

re: fclean all

.PHONY: all bonus clean fclean re