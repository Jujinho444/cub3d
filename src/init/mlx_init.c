/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrasse <jstrasse@student.42lausanne.ch>    +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/26 11:12:48 by jstrasse          #+#    #+#             */
/*   Updated: 2026/11/26 11:13:56 by jstrasse         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_mlx(t_game *game)
{
	game->mlx.mlx_ptr = mlx_init();
	if (!game->mlx.mlx_ptr)
		return (format_error("Failed to initialize mlx"));
	game->mlx.window = mlx_new_window(game->mlx.mlx_ptr, WIN_WIDTH,
			WIN_HEIGHT, "cub3d");
	if (!game->mlx.window)
		return (format_error("Failed to open window"));
	return (init_frame(game));
}

int	init_frame(t_game *game)
{
	t_img	*frame;

	frame = &game->mlx.frame_buffer;
	frame->img_ptr = mlx_new_image(game->mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	if (!frame->img_ptr)
		return (format_error("Failed to create new image"));
	frame->data_address = mlx_get_data_addr(frame->img_ptr,
			&frame->bits_per_pixel, &frame->line_length, &frame->endian);
	frame->width = WIN_WIDTH;
	frame->height = WIN_HEIGHT;
	return (1);
}
