/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aganz <aganz@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 10:38:30 by aganz             #+#    #+#             */
/*   Updated: 2026/11/25 13:42:41 by aganz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_mlx(t_game *game)
{
	game->mlx.mlx_ptr = mlx_init();
	if (!game->mlx.mlx_ptr)
		return (format_error("Failed to initialize mlx"));
	game->mlx.window = mlx_new_window(game->mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT,
						"cub3d");
	if (!game->mlx.window)
		return (format_error("Failed to open window"));
	if (!init_frame(game))
		return (0);
	return (init_textures(game));
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