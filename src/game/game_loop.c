/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrasse <jstrasse@student.42lausanne.ch>    +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/27 23:33:50 by jstrasse          #+#    #+#             */
/*   Updated: 2026/11/27 23:33:50 by jstrasse         ###   ########.ch       */
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
	if (delta_time < 0)
		delta_time = 0;
	update_player(game, delta_time);
	render_frame(game);
	return (0);
}
