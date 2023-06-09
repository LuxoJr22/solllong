/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboyer <mboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 12:10:04 by mboyer            #+#    #+#             */
/*   Updated: 2023/06/09 11:03:12 by mboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	*get_img(t_game *game, char *file)
{
	int	imgw;
	int	imgh;

	return (mlx_xpm_file_to_image(game->mlx, file, &imgw, &imgh));
}

void	put_img(t_game *game, void *img, int x, int y)
{
	mlx_put_image_to_window(game->mlx, game->mlx_win, img, x, y);
}

int	approach(int current, int goal, int delta)
{
	int	sign;

	sign = 1;
	if (current - goal > 0)
		sign = -1;
	if (current != goal)
	{
		if ((goal - current) * sign < delta)
			return (goal);
		return (current + (delta * sign));
	}
	else
		return (goal);
}

int	exit_game(t_game *game)
{
	exit (1);
	return (1);
}
