/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboyer <mboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 16:31:10 by mboyer            #+#    #+#             */
/*   Updated: 2023/06/08 16:43:37 by mboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	**ft_malloc_map(int **map, int fd, char buf[2])
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
	map = malloc(sizeof(int *) * row);
	while (i++ < row)
		map[i] = malloc(sizeof(int) * col);
	return (map);
}

void	is_map(int **cmap, int row, int col)
{
	int	x;
	int	y;

	y = 0;
	while (y < row)
	{
		x = 0;
		while (x < col)
		{
			if (cmap[y][x] == 'E' - 48 || cmap[y][x] == 'C' - 48)
			{
				write(2, "Error\n", 6);
				exit (1);
			}
			x ++;
		}
		y ++;
	}
}

void	check_map(t_map map)
{
	int	**cmap;

	cmap = clone_map(map);
	cmap = fill_map(cmap, 1, map.row, map.col);
	is_map(cmap, map.row, map.col);
}

void	change_room(t_game *game)
{
	if (game->map.map[game->player->py + 1][game->player->px + 1] == 'D' - 48
		&& game->nb_enemies == 0)
	{
		if (game->player->py == 7)
			restart(game, choose_map(game, 0, 1), 0);
		else if (game->player->py == -1)
			restart(game, choose_map(game, 0, -1), 0);
		else if (game->player->px == 13)
			restart(game, choose_map(game, 1, 0), 0);
		else if (game->player->px == -1)
			restart(game, choose_map(game, -1, 0), 0);
	}
}
