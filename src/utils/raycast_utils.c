/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrasse <jstrasse@student.42lausanne.ch>    +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/27 22:09:16 by jstrasse          #+#    #+#             */
/*   Updated: 2026/11/27 22:09:21 by jstrasse         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_vector	get_ray_dir(t_player *player, int screen_x)
{
	t_vector	ray_dir;
	double		camera_x;

	camera_x = 2.0 * screen_x / WIN_WIDTH - 1;
	ray_dir = vec_add(player->direction,
			vec_scale(player->camera_plane, camera_x));
	return (ray_dir);
}

// Divided by 0 is undefined behavior in C
static double	axis_delta_dist(double ray_axis)
{
	if (ray_axis == 0)
		return (INFINITY);
	else
		return (fabs(1 / ray_axis));
}

t_vector	get_delta_dist(t_vector ray_dir)
{
	t_vector	delta_dist;

	delta_dist.x = axis_delta_dist(ray_dir.x);
	delta_dist.y = axis_delta_dist(ray_dir.y);
	return (delta_dist);
}

t_point	get_ray_cell(t_player *player)
{
	t_point	cell;

	cell.x = (int)player->position.x;
	cell.y = (int)player->position.y;
	return (cell);
}

void	init_step_and_side(t_ray *ray, t_vector position)
{
	if (ray->direction.x < 0)
	{
		ray->step.x = -1;
		ray->side_dist.x = (position.x - ray->current_cell.x)
			* ray->delta_dist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->side_dist.x = (ray->current_cell.x + 1.0 - position.x)
			* ray->delta_dist.x;
	}
	if (ray->direction.y < 0)
	{
		ray->step.y = -1;
		ray->side_dist.y = (position.y - ray->current_cell.y)
			* ray->delta_dist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->side_dist.y = (ray->current_cell.y + 1.0 - position.y)
			* ray->delta_dist.y;
	}
}
