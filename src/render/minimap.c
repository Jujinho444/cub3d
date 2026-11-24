/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrasse <jstrasse@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/24 01:26:08 by jstrasse          #+#    #+#             */
/*   Updated: 2026/11/24 01:26:08 by jstrasse         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	tile_color(char c)
{
	if (is_walkable(c))
		return (MINIMAP_FLOOR);
	if (c == '1')
		return (MINIMAP_WALL);
	if (c == ' ')
		return (MINIMAP_VOID);
	return (COLOR_UNSET);
}

void	draw_fov(t_game *game)
{
	t_vector	vector;
	t_player	*player;
	double		camera_x;
	int			i;

	i = 0;
	player = &game->player;
	while (i < MINIMAP_FOV_RAYS)
	{
		camera_x = 2.0 * i / (MINIMAP_FOV_RAYS - 1) - 1;
		vector.x = player->direction.x + player->camera_plane.x * camera_x;
		vector.y = player->direction.y + player->camera_plane.y * camera_x;
		draw_ray(game, vector, player->position);
		i++;
	}
}

void	draw_2Dmap(t_game *game)
{
	char	**grid;
	t_img	*img;
	int		x;
	int		y;

	y = 0;
	grid = game->scene.map.grid;
	img = &game->mlx.frame_buffer;
	while (grid[y])
	{
		x = 0;
		while (grid[y][x])
		{
			draw_square(img, x * TILE, y * TILE, TILE, tile_color(grid[y][x]));
			x++;
		}
		y++;
	}
}

void	draw_minimap_player(t_game *game)
{
	double	px;
	double	py;
	t_img	*img;

	img = &game->mlx.frame_buffer;
	px = (game->player.position.x * TILE) - (MINIMAP_PLAYER_SIZE / 2);
	py = (game->player.position.y * TILE) - (MINIMAP_PLAYER_SIZE / 2);
	draw_square(img, (int)px, (int)py, MINIMAP_PLAYER_SIZE, MINIMAP_PLAYER);
}

void	draw_minimap(t_game *game)
{
	draw_2Dmap(game);
	draw_fov(game);
	draw_minimap_player(game);
}