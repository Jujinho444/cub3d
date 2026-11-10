#include "cub3d.h"

int	read_component(char *string, int *i, int *component)
{
	int	start;

	(*component) = 0;
	(*i) += skip_spaces(&string[*i]);
	start = (*i);
	while (ft_isdigit(string[*i]))
	{
		(*component) = (*component) * 10 + (string[*i] - '0');
		if ((*component) > 255)
			return (format_error("Color Value out of range"));
		(*i)++;
	}
	if (start == (*i))
		return (format_error("Missing Color Value"));
	(*i) += skip_spaces(&string[*i]);
	return (1);
}

int	parse_color(char *value)
{
	int	i;
	int	rgb[3];
	int	j;

	j = 0;
	i = 0;
	while (j < 3)
	{
		if (!read_component(value, &i, &rgb[j]))
			return (COLOR_UNSET);
		if ((value[i] != ',' && j != 2) || (value[i] != '\0' && j == 2))
		{
			format_error("Incorrect Color format");
			return (COLOR_UNSET);
		}
		i++;
		j++;
	}
	return (rgb[0] * 65536 + rgb[1] * 256 + rgb[2]);
}
