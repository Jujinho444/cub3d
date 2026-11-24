/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrasse <jstrasse@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/20 16:19:30 by jstrasse          #+#    #+#             */
/*   Updated: 2026/11/20 16:19:45 by jstrasse         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	setup_hooks(t_game *game)
{
	mlx_hook(game->mlx.window, DestroyNotify, StructureNotifyMask,
		close_game, game);
	mlx_hook(game->mlx.window, KeyPress, KeyPressMask,
		handle_keypress, game);
	mlx_hook(game->mlx.window, KeyRelease, KeyReleaseMask,
		handle_keyrelease, game);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		format_error("Wrong number of arguments in program");
		return (1);
	}
	init_game(&game);
	if (!parse_file(argv[1], &game.scene))
	{
		cleanup_game(&game);
		return (1);
	}
	init_player(&game);
	if (!init_mlx(&game))
	{
		cleanup_game(&game);
		return (1);
	}
	setup_hooks(&game);
	game.last_frame = get_time_seconds();
	mlx_loop_hook(game.mlx.mlx_ptr, game_loop, &game);
	mlx_loop(game.mlx.mlx_ptr);
	cleanup_game(&game);
	return (0);
}
