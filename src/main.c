/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aganz <aganz@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/15 15:30:11 by aganz             #+#    #+#             */
/*   Updated: 2026/11/19 19:36:28 by aganz            ###   ########.fr       */
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
	init_game(&game);
	if (!parse_file(argv[1], &game.scene))
	{
		cleanup_game(&game);
		return (1);
	}
	if (!init_mlx(&game))
	{
		cleanup_game(&game);
		return (1);
	}
	draw_background(&game);
	mlx_put_image_to_window(game.mlx.mlx_ptr, game.mlx.window,
			game.mlx.frame_buffer.img_ptr, 0, 0);
	mlx_hook(game.mlx.window, 17, 0, close_game, &game);
	mlx_hook(game.mlx.window, 2, 1L << 0, handle_keypress, &game);
	mlx_loop(game.mlx.mlx_ptr);
	cleanup_game(&game);
	return (0);
}
