# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aganz <aganz@student.42lausanne.ch>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/11/16 22:24:18 by aganz             #+#    #+#              #
#    Updated: 2026/11/27 14:21:52 by aganz            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	cub3D

CC		=	cc

CFLAGS	=	-Wall -Wextra -Werror -std=gnu17 -MMD -MP

SRCS	=	src/main.c \
			src/init/init.c src/init/mlx_init.c src/init/texture_init.c \
			src/parsing/parse_file.c src/parsing/path_validation.c \
			src/parsing/map/map_utils.c src/parsing/map/map_validation.c \
			src/parsing/map/parse_map.c src/parsing/identifiers/colors.c  \
			src/parsing/identifiers/identifiers_utils.c \
			src/parsing/identifiers/parse_identifier.c \
			src/game/game_loop.c src/game/events.c src/game/player.c \
			src/render/draw.c src/render/minimap.c src/render/raycast.c  src/render/render.c \
			src/exit/cleanup.c src/exit/free.c src/exit/game_exit.c \
			src/utils/utils.c src/utils/vector.c src/utils/time.c src/utils/raycast_utils.c 

OBJS_DIR	=	obj/

OBJS	=	$(addprefix $(OBJS_DIR), $(SRCS:.c=.o))

DEPS	=	$(OBJS:.o=.d)

LIBFT_DIR	=	libft/

LIBFT	=	$(LIBFT_DIR)libft.a

MLX_DIR	=	mlx/

MLX		=	$(MLX_DIR)/libmlx.a

INCLUDES	=	-I.

all: $(NAME)

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
	rm -rf $(NAME)

re: fclean all

bonus: $(NAME)

.PHONY: all clean fclean re bonus

-include $(DEPS)