/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aganz <aganz@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/15 16:56:49 by aganz             #+#    #+#             */
/*   Updated: 2026/11/18 11:31:07 by aganz            ###   ########.fr       */
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