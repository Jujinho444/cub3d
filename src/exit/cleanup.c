/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrasse <jstrasse@student.42lausanne.ch>    +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/26 10:53:10 by jstrasse          #+#    #+#             */
/*   Updated: 2026/11/26 10:53:15 by jstrasse         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	destroy_image(void *mlx_ptr, t_img *img)
{
	if (img->img_ptr)
	{
		mlx_destroy_image(mlx_ptr, img->img_ptr);
		img->img_ptr = NULL;
	}
}

static void	destroy_images(t_game *game)
{
	int	i;

	i = 0;
	destroy_image(game->mlx.mlx_ptr, &game->mlx.frame_buffer);
	while (i < TEX_COUNT)
	{
		destroy_image(game->mlx.mlx_ptr, &game->textures[i]);
		i++;
	}
}

int	cleanup_game(t_game *game)
{
	if (!game)
		return (0);
	if (game->mlx.mlx_ptr != NULL)
	{
		destroy_images(game);
		if (game->mlx.window)
		{
			mlx_destroy_window(game->mlx.mlx_ptr, game->mlx.window);
			game->mlx.window = NULL;
		}
		mlx_destroy_display(game->mlx.mlx_ptr);
		free(game->mlx.mlx_ptr);
		game->mlx.mlx_ptr = NULL;
	}
	free_scene(&game->scene);
	return (0);
}
