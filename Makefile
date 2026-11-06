NAME		=	cub3D

CC			=	cc

CFLAGS		=	-Wall -Wextra -Werror -MMD -MP 

SRCS		=	

OBJS_DIR	=	obj/

OBJS		=	$(addprefix $(OBJS_DIR), $(SRCS:.c=.o))

DEPS		=	$(OBJS:.o=.d)

LIBFT_DIR	=	libft

LIBFT		=	$(LIBFT_DIR)/libft.a

MLX_DIR		= mlx

MLX			= $(MLX_DIR)/libmlx.a

INCLUDES	=	-I. -I$(LIBFT_DIR)

-include $(DEPS)

all:	$(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	$(MAKE) -C $(MLX_DIR)

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

