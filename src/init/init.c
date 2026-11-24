/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrasse <jstrasse@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/24 00:50:59 by jstrasse          #+#    #+#             */
/*   Updated: 2026/11/24 00:58:58 by jstrasse         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_scene(t_scene *scene)
{
	ft_bzero(scene, sizeof(t_scene));
	scene->ceiling_color = COLOR_UNSET;
	scene->floor_color = COLOR_UNSET;
}

void	init_game(t_game *game)
{
	ft_bzero(game, sizeof(t_game));
	init_scene(&game->scene);
}

void	init_player(t_game *game)
{
	t_player	*player;

	player = &game->player;
	player->position = game->scene.start_position;
	if (game->scene.start_direction == 'N')
		player->direction = new_vector(0, -1);
	else if (game->scene.start_direction == 'S')
		player->direction = new_vector(0, 1);
	else if (game->scene.start_direction == 'E')
		player->direction = new_vector(1, 0);
	else if (game->scene.start_direction == 'W')
		player->direction = new_vector(-1, 0);
	player->camera_plane = vec_scale(vec_perpendicular_right(player->direction), PLANE); 
}
