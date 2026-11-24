/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrasse <jstrasse@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/24 01:23:52 by jstrasse          #+#    #+#             */
/*   Updated: 2026/11/24 01:24:04 by jstrasse         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*pixel_address;

	if (x < 0 || x >= img->width)
		return ;
	if (y < 0 || y >= img->height)
		return ;
	pixel_address = img->data_address + y * img->line_length
						+ x * (img->bits_per_pixel / 8);
	*(unsigned int *)pixel_address = color;
}

void	draw_background(t_game *game)
{
	int		x;
	int		y;
	t_img	*frame;

	frame = &game->mlx.frame_buffer;
	y = 0;
	while (y < frame->height)
	{
		x = 0;
		while (x < frame->width)
		{
			if (y < (frame->height / 2))
				put_pixel(frame, x, y, game->scene.ceiling_color);
			else
				put_pixel(frame, x, y, game->scene.floor_color);
			x++;
		}
		y++;
	}
}

void	draw_square(t_img *img, int px, int py, int size, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			put_pixel(img, px + x, py + y, color);
			x++;
		}
		y++;
	}
}

void	draw_ray(t_game *game, t_vector direction, t_vector position)
{
	double	px;
	double	py;
	int		i;
	t_img	*img;

	img = &game->mlx.frame_buffer;
	i = 0;
	while (i < TILE)
	{
		px = position.x * TILE + direction.x * i;
		py = position.y * TILE + direction.y * i;
		put_pixel(img, (int)px, (int)py, MINIMAP_DIRECTION);
		i++;
	}
}
