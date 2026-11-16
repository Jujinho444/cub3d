/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aganz <aganz@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/15 16:47:45 by aganz             #+#    #+#             */
/*   Updated: 2026/11/15 16:53:12 by aganz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	chartab_length(char **tab)
{
	int	i;

	if (!tab)
		return (0);
	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int	skip_spaces(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	return (i);
}

int	is_empty(char *line)
{
	int	i;

	i = skip_spaces(line);
	return (line[i] == '\n' || line[i] == '\0');
}

int	format_error(char *msg)
{
	write(STDERR_FILENO, "Error\n", 6);
	ft_putendl_fd(msg, STDERR_FILENO);
	return (0);
}

int	system_error(char *msg)
{
	write(STDERR_FILENO, "Error\n", 6);
	perror(msg);
	return (0);
}
