/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboyer <mboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 15:45:02 by mboyer            #+#    #+#             */
/*   Updated: 2023/06/08 15:55:58 by mboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

t_game	*init_player(t_game *game)
{
	game->player = malloc(sizeof(t_player));
	init_player_sprites(game);
	game->player->coin = 0;
	game->player->nbmv = 0;
	game->player->cur = 0;
	game->player->cine = 0;
	game->player->dirx = 0;
	game->player->diry = 0;
	game->player->invicibility = 0;
	game->player->health = 6;
	game->player->maxhealth = 6;
	game->player->is_moving = 0;
	game->player->adirx = 0;
	game->player->adiry = 0;
	game->player->dmg = 50;
	return (game);
}
