#include "cub3d.h"

int	get_identifier(char *line)
{
	static const char	*id[ID_COUNT] = {"NO", "SO", "WE", "EA", "F", "C"};
	int					indice;

	indice = 0;
	line = line + skip_spaces(line);
	while (indice < ID_COUNT)
	{
		if (!ft_strncmp(line, id[indice], ft_strlen(id[indice]))
			&& line[ft_strlen(id[indice])] == ' ')
			return (indice);
		indice++;
	}
	return (-1);
}

int	is_set(t_scene *scene, int id)
{
	if (id < TEX_COUNT)
		return (scene->texture_path[id] != NULL);
	else if (id == FLOOR)
		return (scene->floor_color != COLOR_UNSET);
	return (scene->ceiling_color != COLOR_UNSET);
}

int	all_found(t_scene *scene)
{
	int	id;

	id = 0;
	while (id < ID_COUNT)
	{
		if (!is_set(scene, id))
			return (0);
		id++;
	}
	return (1);
}
