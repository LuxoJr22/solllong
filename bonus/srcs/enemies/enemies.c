/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboyer <mboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 12:47:30 by mboyer            #+#    #+#             */
/*   Updated: 2023/06/08 16:14:01 by mboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	delete_enemies(t_game *game, int enemies, t_pos pos, int act_tab)
{
	int		i;
	t_enemy	**tab;

	tab = malloc(sizeof(t_enemy) * enemies);
	i = 0;
	while (i < game->nb_enemies)
	{
		if (game->enemies[i]->is_dead)
		{
			pos.x = game->enemies[i]->cx;
			pos.y = game->enemies[i]->cy;
			create_lanims(game, get_anim(game,
					"sprite/death/tile", 10, 0), pos, 1);
			free(game->enemies[i]);
		}
		else
		{
			tab[act_tab] = game->enemies[i];
			act_tab ++;
		}
		i ++;
	}
	game->nb_enemies = enemies;
	game->enemies = tab;
}

void	check_enemies(t_game *game)
{
	int		i;
	int		enemies;
	int		act_tab;
	t_enemy	**tab;
	t_pos	pos;

	i = 0;
	enemies = 0;
	act_tab = 0;
	while (i < game->nb_enemies)
	{
		if (game->enemies[i]->is_dead == 0)
			enemies ++;
		i ++;
	}
	if (enemies != game->nb_enemies)
	{
		delete_enemies(game, enemies, pos, act_tab);
	}
}

t_anim	**getg_anims(t_game *game)
{
	t_anim	**ret;

	ret = malloc(sizeof(t_anim) * 5);
	ret[0] = malloc(sizeof(t_anim));
	ret[0] = get_anim(game, "sprite/gaper/left/tile", 4, 1);
	ret[1] = malloc(sizeof(t_anim));
	ret[1] = get_anim(game, "sprite/gaper/right/tile", 4, 1);
	ret[2] = malloc(sizeof(t_anim));
	ret[2] = get_anim(game, "sprite/gaper/down/tile", 4, 1);
	ret[3] = malloc(sizeof(t_anim));
	ret[3] = get_anim(game, "sprite/gaper/up/tile", 4, 1);
	ret[4] = malloc(sizeof(t_anim));
	ret[4] = get_anim(game, "sprite/gaper/head/tile", 1, 0);
	return (ret);
}

void	move_enemies(t_game *game, int cpx, int cpy)
{
	int		i;
	t_pos	o;

	i = 0;
	o = game->offset;
	while (i < game->nb_enemies)
	{
		if (game->enemies[i]->px == cpx && game->enemies[i]->py == cpy - 1)
			player_hit(game);
		game->enemies[i]->cx = approach(game->enemies[i]->cx,
				game->enemies[i]->px * 64, 2);
		game->enemies[i]->cy = approach(game->enemies[i]->cy,
				game->enemies[i]->py * 64 + 64, 2);
		put_img(game, game->enemies[i]->anims[game->enemies[i]->cur]->img,
			game->enemies[i]->cx + o.x, game->enemies[i]->cy - 5 + o.y);
		if (game->enemies[i]->type == 'G')
			put_img(game, game->enemies[i]->anims[4]->img,
				game->enemies[i]->cx + o.x, game->enemies[i]->cy + o.y);
		i ++;
	}
}
