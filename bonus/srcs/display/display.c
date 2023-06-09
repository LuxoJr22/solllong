/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboyer <mboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 14:10:28 by mboyer            #+#    #+#             */
/*   Updated: 2023/06/08 16:56:49 by mboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	display_player(t_game *game)
{
	int		offset;
	int		cur;
	t_pos	o;

	offset = 0;
	o = game->offset;
	o.y -= 64;
	o.x -= 32;
	cur = game->player->cur;
	if (cur >= 2 && cur <= 5)
		offset = 16;
	put_img(game, game->player->anims[cur]->img, game->player->cx + o.x,
		game->player->cy + offset + o.y);
	if (game->tears->dir == 1 || (game->tears->dir == 0 && cur == 2))
		put_img(game, game->player->head->up, game->player->cx + o.x,
			game->player->cy - 5 + o.y);
	if (game->tears->dir == 4 || (game->tears->dir == 0 && cur == 4))
		put_img(game, game->player->head->left, game->player->cx + o.x,
			game->player->cy - 5 + o.y);
	if (game->tears->dir == 2 || (game->tears->dir == 0 && cur == 3))
		put_img(game, game->player->head->right, game->player->cx + o.x,
			game->player->cy - 5 + o.y);
	if (game->tears->dir == 3 || (game->tears->dir == 0 && cur == 5))
		put_img(game, game->player->head->down, game->player->cx + o.x,
			game->player->cy - 5 + o.y);
}

void	display_map(t_game *game, int x, int y, t_pos o)
{
	while (x <= game->map.col)
	{
		while (y < game->map.row)
		{
			if (game->map.map[y][x] == 1 || game->map.map[y][x] == 'D' - 48)
			{
				if (x != 0 && y != 0 && y != game->map.row - 1
					&& x != game->map.col)
					mlx_put_image_to_window(game->mlx, game->mlx_win,
						game->sprites->rock, x * 64 + o.x, y * 64 + o.y);
			}
			if (game->map.map[y][x] == 'D' - 48)
				display_door(game, y, x);
			if (game->map.map[y][x] == 'E' - 48)
				mlx_put_image_to_window(game->mlx, game->mlx_win,
					game->sprites->trapdoor->img, (x * 64) - 20 + o.x,
					(y * 64) - 20 + o.y);
		y += 1;
		}
	x += 1;
	y = 0;
	}
}

void	display_game(t_game *game)
{
	int		x;
	int		y;
	t_pos	nbpos;
	t_pos	o;

	o = game->offset;
	x = 0;
	y = 0;
	mlx_put_image_to_window(game->mlx, game->mlx_win,
		game->sprites->black, 0, 0);
	mlx_put_image_to_window(game->mlx, game->mlx_win,
		game->sprites->black, 350, 0);
	mlx_put_image_to_window(game->mlx, game->mlx_win,
		game->sprites->ground, x * 64, y * 64);
	display_map(game, x, y, o);
	mlx_put_image_to_window(game->mlx, game->mlx_win,
		game->sprites->score, 280, 0);
	display_picks(game);
	display_tears(game);
	display_lanims(game);
	display_life(game);
	nbpos.x = 410;
	nbpos.y = 10;
	display_numbers(game, game->player->nbmv, game->sprites->numbers, nbpos);
}

void	display_menu(t_game *game)
{
	t_pos	o;

	o.x = 100;
	o.y = 100;
	mlx_put_image_to_window(game->mlx, game->mlx_win,
		game->sprites->menu->ui, -100 + o.x, -50 + o.y);
	mlx_put_image_to_window(game->mlx, game->mlx_win,
		game->sprites->menu->continues, 320 + o.x, 60 + o.y);
	mlx_put_image_to_window(game->mlx, game->mlx_win,
		game->sprites->menu->challenge, 320 + o.x, 120 + o.y);
	mlx_put_image_to_window(game->mlx, game->mlx_win,
		game->sprites->menu->options, 340 + o.x, 220 + o.y);
	mlx_put_image_to_window(game->mlx, game->mlx_win,
		game->sprites->menu->select, 300 + o.x, game->select * 80 + 90 + o.y);
	mlx_put_image_to_window(game->mlx, game->mlx_win,
		game->sprites->menu->exit, 340 + o.x, 320 + o.y);
}

void	display_back(t_game *game, t_pos o)
{
	mlx_put_image_to_window(game->mlx, game->mlx_win,
		game->sprites->menu->menu, 0 + o.x, 0 + o.y);
	mlx_put_image_to_window(game->mlx, game->mlx_win,
		game->sprites->menu->menu, 480 + o.x, 0 + o.y);
	mlx_put_image_to_window(game->mlx, game->mlx_win,
		game->sprites->menu->menu, 0 + o.x, 270 + o.y);
	mlx_put_image_to_window(game->mlx, game->mlx_win,
		game->sprites->menu->menu, 480 + o.x, 270 + o.y);
}
