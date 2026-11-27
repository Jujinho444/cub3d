/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrasse <jstrasse@student.42lausanne.ch>    +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/27 22:26:51 by jstrasse          #+#    #+#             */
/*   Updated: 2026/11/27 22:29:05 by jstrasse         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_tex_coord(t_column *col, t_ray *ray, int line_height)
{
	int	raw_start;

	col->tex_x = col->texture->width * ray->point_of_impact;
	if (ray->wall_type == WEST || ray->wall_type == SOUTH)
		col->tex_x = col->texture->width - col->tex_x - 1;
	col->tex_step = 1.0 * col->texture->height / line_height;
	raw_start = WIN_HEIGHT / 2 - line_height / 2;
	col->tex_position = (col->draw_start - raw_start) * col->tex_step;
}

void	init_column(t_column *col, t_ray *ray, t_game *game)
{
	int		line_height;
	double	dist_to_wall;

	dist_to_wall = ray->distance_to_wall;
	if (dist_to_wall < MIN_DIST_TO_WALL)
		dist_to_wall = MIN_DIST_TO_WALL;
	line_height = WIN_HEIGHT / dist_to_wall;
	if (line_height < 1)
		line_height = 1;
	col->draw_start = WIN_HEIGHT / 2 - line_height / 2;
	col->draw_end = col->draw_start + line_height - 1;
	if (col->draw_start < 0)
		col->draw_start = 0;
	if (col->draw_end >= WIN_HEIGHT)
		col->draw_end = WIN_HEIGHT - 1;
	col->texture = &game->textures[ray->wall_type];
	set_tex_coord(col, ray, line_height);
}

int	get_texel(t_img *texture, int x, int y)
{
	char	*texel_address;

	if (x < 0)
		x = 0;
	if (x >= texture->width)
		x = texture->width - 1;
	if (y < 0)
		y = 0;
	if (y >= texture->height)
		y = texture->height - 1;
	texel_address = texture->data_address + y * texture->line_length
		+ x * (texture->bits_per_pixel / 8);
	return (*(unsigned int *)texel_address);
}

void	render_frame(t_game *game)
{
	t_ray		ray;
	t_column	col;
	int			x;

	x = 0;
	while (x < WIN_WIDTH)
	{
		ray = cast_ray(game, x);
		init_column(&col, &ray, game);
		draw_column(game, &col, x);
		x++;
	}
	draw_minimap(game);
	mlx_put_image_to_window(game->mlx.mlx_ptr, game->mlx.window,
		game->mlx.frame_buffer.img_ptr, 0, 0);
}
