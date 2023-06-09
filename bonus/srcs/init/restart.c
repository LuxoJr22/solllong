/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restart.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboyer <mboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 15:56:01 by mboyer            #+#    #+#             */
/*   Updated: 2023/06/08 16:43:29 by mboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	restart_game(t_game *game)
{
	game->nbc = 0;
	game->player->coin = 0;
	game->player->cur = 0;
	game->nb_enemies = 0;
	game->is_win = 0;
	game->frame = 0;
	game->select = 0;
	game->sprites->trapdoor = get_anim(game, "sprite/trapdoor/tile", 6, 0);
	game->player->anims[6] = get_anim(game, "sprite/isaac/death/tile", 4, 0);
	game->player->anims[7] = get_anim(game, "sprite/isaac/end/tile", 4, 0);
	game->sprites->penny = get_anim(game, "sprite/penny/tile", 6, 1);
	free(game->enemies);
	game->player->cine = 0;
	reset_tears(game, 1);
}

void	restart_map(t_game *game)
{
	t_pos	size;

	size.x = 1088;
	size.y = 704;
	if ((game->map.col + 1) * 64 > size.x)
		size.x = (game->map.col + 1) * 64;
	if (game->map.row * 64 > size.y)
		size.y = game->map.row * 64;
	game->offset.x = (size.x - (game->map.col + 1) * 64) / 2;
	game->offset.y = (size.y - (game->map.row * 64)) / 2;
	if (game->maps[game->act_pos.y][game->act_pos.x].is_end == 1)
		game->nb_enemies = 0;
	game->enemies = malloc(sizeof(t_enemy) * game->nb_enemies + 1);
	game = get_elem(game);
}

t_game	*restart(t_game *game, char *map, int complete)
{
	t_pos	player;

	restart_game(game);
	if (complete == 1)
		game->player->nbmv = 0;
	else
	{
		player.x = game->player->px;
		player.y = game->player->py;
		if (player.x <= 0)
			player.x = 12;
		else if (player.x >= 12)
			player.x = 0;
		if (player.y <= 0)
			player.y = 6;
		else if (player.y >= 6)
			player.y = 0;
	}
	get_map(map, game);
	restart_map(game);
	game->sprites->door = getd_anims(game);
	game->player->py = player.y;
	game->player->px = player.x;
	game = init_pos(game);
	return (game);
}
