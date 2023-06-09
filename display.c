/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboyer <mboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:43:23 by mboyer            #+#    #+#             */
/*   Updated: 2023/06/09 12:07:52 by mboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

void	**get_number(t_game *game, char *folder)
{
	int		i;
	void	**imgs;

	i = 0;
	imgs = malloc(sizeof(void *) * 10);
	while (i < 10)
	{
		imgs[i] = get_img(game,
				ft_strjoin(ft_strjoin(folder, ft_itoa(i)), ".xpm"));
		i++;
	}
	return (imgs);
}

void	fill_back(t_game *game, int x, int y)
{
	if (y == 0 && x == 0)
		put_img(game, game->sprites->wallc, x * 64, y * 64);
	else if (y == 0 && x == game->map.col)
		put_img(game, game->sprites->wallcbr, x * 64, y * 64);
	else if (y == game->map.row - 1 && x == 0)
		put_img(game, game->sprites->wallctl, x * 64, y * 64);
	else if (y == game->map.row - 1 && x == game->map.col)
		put_img(game, game->sprites->wallcbl, x * 64, y * 64);
	else if (y == 0)
		put_img(game, game->sprites->wall, x * 64, y * 64);
	else if (x == 0)
		put_img(game, game->sprites->wall1, x * 64, y * 64);
	else if (x == game->map.col)
		put_img(game, game->sprites->wallr, x * 64, y * 64);
	else if (y == game->map.row - 1)
		put_img(game, game->sprites->wallb, x * 64, y * 64);
	else
		put_img(game, game->sprites->rock, x * 64, y * 64);
}

void	fill_ground(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x <= game->map.col)
	{
		while (y < game->map.row)
		{
			if (game->map.map[y][x] == 1)
				fill_back(game, x, y);
			else
				put_img(game, game->sprites->ground, x * 64, y * 64);
			if (game->map.map[y][x] == 'E' - 48)
				put_img(game, game->sprites->trapdoor->img,
					(x * 64) - 20, (y * 64) - 20);
			if (game->map.map[y][x] == 'C' - 48)
				put_img(game, game->sprites->penny->img,
					x * 64 + 16, y * 64 + 20);
			y += 1;
		}
		x += 1;
		y = 0;
	}
}

void	display_player(t_game *game)
{
	int	offset;

	offset = 0;
	if (game->player->cur >= 2 && game->player->cur <= 5)
		offset = 16;
	put_img(game, game->player->anims[game->player->cur]->img,
		game->player->cx, game->player->cy + offset);
	if (game->player->cur == 2)
		put_img(game, game->player->head->up,
			game->player->cx, game->player->cy - 5);
	if (game->player->cur == 4)
		put_img(game, game->player->head->left,
			game->player->cx, game->player->cy - 5);
	if (game->player->cur == 3)
		put_img(game, game->player->head->right,
			game->player->cx, game->player->cy - 5);
	if (game->player->cur == 5)
		put_img(game, game->player->head->down,
			game->player->cx, game->player->cy - 5);
}
