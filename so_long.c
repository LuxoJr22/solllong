/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboyer <mboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 14:04:37 by mboyer            #+#    #+#             */
/*   Updated: 2023/06/09 13:50:37 by mboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	game_adv(t_game *game, int cpx, int cpy)
{
	game->sprites = anim(game->sprites, game);
	if (game->frame == 60)
		game->frame = 0;
	if (game->map.map[cpy][cpx] == 'C' - 48)
	{
		game->player->score ++;
		game->map.map[cpy][cpx] = 0;
	}
	if (game->map.map[cpy][cpx] == 'E' - 48 && game->is_win)
		game->scene = 2;
	if (game->nbc == game->player->score)
		game->is_win = 1;
}

int	fill(t_game *game)
{
	int		cpy;
	int		cpx;
	t_pos	pos;

	fill_ground(game);
	pos.x = game->length / 2;
	pos.y = 10;
	display_numbers(game, game->player->nbmv, game->sprites->numbers, pos);
	game->player->cx = approach(game->player->cx, game->player->gx, 5);
	game->player->cy = approach(game->player->cy, game->player->gy, 5);
	if (game->player->cy == game->player->gy
		&& game->player->cx == game->player->gx)
	{
		game->player->cur = 0;
		if (game->is_win == 1)
			game->player->cur = 1;
	}
	game->frame ++;
	cpx = (game->player->cx) / 64;
	cpy = (game->player->cy + 20) / 64;
	game_adv(game, cpx, cpy);
	display_player(game);
	return (1);
}

t_game	*change_pos(t_game *game, int x, int y, int cur)
{
	game->player->gx += x * 64;
	game->player->gy += y * 64;
	game->player->py += y;
	game->player->px += x;
	game->player->cur = cur;
	return (game);
}

int	move(int keycode, t_game *game)
{
	int	y;
	int	x;

	y = game->player->py + 1;
	x = game->player->px + 1;
	if (keycode == 53)
		exit(1);
	if (keycode == 36)
		game->scene = 1;
	if (keycode == 13 && game->player->gy > 0
		&& game->map.map[y - 1][x] != 1)
		game = change_pos(game, 0, -1, 2);
	if (keycode == 0 && game->player->gx > 24
		&& game->map.map[y][x - 1] != 1)
		game = change_pos(game, -1, 0, 4);
	if (keycode == 1 && game->player->gy < (game->map.row - 2) * 64
		&& game->map.map[y + 1][x] != 1)
		game = change_pos(game, 0, 1, 5);
	if (keycode == 2 && game->player->gx < (game->map.col - 1) * 64
		&& game->map.map[y][x + 1] != 1)
		game = change_pos(game, 1, 0, 3);
	if (game->player->px + 1 != x || game->player->py + 1 != y)
		game->player->nbmv ++;
	return (1);
}

int	main(int argc, char **argv)
{
	t_game	*game;
	void	*params;

	if (argc != 2)
	{
		write(2, "Error\n", 6);
		return (1);
	}
	game = malloc(sizeof(t_game));
	init_game(game, argv);
	mlx_hook(game->mlx_win, 2, 0L, move, game);
	mlx_hook(game->mlx_win, 17, (1L << 0), exit_game, game);
	mlx_loop_hook(game->mlx, scene_manager, game);
	mlx_loop(game->mlx);
}
