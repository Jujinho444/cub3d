/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrasse <jstrasse@student.42lausanne.ch>    +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/26 11:18:06 by jstrasse          #+#    #+#             */
/*   Updated: 2026/11/26 11:18:06 by jstrasse         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	get_time_seconds(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec + (double)tv.tv_usec / 1000000);
}
