/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aganz <aganz@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/01 19:58:01 by aganz             #+#    #+#             */
/*   Updated: 2026/11/01 20:17:45 by aganz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../minilibx/mlx.h"
# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

//define windows
# define WIN_WIDTH 960
# define WIN_HEIGHT 720

//define keys
# define KEY_UP		65362
# define KEY_LEFT	65361
# define KEY_RIGHT	65363
# define KEY_DOWN	65364
# define KEY_ESC	65307

//define speed
# define MOVESPEED 0.0125
# define ROTSPEED 0.015

typedef struct s_img
{

}	t_img;

typedef struct s_minimap
{

}	t_minimap;

typedef struct s_map
{

}	t_map;

typedef struct s_player
{

}	t_player;

typedef struct s_ray
{

}	t_ray;

typedef struct s_game
{
	void	*mlx;
	void	*win;
}	t_game;

#endif