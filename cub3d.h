/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jefferson <jefferson@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/01 19:58:01 by aganz             #+#    #+#             */
/*   Updated: 2026/11/06 11:55:06 by jefferson        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx/mlx.h"
# include "libft/libft.h"
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
# define PLANE 0.66
# define COLOR_UNSET -1

typedef enum e_textures
{
	NORTH,
	SOUTH,
	WEST,
	EAST,
	TEX_COUNT
}			t_textures;

typedef struct s_vector
{
	double	x;
	double	y;
}				t_vector;

typedef struct s_img
{
	char	*data_address;
	void	*img_ptr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}				t_img;

typedef struct s_keys
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	left;
	int	right;
}				t_keys;

typedef struct s_player
{
	t_vector		position;
	t_vector		direction;
	t_vector		camera_plane;
	t_keys			keys;
}				t_player;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
}				t_map;

typedef struct s_scene
{
	int			floor_color;
	int			ceiling_color;
	char		*texture_path[TEX_COUNT];
	char		start_direction;
	t_vector	start_position;
	t_map		map;
}				t_scene;

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*window;
	t_img	frame_buffer;
}				t_mlx;

typedef struct s_game
{
	t_img		textures[TEX_COUNT];
	t_mlx		mlx;
	t_player	player;
	t_scene		scene;
}				t_game;

typedef struct s_minimap
{
}				t_minimap;

// UTILS
int		chartab_length(char **tab);
void	free_char_tab(char **tab);
int		skip_spaces(char *line);

// VALIDATION
int		check_path(char *filename);
int		check_extension(char *filename);

// PARSING
int		parse_header(char **filecontent, t_scene *scene);
char	**append_line(char **filecontent, char *line);
char	**read_file(int fd);
#endif