/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboyer <mboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:37:46 by mboyer            #+#    #+#             */
/*   Updated: 2023/06/09 17:23:51 by mboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_game	*init_player(t_game *game)
{
	int	imgh;
	int	imgw;

	game->player = malloc(sizeof(t_player));
	game->player->anims = malloc(sizeof(t_anim) * 10);
	game->player->head = malloc(sizeof(t_head));
	game->player->anims[0] = get_anim(game, "sprite/isaac/idle/tile", 1, 0);
	game->player->anims[1] = get_anim(game, "sprite/isaac/thumb/tile", 1, 0);
	game->player->anims[2] = get_anim(game, "sprite/isaac/up/tile", 10, 1);
	game->player->anims[3] = get_anim(game, "sprite/isaac/left/tile", 10, 1);
	game->player->anims[4] = get_anim(game, "sprite/isaac/right/tile", 10, 1);
	game->player->anims[5] = get_anim(game, "sprite/isaac/down/tile", 10, 1);
	game->player->head->up = mlx_xpm_file_to_image(game->mlx,
			"sprite/isaac/head/up.xpm", &imgw, &imgh);
	game->player->head->down = mlx_xpm_file_to_image(game->mlx,
			"sprite/isaac/head/down.xpm", &imgw, &imgh);
	game->player->head->left = mlx_xpm_file_to_image(game->mlx,
			"sprite/isaac/head/left.xpm", &imgw, &imgh);
	game->player->head->right = mlx_xpm_file_to_image(game->mlx,
			"sprite/isaac/head/right.xpm", &imgw, &imgh);
	game->player->score = 0;
	game->player->nbmv = 0;
	game->player->cur = 0;
	return (game);
}

t_game	*init_pos(t_game *game)
{
	int	i_e;

	i_e = 0;
	while (i_e < game->nb_enemies)
	{
		game->enemies[i_e]->cy = game->enemies[i_e]->py * 64 + 64;
		game->enemies[i_e]->cx = game->enemies[i_e]->px * 64 + 64;
		game->enemies[i_e]->gy = game->enemies[i_e]->py * 64 + 64;
		game->enemies[i_e]->gx = game->enemies[i_e]->px * 64 + 64;
		i_e ++;
	}
	game->player->cy = game->player->py * 64 + 44;
	game->player->cx = game->player->px * 64 + 64;
	game->player->gy = game->player->py * 64 + 44;
	game->player->gx = game->player->px * 64 + 64;
	return (game);
}

void	init_game(t_game *game, char **argv)
{
	game->mlx = mlx_init();
	game->nbc = 0;
	game = init_player(game);
	game->nb_enemies = 0;
	game->is_win = 0;
	game->frame = 0;
	game->realf = 0;
	game->scene = 0;
	game = get_map(argv[1], game);
	game->enemies = malloc(sizeof(t_enemy) * game->nb_enemies + 1);
	game = get_elem(game);
	game = init_pos(game);
	game->length = (game->map.col + 1) * 64;
	game->heigth = game->map.row * 64;
	game->mlx_win = mlx_new_window(game->mlx,
			game->length, game->heigth, "So Long");
	game->sprites = get_sprites(game);
}

t_map	ft_malloc_map(int **map, int fd, char buf[2])
{
	int		col;
	int		row;
	int		ret;
	int		i;

	col = 0;
	row = 0;
	i = -1;
	ret = read(fd, buf, 1);
	while (ret && buf[0] != '\n')
	{
		ret = read(fd, buf, 1);
		col ++;
	}
	while (ret)
	{
		ret = read(fd, buf, 1);
		if (buf[0] == '\n')
			row ++;
	}
	if (buf[0] != '\n')
		row += 2;
	return (allocate_map(row, col, i));
}
