#include "cub3d.h"

int	check_chars(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (map->grid[y])
	{
		x = 0;
		while (map->grid[y][x])
		{
			if (!check_map_char(map->grid[y][x]))
				return (format_error("Invalid character in map"));
			x++;
		}
		y++;
	}
	return (1);
}

int	check_closed(t_map *map)
{
	int	y;
	int	x;

	y = 0;
	while (map->grid[y])
	{
		x = 0;
		while (map->grid[y][x])
		{
			if (is_walkable(map->grid[y][x]))
			{
				if (has_void_neighbour(map->grid, y, x))
					return (format_error("Unclosed map"));
			}
			x++;
		}
		y++;
	}
	return (1);
}

int	check_map_char(char c)
{
	static const char	valid_char[] = " 01NSWE";
	int					i;

	i = 0;
	while (valid_char[i])
	{
		if (c == valid_char[i])
			return (1);
		i++;
	}
	return (0);
}

int	find_player(t_scene *scene)
{
	int	x;
	int	y;
	int	found;

	y = 0;
	found = 0;
	while (scene->map.grid[y])
	{
		x = 0;
		while (scene->map.grid[y][x])
		{
			if (set_player_start(scene, scene->map.grid[y][x], y, x))
				found++;
			x++;
		}
		y++;
	}
	if (found != 1)
		return (format_error("One player in map is required"));
	return (1);
}

int	validate_map(t_scene *scene)
{
	if (!check_chars(&scene->map))
		return (0);
	if (!find_player(scene))
		return (0);
	if (!check_closed(&scene->map))
		return (0);
	return (1);
}
