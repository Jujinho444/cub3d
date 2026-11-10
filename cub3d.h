/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jefferson <jefferson@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/01 19:58:01 by aganz             #+#    #+#             */
/*   Updated: 2026/11/10 09:01:00 by jefferson        ###   ########.fr       */
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

typedef enum e_identifiers
{
	FLOOR = TEX_COUNT,
	CEILING,
	ID_COUNT
}			t_identifiers;

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

// COLORS.C
int		read_component(char *string, int *i, int *component);
int		parse_color(char *value);

// FREE.C
void	free_char_tab(char **tab);
void	free_scene(t_scene *scene);

//IDENTIFIERS_UTILS.C
int		get_identifier(char *line);
int		is_set(t_scene *scene, int id);
int		all_found(t_scene *scene);

// INIT.C
void	init_scene(t_scene *scene);

// MAP_UTILS.C
int		line_length(char *line);
int		is_player_char(char c);
int		is_walkable(char c);
int		set_player_start(t_scene *scene, char c, int y, int x);
int		has_void_neighbour(char **grid, int y, int x);

// MAP_VALIDATION.C
int		check_chars(t_map *map);
int		check_closed(t_map *map);
int		check_map_char(char c);
int		find_player(t_scene *scene);
int		validate_map(t_scene *scene);

// PARSE_MAP.C
int		get_map_size(char **filecontent, int start, t_map *map);
char	*create_row(int width);
int		build_map_grid(char **filecontent, int start, t_map *map);
int		is_map_line(char *line);

// PARSE_FILE.C
char	**append_line(char **filecontent, char *line);
char	**read_file(int fd);
char	**load_file(char *path);
int		parse_content(char **file, t_scene *scene);
int		parse_file(char *path, t_scene *scene);

// PARSE_IDENTIFIERS.C
char	*extract_value(char *line, int id);
int		store_value(t_scene *scene, int id, char *value);
int		parse_line(char *filecontent_line, t_scene *scene);
int		parse_identifiers(char **filecontent, t_scene *scene);

// PATH_VALIDATION.C
int		check_extension(char *filename);
int		check_path(char *filename);

//UTILS.C
int		chartab_length(char **tab);
int		skip_spaces(char *line);
int		is_empty(char *line);
int		format_error(char *msg);
int		system_error(char *msg);

#endif