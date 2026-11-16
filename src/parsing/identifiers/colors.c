/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aganz <aganz@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/15 22:39:33 by aganz             #+#    #+#             */
/*   Updated: 2026/11/16 21:22:22 by aganz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	read_component(char *string, int *i, int *component)
{
	int	start;

	(*component) = 0;
	(*i) += skip_spaces(&string[*i]);
	start = (*i);
	while (ft_isdigit(string[*i]))
	{
		(*component) = (*component) * 10 + (string[*i] - '0');
		if ((*component) > 255)
			return (format_error("Color value out of range"));
		(*i)++;
	}
	if (start == (*i))
		return (format_error("Missing color value"));
	(*i) += skip_spaces(&string[*i]);
	return (1);
}

int	parse_color(char *value)
{
	int	i;
	int	rgb[3];
	int	j;

	j = 0;
	i = 0;
	while (j < 3)
	{
		if (!read_component(value, &i, &rgb[j]))
			return (COLOR_UNSET);
		if ((value[i] != ',' && j != 2) || (value[i] != '\0' && j == 2))
		{
			format_error("Incorrect color format");
			return (COLOR_UNSET);
		}
		i++;
		j++;
	}
	return (rgb[0] * 65536 + rgb[1] * 256 + rgb[2]);
}
