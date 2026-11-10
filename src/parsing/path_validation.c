#include "cub3d.h"

int	check_extension(char *filename)
{
	int	length;

	length = ft_strlen(filename);
	if (length < 5 || ft_strncmp(filename + length - 4, ".cub", 4))
		return (format_error("Wrong filename extension"));
	if (filename[length - 5] == '/')
		return (format_error("Wrong filename extension"));
	return (1);
}

int	check_path(char *filename)
{
	int	fd;

	fd = open(filename, O_DIRECTORY | O_RDONLY);
	if (fd != -1)
	{
		close(fd);
		errno = EISDIR;
		return (system_error(filename));
	}
	return (1);
}
