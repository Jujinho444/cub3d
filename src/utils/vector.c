/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrasse <jstrasse@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/24 00:19:45 by jstrasse          #+#    #+#             */
/*   Updated: 2026/11/24 00:44:21 by jstrasse         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_vector	new_vector(double x, double y)
{
	t_vector	result;

	result.x = x;
	result.y = y;
	return (result);
}

t_vector	vec_add(t_vector vector_a, t_vector vector_b)
{
	t_vector	result;

	result.x = vector_a.x + vector_b.x;
	result.y = vector_a.y + vector_b.y;
	return (result);
}

t_vector	vec_scale(t_vector vector, double factor)
{
	t_vector	result;

	result.x = vector.x * factor;
	result.y = vector.y * factor;
	return (result);
}

t_vector	vec_perpendicular_right(t_vector vector)
{
	t_vector	result;

	result.x = -vector.y;
	result.y = vector.x;
	return (result);
}

t_vector	rotate_vector(t_vector vector, double angle)
{
	t_vector	result;

	result.x = vector.x * cos(angle) - vector.y * sin(angle);
	result.y = vector.x * sin(angle) + vector.y * cos(angle);
	return (result);
}
