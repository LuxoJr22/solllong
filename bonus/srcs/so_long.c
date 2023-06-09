/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboyer <mboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 14:04:37 by mboyer            #+#    #+#             */
/*   Updated: 2023/06/08 16:43:09 by mboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	game_act(t_game *game)
{
	if (game->player->dirx == 0 && game->player->diry == 0
		&& game->player->cur != 6
		&& (game->player->invicibility == 0 || game->player->invicibility > 20))
		game->player->cur = 0;
	if (game->nb_enemies == 0)
		game->maps[game->act_pos.y][game->act_pos.x].is_end = 1;
	game->frame ++;
	game->sprites = anim(game->sprites, game);
	if (game->frame == 60)
		game->frame = 0;
	check_picks(game);
	if (game->player->invicibility != 0)
		game->player->invicibility ++;
	if (game->player->invicibility == 40)
		game->player->invicibility = 0;
	if (game->map.map[game->player->py + 1][game->player->px + 1]
		== 'E' - 48 && game->is_win)
		game->player->cine = 2;
	if (game->nbc == game->player->coin)
		game->is_win = 1;
}

int	fill(t_game *game)
{
	if (game->tears->dir != 0 && game->tears->is_active == 0)
		create_tears(game, game->tears->dir);
	if (game->tears->is_active != 0)
		game->tears->is_active ++;
	if (game->tears->is_active == 5)
		game->tears->is_active = 0;
	move_tears(game);
	reset_tears(game, 0);
	reset_lanims(game, 0);
	reset_picks(game);
	display_game(game);
	game_act(game);
	move_enemies(game, game->player->px + 1, game->player->py + 1);
	check_enemies(game);
	if ((game->player->invicibility / 4) % 2 == 0)
		display_player(game);
	change_room(game);
	if (game->player->dirx == 0 && game->player->diry == 0
		&& game->player->is_moving != 0 && game->frame % 3 == 0)
		slide(game);
	return (1);
}

int	exit_game(t_game *game)
{
	exit (1);
	return (1);
}

int	main(void)
{
	t_game	*game;
	void	*params;
	t_pos	size;

	game = malloc(sizeof(t_game));
	init_game(game);
	size.x = 1088;
	size.y = 704;
	if ((game->map.col + 1) * 64 > size.x)
		size.x = (game->map.col + 1) * 64;
	if (game->map.row * 64 > size.y)
		size.y = game->map.row * 64;
	game->offset.x = (size.x - (game->map.col + 1) * 64) / 2;
	game->offset.y = (size.y - ((game->map.row) * 64)) / 2;
	game->mlx_win = mlx_new_window(game->mlx,
			size.x, size.y, "So Long");
	game->sprites = get_sprites(game);
	mlx_hook(game->mlx_win, 2, (1L << 0), key_manager, game);
	mlx_hook(game->mlx_win, 3, (1L << 1), relinput, game);
	mlx_hook(game->mlx_win, 17, (1L << 0), exit_game, game);
	mlx_loop_hook(game->mlx, scene_manager, game);
	mlx_loop(game->mlx);
}
