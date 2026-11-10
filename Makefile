NAME		=	cub3D

CC			=	cc

CFLAGS		=	-Wall -Wextra -Werror -MMD -MP 

SRCS		=	src/main.c src/free.c src/init.c src/utils.c \
				src/parsing/parse_file.c src/parsing/path_validation.c \
				src/parsing/map/map_utils.c src/parsing/map/map_validation.c \
				src/parsing/map/parse_map.c src/parsing/identifiers/colors.c  \
				src/parsing/identifiers/identifiers_utils.c \
				src/parsing/identifiers/parse_identifier.c

OBJS_DIR	=	obj/

OBJS		=	$(addprefix $(OBJS_DIR), $(SRCS:.c=.o))

DEPS		=	$(OBJS:.o=.d)

LIBFT_DIR	=	libft/

LIBFT		=	$(LIBFT_DIR)libft.a

MLX_DIR		= mlx

MLX			= $(MLX_DIR)/libmlx.a

INCLUDES	=	-I. -I$(LIBFT_DIR)

all:	$(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	$(MAKE) -C $(MLX_DIR) CC="cc -std=gnu17"

$(OBJS_DIR)%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean
	rm -rf $(OBJS_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

-include $(DEPS)
