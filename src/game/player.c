/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrasse <jstrasse@student.42lausanne.ch>    +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/26 10:53:34 by jstrasse          #+#    #+#             */
/*   Updated: 2026/11/26 10:53:34 by jstrasse         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double	margin(double d)
{
	if (d > 0)
		return (WALL_MARGIN);
	if (d < 0)
		return (-WALL_MARGIN);
	return (0);
}

static void	move_player(t_game *game, t_vector	delta)
{
	t_vector	target;
	char		**grid;
	t_vector	*position;

	position = &game->player.position;
	grid = game->scene.map.grid;
	target = vec_add(*position, delta);
	if (is_walkable(grid[(int)position->y][(int)(target.x + margin(delta.x))]))
		position->x = target.x;
	if (is_walkable(grid[(int)(target.y + margin(delta.y))][(int)position->x]))
		position->y = target.y;
}

static void	rotate_player(t_player *player, double angle)
{
	player->direction = rotate_vector(player->direction, angle);
	player->camera_plane = rotate_vector(player->camera_plane, angle);
}

void	update_player(t_game *game, double delta_time)
{
	t_player	*player;
	t_vector	dir;
	double		step;
	double		angle;

	step = MOVESPEED * delta_time;
	angle = ROTSPEED * delta_time;
	player = &game->player;
	dir = player->direction;
	if (game->keys.w)
		move_player(game, vec_scale(dir, step));
	if (game->keys.s)
		move_player(game, vec_scale(dir, -step));
	if (game->keys.d)
		move_player(game, vec_scale(vec_perpendicular_right(dir), step));
	if (game->keys.a)
		move_player(game, vec_scale(vec_perpendicular_right(dir), -step));
	if (game->keys.left)
		rotate_player(player, -angle);
	if (game->keys.right)
		rotate_player(player, angle);
}
