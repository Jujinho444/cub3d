/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aganz <aganz@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/15 15:30:11 by aganz             #+#    #+#             */
/*   Updated: 2026/11/15 16:46:46 by aganz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		format_error("Wrong number of arguments in program");
		return (1);
	}
	init_scene(&game.scene);
	if (!parse_file(argv[1], &game.scene))
		return (1);
	free_scene(&game.scene);
	return (0);
}
