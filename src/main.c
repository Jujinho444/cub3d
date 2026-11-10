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