#include "cub3d.h"

void	init_scene(t_scene *scene)
{
	ft_bzero(scene, sizeof(t_scene));
	scene->ceiling_color = COLOR_UNSET;
	scene->floor_color = COLOR_UNSET;
}
