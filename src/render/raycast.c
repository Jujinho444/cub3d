/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrasse <jstrasse@student.42lausanne.ch>    +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/27 22:10:53 by jstrasse          #+#    #+#             */
/*   Updated: 2026/11/27 22:11:00 by jstrasse         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_ray(t_ray *ray, t_player *player, int screen_x)
{
	ray->direction = get_ray_dir(player, screen_x);
	ray->current_cell = get_ray_cell(player);
	ray->delta_dist = get_delta_dist(ray->direction);
	init_step_and_side(ray, player->position);
}

void	dda_loop(t_ray *ray, char **map_grid)
{
	int	wall_hit;

	wall_hit = 0;
	while (wall_hit == 0)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->current_cell.x += ray->step.x;
			ray->last_axis = AXIS_X;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->current_cell.y += ray->step.y;
			ray->last_axis = AXIS_Y;
		}
		if (!is_walkable(map_grid[ray->current_cell.y][ray->current_cell.x]))
			wall_hit = 1;
	}
}

void	set_wall_hit(t_ray *ray, t_player *player)
{
	double	impact;

	if (ray->last_axis == AXIS_X)
	{
		ray->distance_to_wall = ray->side_dist.x - ray->delta_dist.x;
		impact = player->position.y + ray->distance_to_wall * ray->direction.y;
		if (ray->step.x == 1)
			ray->wall_type = EAST;
		else
			ray->wall_type = WEST;
	}
	else
	{
		ray->distance_to_wall = ray->side_dist.y - ray->delta_dist.y;
		impact = player->position.x + ray->distance_to_wall * ray->direction.x;
		if (ray->step.y == 1)
			ray->wall_type = SOUTH;
		else
			ray->wall_type = NORTH;
	}
	ray->point_of_impact = impact - floor(impact);
}

t_ray	cast_ray(t_game *game, int screen_x)
{
	t_ray	ray;

	init_ray(&ray, &game->player, screen_x);
	dda_loop(&ray, game->scene.map.grid);
	set_wall_hit(&ray, &game->player);
	return (ray);
}
