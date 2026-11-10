#include "cub3d.h"

char	**append_line(char **filecontent, char *line)
{
	int		length;
	int		i;
	char	**newfilecontent;

	i = 0;
	length = chartab_length(filecontent);
	newfilecontent = malloc(sizeof(char *) * (length + 2));
	if (!newfilecontent)
	{
		free_char_tab(filecontent);
		free(line);
		system_error("malloc");
		return (NULL);
	}
	while (i < length)
	{
		newfilecontent[i] = filecontent[i];
		i++;
	}
	newfilecontent[length] = line;
	newfilecontent[length + 1] = NULL;
	free(filecontent);
	return (newfilecontent);
}

char	**read_file(int fd)
{
	char	**filecontent;
	char	*line;

	filecontent = ft_calloc(1, sizeof(char *));
	if (!filecontent)
	{
		system_error("malloc");
		return (NULL);
	}
	line = get_next_line(fd);
	while (line)
	{
		filecontent = append_line(filecontent, line);
		if (!filecontent)
		{
			gnl_cleanup();
			return (NULL);
		}
		line = get_next_line(fd);
	}
	return (filecontent);
}

char	**load_file(char *path)
{
	int		fd;
	char	**file;

	if (!check_extension(path))
		return (NULL);
	if (!check_path(path))
		return (NULL);
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		system_error(path);
		return (NULL);
	}
	file = read_file(fd);
	close(fd);
	return (file);
}

int	parse_content(char **file, t_scene *scene)
{
	int	map_index;

	map_index = parse_identifiers(file, scene);
	if (!map_index)
		return (0);
	if (!get_map_size(file, map_index, &scene->map))
		return (0);
	if (!build_map_grid(file, map_index, &scene->map))
		return (0);
	if (!validate_map(scene))
		return (0);
	return (1);
}

int	parse_file(char *path, t_scene *scene)
{
	char	**file;

	file = load_file(path);
	if (!file)
		return (0);
	if (!parse_content(file, scene))
	{
		free_scene(scene);
		free_char_tab(file);
		return (0);
	}
	free_char_tab(file);
	return (1);
}
