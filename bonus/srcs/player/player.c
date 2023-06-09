/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboyer <mboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 14:05:52 by mboyer            #+#    #+#             */
/*   Updated: 2023/06/08 16:56:06 by mboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	slide(t_game *game)
{
	int		y;
	int		x;
	t_pos	max;
	t_pos	min;

	y = game->player->py + 1;
	x = game->player->px + 1;
	max.x = (game->player->cx + 20) / 64;
	max.y = (game->player->cy + 10) / 64;
	min.x = (game->player->cx - 20) / 64;
	min.y = (game->player->cy - 20) / 64;
	if (game->map.map[y + game->player->adiry][x + game->player->adirx] != 1)
	{
		change_pos(game, game->player->adirx, game->player->adiry, 0);
		game->player->is_moving --;
	}
}

t_game	*change_pos(t_game *game, int x, int y, int cur)
{
	t_pos	o;

	o = game->offset;
	if (game->player->dirx != 0 || game->player->diry != 0)
	{
		game->player->is_moving = 3;
		game->player->adirx = x;
		game->player->adiry = y;
	}
	game->player->cx += x * 5;
	game->player->cy += y * 5;
	game->player->py = (game->player->cy) / 64 - 1;
	game->player->px = (game->player->cx) / 64 - 1;
	if (game->player->invicibility == 0 || game->player->invicibility > 20)
		game->player->cur = cur;
	return (game);
}

void	player_hit(t_game *game)
{
	if (game->player->invicibility == 0)
	{
		game->player->cur = 8;
		game->player->health --;
		if (game->player->health == 0)
			game->player->cine = 1;
		game->player->invicibility = 1;
	}
}

int	is_moveable(t_game *game, int y, int x)
{
	if (game->map.map[y][x] == 1 || (game->map.map[y][x] == 20
		&& game->nb_enemies != 0))
		return (0);
	return (1);
}

int	move(t_game *game, int diry, int dirx)
{
	int		y;
	int		x;
	t_pos	max;
	t_pos	min;

	y = game->player->py + 1;
	x = game->player->px + 1;
	max.x = (game->player->cx + 20) / 64;
	max.y = (game->player->cy + 10) / 64;
	min.x = (game->player->cx - 20) / 64;
	min.y = (game->player->cy - 20) / 64;
	if (diry == -1 && (is_moveable(game, y - 1, x) || min.y != y - 1))
		game = change_pos(game, 0, -1, 2);
	if (diry == 1 && (is_moveable(game, y + 1, x) || max.y != y + 1))
		game = change_pos(game, 0, 1, 5);
	y = (game->player->cy) / 64;
	x = (game->player->cx) / 64;
	if (dirx == -1 && (game->map.map[y][x - 1] != 1 || min.x != x - 1))
		game = change_pos(game, -1, 0, 4);
	if (dirx == 1 && (game->map.map[y][x + 1] != 1 || max.x != x + 1))
		game = change_pos(game, 1, 0, 3);
	if (game->player->px + 1 != x || game->player->py + 1 != y)
		game->player->nbmv ++;
	return (1);
}
