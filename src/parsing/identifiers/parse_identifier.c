/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_identifier.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrasse <jstrasse@student.42lausanne.ch>    +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/26 11:14:41 by jstrasse          #+#    #+#             */
/*   Updated: 2026/11/26 11:14:41 by jstrasse         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*extract_value(char *line, int id)
{
	int		i;
	char	*result;

	if (id < TEX_COUNT)
		i = 2;
	else
		i = 1;
	line = line + skip_spaces(line) + i;
	result = ft_strtrim(line, " \n");
	if (!result)
	{
		system_error("malloc");
		return (NULL);
	}
	if (result[0] == '\0')
	{
		free(result);
		format_error("identifier has empty value");
		return (NULL);
	}
	return (result);
}

int	store_value(t_scene *scene, int id, char *value)
{
	int	*color;

	if (id < TEX_COUNT)
	{
		if (ft_strchr(value, ' '))
		{
			free(value);
			return (format_error("Space in texture path"));
		}
		scene->texture_path[id] = value;
		return (1);
	}
	if (id == FLOOR)
		color = &scene->floor_color;
	else
		color = &scene->ceiling_color;
	*color = parse_color(value);
	free(value);
	return (*color != COLOR_UNSET);
}

int	parse_line(char *filecontent_line, t_scene *scene)
{
	int		id;
	char	*value;

	id = get_identifier(filecontent_line);
	if (id == -1)
		return (format_error("Unknown identifier"));
	if (is_set(scene, id))
		return (format_error("Identifier is duplicated"));
	value = extract_value(filecontent_line, id);
	if (!value)
		return (0);
	return (store_value(scene, id, value));
}

int	parse_identifiers(char **filecontent, t_scene *scene)
{
	int	i;

	i = 0;
	while (filecontent[i])
	{
		if (!is_empty(filecontent[i]))
		{
			if (all_found(scene))
			{
				if (get_identifier(filecontent[i]) != -1)
					return (format_error("identifier is duplicated"));
				return (i);
			}
			if (is_map_line(filecontent[i]))
				return (format_error("missing element in header"));
			if (!parse_line(filecontent[i], scene))
				return (0);
		}
		i++;
	}
	if (all_found(scene))
		return (format_error("missing map"));
	else
		return (format_error("missing element in header"));
}
