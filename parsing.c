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

	filecontent = ft_calloc(sizeof(char *), 1);
	if (!filecontent)
		return (NULL);
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

int	get_identifier(char *line)
{
	static const char	*id[TEX_COUNT + 2] = {"NO", "SO", "WE", "EA", "F", "C"};
	int					indice;

	indice = 0;
	line = line + skip_spaces(line);
	while (indice < TEX_COUNT + 2)
	{
		if (!ft_strncmp(line, id[indice], ft_strlen(id[indice])))
			if (line[ft_strlen(id[indice])] == ' ')
				return (indice);
		indice++;
	}
	return (-1);
}

int	parse_element(char *filecontent_line, t_scene *scene)
{
	int	i;
}

int	parse_header(char **filecontent, t_scene *scene)
{
	int	i;

	i = 0;
	while (filecontent[i])
	{
		if (!is_empty(filecontent[i]))
		{
			if (all_found(scene))
				return (i);
			if (!parse_element(filecontent[i], scene))
				return (-1);
		}
		i++;
	}
	if (all_found(scene))
		print_error("missing map");
	else
		print_error("missing element in header");
	return (-1);
}
