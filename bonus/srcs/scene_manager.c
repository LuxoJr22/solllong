/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboyer <mboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 16:46:37 by mboyer            #+#    #+#             */
/*   Updated: 2023/06/08 15:05:44 by mboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	handle_cine(t_game *game, int cur)
{
	if ((game->player->cur != 6 && game->player->cur != 7) || game->frame == 60)
		game->frame = 0;
	game->player->cur = 7;
	if (game->player->cine == 1)
		game->player->cur = 6;
	cur = game->player->cur;
	if (game->frame == 59)
	{
		if (game->player->cine == 1)
			game->scene = 3;
		if (game->player->cine == 2)
			game->scene = 2;
	}
	return (cur);
}

void	cine_player(t_game *game, int cur, t_pos o, int y)
{
	if (cur == 6)
		put_img(game, game->player->anims[cur]->img,
			game->player->cx + o.x, game->player->cy + o.y + y);
	else
		put_img(game, game->player->anims[cur]->img,
			game->player->px * 64 + 56 + o.x, game->player->py * 64 + o.y);
	if (game->frame % 8 == 0 && game->player->anims[cur]->next)
		game->player->anims[cur] = game->player->anims[cur]->next;
}

void	cine(t_game *game)
{
	int		i;
	t_pos	o;
	int		y;
	int		cur;

	y = 0;
	i = 0;
	o = game->offset;
	cur = handle_cine(game, cur);
	display_game(game);
	while (i < game->nb_enemies)
	{
		put_img(game, game->enemies[i]->anims[game->enemies[i]->cur]->img,
			game->enemies[i]->cx + o.x, game->enemies[i]->cy + o.y);
		i ++;
	}
	if (!game->player->anims[cur]->next && cur == 6)
		y = 10;
	o.y -= 64;
	o.x -= 32;
	cine_player(game, cur, o, y);
	game->frame ++;
}

void	options(t_game *game)
{
	display_finish(game);
	mlx_put_image_to_window(game->mlx, game->mlx_win,
		game->sprites->menu->optionsmenu, 340, 100);
}

int	scene_manager(t_game *game)
{
	if (game->realf == 100)
	{
		if (game->scene == 1)
			move(game, game->player->diry, game->player->dirx);
		if (game->scene == 1 && !game->player->cine)
			fill(game);
		else if (game->scene == 1)
			cine(game);
		if (game->scene == 0)
			menu(game);
		if (game->scene == 2)
			finish(game);
		if (game->scene == 3)
			death(game);
		if (game->scene == 4)
			select_map(game);
		if (game->scene == 5)
			options(game);
		game->realf = 0;
	}
	game->realf ++;
	return (1);
}
