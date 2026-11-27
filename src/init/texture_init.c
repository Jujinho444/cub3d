/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrasse <jstrasse@student.42lausanne.ch>    +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/27 22:09:46 by jstrasse          #+#    #+#             */
/*   Updated: 2026/11/27 22:09:46 by jstrasse         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	load_texture(void *mlx_ptr, char *path, t_img *img)
{
	img->img_ptr = mlx_xpm_file_to_image(mlx_ptr, path, &img->width,
			&img->height);
	if (!img->img_ptr)
		return (format_error("Failed to load texture"));
	img->data_address = mlx_get_data_addr(img->img_ptr,
			&img->bits_per_pixel, &img->line_length, &img->endian);
	return (1);
}

int	init_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < TEX_COUNT)
	{
		if (!load_texture(game->mlx.mlx_ptr, game->scene.texture_path[i],
				&game->textures[i]))
			return (0);
		i++;
	}
	return (1);
}
