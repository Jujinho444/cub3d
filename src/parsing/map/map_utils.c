#include "cub3d.h"

int	line_length(char *line)
{
	int	length;

	length = 0;
	while (line[length] != '\0' && line[length] != '\n')
		length++;
	return (length);
}

int	is_player_char(char c)
{
	if (c == 'N' || c == 'W' || c == 'E' || c == 'S')
		return (1);
	return (0);
}

int	is_walkable(char c)
{
	if (c == '0' || is_player_char(c))
		return (1);
	return (0);
}

int	set_player_start(t_scene *scene, char c, int y, int x)
{
	if (is_player_char(c))
	{
		scene->start_direction = c;
		scene->start_position.x = x + 0.5;
		scene->start_position.y = y + 0.5;
		return (1);
	}
	return (0);
}

int	has_void_neighbour(char **grid, int y, int x)
{
	int	dx;
	int	dy;

	dy = -1;
	while (dy <= 1)
	{
		dx = -1;
		while (dx <= 1)
		{
			if (grid[y + dy][x + dx] == ' ')
				return (1);
			dx++;
		}
		dy++;
	}
	return (0);
}
