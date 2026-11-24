/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrasse <jstrasse@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/23 23:08:31 by jstrasse          #+#    #+#             */
/*   Updated: 2026/11/23 23:08:31 by jstrasse         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	game_loop(t_game *game)
{
	double	delta_time;
	double	current_time;

	current_time = get_time_seconds();
	delta_time = current_time - game->last_frame;
	game->last_frame = current_time;
	if (delta_time > MAX_DELTATIME)
		delta_time = MAX_DELTATIME;
	update_player(game, delta_time);
	draw_background(game);
	draw_minimap(game);
	mlx_put_image_to_window(game->mlx.mlx_ptr, game->mlx.window,
			game->mlx.frame_buffer.img_ptr, 0, 0);
	return (0);
}
