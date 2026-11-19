#include "cub3d.h"

void	put_pixel(t_img *image, int x, int y, int color)
{
	unsigned int	index;

	if (x >= image->width || y >= image->height || x < 0 || y < 0)
		return ;
	index = y * image->line_length + x * image->bits_per_pixel / 8;
	*(unsigned int *)(&image->data_address[index]) = color;
}