/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboyer <mboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 10:34:08 by mboyer            #+#    #+#             */
/*   Updated: 2023/06/09 12:08:55 by mboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_sprites	*anim(t_sprites *sprite, t_game *game)
{
	int	cur;

	cur = game->player->cur;
	if (game->frame % 5 == 0)
	{
		if (game->frame < 35)
			sprite->penny = sprite->penny->next;
		if (game->is_win && sprite->trapdoor->next)
			sprite->trapdoor = sprite->trapdoor->next;
		if (cur == 2 || cur == 3 || cur == 4 || cur == 5)
			game->player->anims[cur] = game->player->anims[cur]->next;
	}
	return (sprite);
}

t_anim	*get_anim(t_game *game, char *folder, int nbsprites, int is_loop)
{
	int		i;
	t_anim	*anim;
	t_anim	*first;
	t_anim	*temp;

	i = 0;
	anim = 0;
	while (i < nbsprites)
	{
		temp = malloc(sizeof(t_anim));
		if (anim)
			anim->next = temp;
		else
			first = temp;
		temp->img = get_img(game,
				ft_strjoin(ft_strjoin(folder, ft_itoa(i)), ".xpm"));
		anim = temp;
		i++;
	}
	if (is_loop)
		anim->next = first;
	else
		anim->next = 0;
	return (first);
}

t_sprites	*get_sprites(t_game *game)
{
	t_sprites	*sprite;

	sprite = malloc(sizeof(t_sprites));
	sprite->menu = get_img(game, "sprite/menu.xpm");
	sprite->ground = get_img(game, "sprite/tile012.xpm");
	sprite->wall = get_img(game, "sprite/walls/tile.xpm");
	sprite->wall1 = get_img(game, "sprite/walls/wall1.xpm");
	sprite->wallc = get_img(game, "sprite/walls/tile000.xpm");
	sprite->wallr = get_img(game, "sprite/walls/wallr.xpm");
	sprite->wallctl = get_img(game, "sprite/walls/wallctl.xpm");
	sprite->wallcbl = get_img(game, "sprite/walls/wallcbl.xpm");
	sprite->wallb = get_img(game, "sprite/walls/wallb.xpm");
	sprite->wallcbr = get_img(game, "sprite/walls/wallcbr.xpm");
	sprite->rock = get_img(game, "sprite/tile001.xpm");
	sprite->penny = get_anim(game, "sprite/penny/tile", 6, 1);
	sprite->trapdoor = get_anim(game, "sprite/trapdoor/tile", 6, 0);
	sprite->numbers = get_number(game, "sprite/number/white/");
	sprite->main_menu = get_img(game, "sprite/mainmenu.xpm");
	sprite->win = get_img(game, "sprite/win.xpm");
	return (sprite);
}
