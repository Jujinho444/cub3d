/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstrasse <jstrasse@student.42lausanne.ch>    +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/26 10:53:48 by jstrasse          #+#    #+#             */
/*   Updated: 2026/11/26 10:54:11 by jstrasse         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_keys(t_keys *keys, int keycode, int value)
{
	if (keycode == KEY_W)
		keys->w = value;
	else if (keycode == KEY_A)
		keys->a = value;
	else if (keycode == KEY_S)
		keys->s = value;
	else if (keycode == KEY_D)
		keys->d = value;
	else if (keycode == KEY_LEFT)
		keys->left = value;
	else if (keycode == KEY_RIGHT)
		keys->right = value;
}

int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		close_game(game);
	else
		set_keys(&game->keys, keycode, 1);
	return (0);
}

int	handle_keyrelease(int keycode, t_game *game)
{
	set_keys(&game->keys, keycode, 0);
	return (0);
}
