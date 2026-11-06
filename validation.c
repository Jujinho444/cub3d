#include "cub3d.h"

int	check_extension(char *filename)
{
	int	length;

	length = ft_strlen(filename);
	if (length < 5 || ft_strncmp(filename + length - 4, ".cub", 4))
		return (0);
	if (filename[length - 5] == '/')
		return (0);
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
		perror(filename);
		return (0);
	}
	return (1);
}
