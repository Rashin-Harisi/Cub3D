RED     = \033[31m
GREEN   = \033[32m
MAGENTA = \033[35m
CYAN    = \033[36m
RESET   = \033[0m

NAME		= cub3d
HEADER      = cub3d.h libft/libft.h

MANDATORY_SRC	= main.c \
				print.c \
				get_next_line.c \
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

LIBFT_PATH	= ./libft
LIBFT		= libft.a

CC		= cc
CFLAGS	= -Wall -Wextra -Werror -g -I.

all: $(NAME)

$(NAME): $(LIBFT) $(MANDATORY_OBJ)
	@printf "$(GREEN)Linking $(NAME)...$(RESET)\n"
	@$(CC) $(CFLAGS) $(MANDATORY_OBJ) $(LIBFT) -lreadline -o $(NAME)
	@printf "$(GREEN)Mandatory part is built.$(RESET)\n"

$(LIBFT):
	@printf "$(CYAN)Building libft...$(RESET)\n"
	@$(MAKE) --no-print-directory -s -C $(LIBFT_PATH)
	@cp $(LIBFT_PATH)/libft.a .

%.o: %.c $(HEADER)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@printf "$(RED)Removing object files... $(RESET)\n"
	@rm -f $(MANDATORY_OBJ)
	@$(MAKE) clean --no-print-directory -s -C $(LIBFT_PATH)

fclean: clean
	@printf "$(MAGENTA)Removing $(NAME) and $(LIBFT)... $(RESET)\n"
	@rm -f $(NAME) libft.a libftprintf.a
	@$(MAKE) fclean --no-print-directory -s -C $(LIBFT_PATH)

re: fclean all

.PHONY: all bonus clean fclean re