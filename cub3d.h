/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrasse <jstrasse@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/24 01:26:33 by jstrasse          #+#    #+#             */
/*   Updated: 2026/11/24 01:42:47 by jstrasse         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx/mlx.h"
# include "libft/libft.h"
# include <X11/X.h>
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>

//define windows
# define WIN_WIDTH 1900
# define WIN_HEIGHT 1090

//define keys
# define KEY_W		119
# define KEY_A		97
# define KEY_S		115
# define KEY_D		100
# define KEY_LEFT	65361
# define KEY_RIGHT	65363
# define KEY_ESC	65307

//define speed
# define MOVESPEED 3.0
# define ROTSPEED 2.0
# define PLANE 0.66
# define COLOR_UNSET -1
# define WALL_MARGIN 0.2
# define MAX_DELTATIME 0.05
# define TILE 24
# define MINIMAP_PLAYER_SIZE 6 // TILE divided by 4
# define MINIMAP_WALL 0x000000
# define MINIMAP_VOID 0xFFFFFF
# define MINIMAP_FLOOR 0x00129A
# define MINIMAP_PLAYER 0xEB3324
# define MINIMAP_DIRECTION 0xFFFD55
# define MINIMAP_FOV_RAYS 42

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

typedef struct s_vector_int
{
	int	x;
	int	y;
}				t_vector_int;

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

typedef struct s_ray
{
	double			distance_to_wall;
	t_vector_int	current_position;
	t_textures		wall;
	double			point_of_impact;
	t_vector		delta_dist;
	t_vector		side_dist;
	t_vector_int	step;
	t_vector		ray_dir;
	int				last_axis;
}				t_ray;

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
	t_vector	position;
	t_vector	direction;
	t_vector	camera_plane;
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
	t_keys		keys;
	t_scene		scene;
	double		last_frame;
}				t_game;

// INIT
/*init.c*/
void	init_scene(t_scene *scene);
void	init_game(t_game *game);
void	init_player(t_game *game);
/*mlx_init.c*/
int		init_mlx(t_game *game);
int		init_frame(t_game *game);

// PARSING
/*parse_file.c*/
char	**append_line(char **filecontent, char *line);
char	**read_file(int fd);
char	**load_file(char *path);
int		parse_content(char **file, t_scene *scene);
int		parse_file(char *path, t_scene *scene);
/*path_validation.c*/
int		check_extension(char *filename);
int		check_path(char *filename);
// identifiers
/*colors.c*/
int		read_component(char *string, int *i, int *component);
int		parse_color(char *value);
/*identifiers_utils.c*/
int		get_identifier(char *line);
int		is_set(t_scene *scene, int id);
int		all_found(t_scene *scene);
/* parse_identifiers.c*/
char	*extract_value(char *line, int id);
int		store_value(t_scene *scene, int id, char *value);
int		parse_line(char *filecontent_line, t_scene *scene);
int		parse_identifiers(char **filecontent, t_scene *scene);
// map
/*map_utils.c*/
int		line_length(char *line);
int		is_player_char(char c);
int		is_walkable(char c);
int		set_player_start(t_scene *scene, char c, int y, int x);
int		has_void_neighbour(char **grid, int y, int x);
/*map_validation.c*/
int		check_chars(t_map *map);
int		check_closed(t_map *map);
int		check_map_char(char c);
int		find_player(t_scene *scene);
int		validate_map(t_scene *scene);
/*parse_map.c*/
int		get_map_size(char **filecontent, int start, t_map *map);
char	*create_row(int width);
int		build_map_grid(char **filecontent, int start, t_map *map);
int		is_map_line(char *line);

// GAME
/*game_loop.c*/
int		game_loop(t_game *game);
/*events.c*/
int		handle_keypress(int keycode, t_game *game);
int		handle_keyrelease(int keycode, t_game *game);
/*player.c*/
void	update_player(t_game *game, double delta_time);

// RENDER
/*draw.c*/
void	put_pixel(t_img *img, int x, int y, int color);
void	draw_background(t_game *game);
void	draw_square(t_img *img, int px, int py, int size, int color);
void	draw_ray(t_game *game, t_vector direction, t_vector position);
/*minimap.c*/
void	draw_minimap(t_game *game);
void	draw_fov(t_game *game);
void	draw_minimap_player(t_game *game);
void	draw_2Dmap(t_game *game);

// EXIT
/*cleanup.c*/
int	cleanup_game(t_game *game);
/*free.c*/
void	free_char_tab(char **tab);
void	free_scene(t_scene *scene);
/*game_exit.c*/
int		close_game(t_game *game);

// UTILS
/*utils.c*/
int		chartab_length(char **tab);
int		skip_spaces(char *line);
int		is_empty(char *line);
int		format_error(char *msg);
int		system_error(char *msg);
/*vector.c*/
t_vector	new_vector(double x, double y);
t_vector	vec_add(t_vector vector_a, t_vector vector_b);
t_vector	vec_scale(t_vector vector, double factor);
t_vector	vec_perpendicular_right(t_vector vector);
t_vector	rotate_vector(t_vector vector, double angle);
/*time.c*/
double	get_time_seconds(void);

#endif