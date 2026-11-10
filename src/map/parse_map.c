#include "cub3d.h"

int	get_map_size(char **filecontent, int start, t_map *map)
{
	int	width;
	int	height;

	height = 0;
	while (filecontent[start])
	{
		if (is_empty(filecontent[start])
			&& (filecontent[start + 1] && !is_empty(filecontent[start + 1])))
			return (format_error("Incorrect Map, empty line inside map"));
		width = line_length(filecontent[start]);
		if (width > map->width)
			map->width = width;
		if (!is_empty(filecontent[start]))
			height++;
		start++;
	}
	map->height = height;
	return (1);
}

char	*create_row(int width)
{
	char	*row;
	int		i;

	i = 0;
	row = malloc(sizeof(char) * (width + 3));
	if (!row)
	{
		system_error("malloc");
		return (NULL);
	}
	while (i < width + 2)
	{
		row[i] = ' ';
		i++;
	}
	row[i] = '\0';
	return (row);
}

int	build_map_grid(char **filecontent, int start, t_map *map)
{
	char	**grid;
	char	*src;
	int		i;

	i = 0;
	grid = ft_calloc(map->height + 3, sizeof(char *));
	if (!grid)
		return (system_error("malloc"));
	while (i < map->height + 2)
	{
		grid[i] = create_row(map->width);
		if (!grid[i])
		{
			free_char_tab(grid);
			return (0);
		}
		if (i >= 1 && i <= map->height)
		{
			src = filecontent[start + i - 1];
			ft_memcpy(grid[i] + 1, src, line_length(src));
		}
		i++;
	}
	map->grid = grid;
	return (1);
}

int	is_map_line(char *line)
{
	int	i;

	i = 0;
	if (is_empty(line))
		return (0);
	while (line[i] && line[i] != '\n')
	{
		if (!check_map_char(line[i]))
			return (0);
		i++;
	}
	return (1);
}