/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrasse <jstrasse@student.42lausanne.ch>    +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/26 10:52:52 by jstrasse          #+#    #+#             */
/*   Updated: 2026/11/26 10:53:03 by jstrasse         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_scene(t_scene *scene)
{
	int	i;

	i = 0;
	while (i < TEX_COUNT)
	{
		free(scene->texture_path[i]);
		scene->texture_path[i] = NULL;
		i++;
	}
	free_char_tab(scene->map.grid);
	scene->map.grid = NULL;
}

void	free_char_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
