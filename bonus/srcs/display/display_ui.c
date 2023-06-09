/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_ui.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboyer <mboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 14:22:50 by mboyer            #+#    #+#             */
/*   Updated: 2023/06/08 16:56:57 by mboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	display_numbers(t_game *game, int nb, void **numbers, t_pos pos)
{
	if (nb < 10)
		mlx_put_image_to_window(game->mlx, game->mlx_win,
			numbers[nb], pos.x, pos.y);
	else if (nb <= 99)
	{
		mlx_put_image_to_window(game->mlx, game->mlx_win,
			numbers[nb % 10], pos.x + 30, pos.y);
		mlx_put_image_to_window(game->mlx, game->mlx_win,
			numbers[nb / 10], pos.x, pos.y);
	}
	else
	{
		mlx_put_image_to_window(game->mlx, game->mlx_win,
			numbers[9], pos.x + 30, pos.y);
		mlx_put_image_to_window(game->mlx, game->mlx_win,
			numbers[9], pos.x, pos.y);
	}
}

void	display_finish(t_game *game)
{
	mlx_put_image_to_window(game->mlx, game->mlx_win,
		game->sprites->menu->menu, 0, 0);
	mlx_put_image_to_window(game->mlx, game->mlx_win,
		game->sprites->menu->menu, 480, 0);
	mlx_put_image_to_window(game->mlx, game->mlx_win,
		game->sprites->menu->menu, 960, 0);
	mlx_put_image_to_window(game->mlx, game->mlx_win,
		game->sprites->menu->menu, 0, 270);
	mlx_put_image_to_window(game->mlx, game->mlx_win,
		game->sprites->menu->menu, 480, 270);
	mlx_put_image_to_window(game->mlx, game->mlx_win,
		game->sprites->menu->menu, 960, 270);
	mlx_put_image_to_window(game->mlx, game->mlx_win,
		game->sprites->menu->menu, 0, 540);
	mlx_put_image_to_window(game->mlx, game->mlx_win,
		game->sprites->menu->menu, 480, 540);
	mlx_put_image_to_window(game->mlx, game->mlx_win,
		game->sprites->menu->menu, 960, 540);
}

void	display_death(t_game *game)
{
	t_pos	nbpos;

	mlx_put_image_to_window(game->mlx, game->mlx_win,
		game->sprites->menu->menu, 0, 0);
	mlx_put_image_to_window(game->mlx, game->mlx_win,
		game->sprites->menu->menu, 480, 0);
	mlx_put_image_to_window(game->mlx, game->mlx_win,
		game->sprites->menu->menu, 0, 270);
	mlx_put_image_to_window(game->mlx, game->mlx_win,
		game->sprites->menu->menu, 480, 270);
	mlx_put_image_to_window(game->mlx, game->mlx_win,
		game->sprites->menu->death, 150, 0);
	nbpos.x = 400;
	nbpos.y = 310;
}

void	display_select(t_game *game)
{
	int		i;
	t_pos	nbpos;
	t_pos	o;

	o.x = 150;
	o.y = 150;
	i = 0;
	display_back(game, o);
	mlx_put_image_to_window(game->mlx, game->mlx_win,
		game->sprites->menu->back_select, 100 + o.x, 50 + o.y);
	while (i < 12)
	{
		nbpos.x = 150 + (i % 4) * 130 + o.x;
		nbpos.y = 100 + (i / 4) * 80 + o.y;
		mlx_put_image_to_window(game->mlx, game->mlx_win,
			game->sprites->menu->map_text, nbpos.x, nbpos.y);
		nbpos.x += 70;
		i ++;
		display_numbers(game, i, game->sprites->numbersb, nbpos);
	}
}

//display_numbers(game, game->player->score, game->sprites->numbersb, nbpos);