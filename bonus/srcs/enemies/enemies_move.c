/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies_move.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboyer <mboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 15:11:49 by mboyer            #+#    #+#             */
/*   Updated: 2023/06/08 16:08:36 by mboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	gaper_movement(t_game *game, int i, int py, int px)
{
	if (game->enemies[i]->cy == game->enemies[i]->py * 64 + 64
		&& game->enemies[i]->cx == game->enemies[i]->px * 64)
	{
		game->enemies[i]->cur = 1;
		if (game->enemies[i]->py < game->player->py
			&& game->map.map[py + 2][px] != 1)
			game->enemies[i]->py ++;
		else if (game->enemies[i]->py > game->player->py
			&& game->map.map[py][px] != 1)
			game->enemies[i]->py --;
	}
	if (game->enemies[i]->cx == game->enemies[i]->px * 64
		&& game->enemies[i]->cy == game->enemies[i]->py * 64 + 64)
	{
		game->enemies[i]->cur = 1;
		if (game->enemies[i]->px < game->player->px + 1
			&& game->map.map[py + 1][px + 1] != 1)
			game->enemies[i]->px ++;
		else if (game->enemies[i]->px > game->player->px + 1
			&& game->map.map[py + 1][px - 1] != 1)
			game->enemies[i]->px --;
	}
}

void	move_gaper(t_game *game, int i)
{
	int	px;
	int	py;

	py = game->enemies[i]->py;
	px = game->enemies[i]->px;
	gaper_movement(game, i, py, px);
}

void	move_h(t_game *game, int posx, int posy, int i)
{
	if (!(game->map.map[posy + 1][posx - 1] == 1
		&& game->map.map[posy + 1][posx + 1] == 1))
	{
		if (game->map.map[posy + 1][posx + game->enemies[i]->dir]
			== 1)
			game->enemies[i]->dir *= -1;
			game->enemies[i]->px += game->enemies[i]->dir;
			game->enemies[i]->cur = 1;
		if (game->enemies[i]->dir == -1)
			game->enemies[i]->cur = 0;
	}
}

void	move_v(t_game *game, int posx, int posy, int i)
{
	if (!(game->map.map[posy + 2][posx] == 1
		&& game->map.map[posy][posx] == 1))
	{
		if (game->map.map[posy + 1 + game->enemies[i]->dir][posx]
			== 1)
			game->enemies[i]->dir *= -1;
			game->enemies[i]->py += game->enemies[i]->dir;
			game->enemies[i]->cur = 2;
		if (game->enemies[i]->dir == -1)
			game->enemies[i]->cur = 3;
	}
}

t_game	*enemies_move(t_game *game)
{
	int	i;
	int	posx;
	int	posy;

	i = 0;
	while (i < game->nb_enemies)
	{
		posx = game->enemies[i]->px;
		posy = game->enemies[i]->py;
		if ((game->enemies[i]->type == 'H' || game->enemies[i]->type == 'V')
			&& game->frame == 1)
		{
			if (game->enemies[i]->sens == 1)
				move_h(game, posx, posy, i);
			if (game->enemies[i]->sens == 2)
				move_v(game, posx, posy, i);
		}
		if (game->enemies[i]->type == 'G')
			move_gaper(game, i);
		i ++;
	}
	return (game);
}
