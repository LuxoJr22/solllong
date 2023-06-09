/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboyer <mboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:40:04 by mboyer            #+#    #+#             */
/*   Updated: 2023/06/09 12:09:26 by mboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	menu(t_game *game)
{
	t_pos	pos;

	pos.x = game->length / 2 - 230;
	pos.y = game->heigth / 2 - 240;
	mlx_put_image_to_window(game->mlx, game->mlx_win,
		game->sprites->menu, 0, 0);
	mlx_put_image_to_window(game->mlx, game->mlx_win,
		game->sprites->menu, 480, 0);
	mlx_put_image_to_window(game->mlx, game->mlx_win,
		game->sprites->menu, 0, 270);
	mlx_put_image_to_window(game->mlx, game->mlx_win,
		game->sprites->menu, 480, 270);
	put_img(game, game->sprites->main_menu, pos.x, pos.y);
}

void	finish(t_game *game)
{
	t_pos	pos;

	pos.x = game->length / 2 - 100;
	pos.y = game->heigth / 2 - 50;
	mlx_put_image_to_window(game->mlx, game->mlx_win,
		game->sprites->menu, 0, 0);
	mlx_put_image_to_window(game->mlx, game->mlx_win,
		game->sprites->menu, 480, 0);
	mlx_put_image_to_window(game->mlx, game->mlx_win,
		game->sprites->menu, 0, 270);
	mlx_put_image_to_window(game->mlx, game->mlx_win,
		game->sprites->menu, 480, 270);
	put_img(game, game->sprites->win, pos.x, pos.y);
}

int	scene_manager(t_game *game)
{
	if (game->realf == 1)
	{
		if (game->scene == 1)
			fill(game);
		if (game->scene == 0)
			menu(game);
		if (game->scene == 2)
			finish(game);
		game->realf = 0;
	}
	game->realf ++;
	return (1);
}
