#include "cub3d.h"

void	move_player(t_player *player)
{
	if (player->keys.w)
		player->position.y -= MOVESPEED;
	if (player->keys.s)
		player->position.y += MOVESPEED;
	if (player->keys.a)
		player->position.x -= MOVESPEED;
	if (player->keys.d)
		player->position.x += MOVESPEED;
}