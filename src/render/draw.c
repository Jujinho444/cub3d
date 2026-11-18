/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aganz <aganz@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 22:54:04 by aganz             #+#    #+#             */
/*   Updated: 2026/11/18 16:40:35 by aganz            ###   ########.fr       */
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
