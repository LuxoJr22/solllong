/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboyer <mboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 12:47:49 by mboyer            #+#    #+#             */
/*   Updated: 2023/06/08 16:47:11 by mboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	input(int keycode, t_game *game)
{
	if (game->player->cine == 0)
	{
		if (keycode == 13)
			game->player->diry = -1;
		if (keycode == 0)
			game->player->dirx = -1;
		if (keycode == 1)
			game->player->diry = 1;
		if (keycode == 2)
			game->player->dirx = 1;
		if (keycode == 126)
			game->tears->dir = 1;
		if (keycode == 124)
			game->tears->dir = 2;
		if (keycode == 125)
			game->tears->dir = 3;
		if (keycode == 123)
			game->tears->dir = 4;
	}
	else
	{
		game->player->dirx = 0;
		game->player->diry = 0;
	}
	return (0);
}

int	relinput(int keycode, t_game *game)
{
	if (keycode == 13 && game->player->diry == -1)
		game->player->diry = 0;
	if (keycode == 0 && game->player->dirx == -1)
		game->player->dirx = 0;
	if (keycode == 1 && game->player->diry == 1)
		game->player->diry = 0;
	if (keycode == 2 && game->player->dirx == 1)
		game->player->dirx = 0;
	if (keycode == 126 && game->tears->dir == 1)
		game->tears->dir = 0;
	if (keycode == 124 && game->tears->dir == 2)
		game->tears->dir = 0;
	if (keycode == 125 && game->tears->dir == 3)
		game->tears->dir = 0;
	if (keycode == 123 && game->tears->dir == 4)
		game->tears->dir = 0;
	return (0);
}

int	menu_select(int keycode, t_game *game)
{
	if (keycode == 36)
	{
		if (game->select == 0)
			game->scene = 1;
		if (game->select == 3)
			exit (1);
		if (game->select == 2)
			game->scene = 5;
		if (game->select == 1)
			game->scene = 4;
	}
	if (keycode == 125 && game->select < 3)
		game->select ++;
	if (keycode == 126 && game->select > 0)
		game->select --;
	return (1);
}

int	key_manager(int keycode, t_game *game)
{
	input(keycode, game);
	if (keycode == 53)
		exit(0);
	if (game->scene == 0)
		menu_select(keycode, game);
	if ((game->scene == 2 || game->scene == 3)
		&& (keycode == 49 || keycode == 36))
	{
		game = restart(game, game->map_name, 1);
		if (keycode == 49)
			game->scene = 0;
		if (keycode == 36)
			game->scene = 1;
	}
	if (game->scene == 4 || game->scene == 5)
	{
		if (keycode == 49)
			game->scene = 0;
	}
	return (1);
}
