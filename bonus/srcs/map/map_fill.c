/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_fill.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboyer <mboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 14:22:20 by mboyer            #+#    #+#             */
/*   Updated: 2023/06/08 14:42:26 by mboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	check_finishable(int **cmap, int is_end, int x, int y)
{
	if (cmap[y - 1][x] != 1 && cmap[y - 1][x] != 'P' - 48)
	{
		cmap[y - 1][x] = 'P' - 48;
		is_end = 1;
	}
	if (cmap[y][x - 1] != 1 && cmap[y][x - 1] != 'P' - 48)
	{				
		cmap[y][x - 1] = 'P' - 48;
		is_end = 1;
	}
	if (cmap[y + 1][x] != 1 && cmap[y + 1][x] != 'P' - 48)
	{				
		cmap[y + 1][x] = 'P' - 48;
		is_end = 1;
	}
	if (cmap[y][x + 1] != 1 && cmap[y][x + 1] != 'P' - 48)
	{
		cmap[y][x + 1] = 'P' - 48;
		is_end = 1;
	}
	return (is_end);
}

int	**fill_map(int **cmap, int is_end, int row, int col)
{
	int	x;
	int	y;

	if (!is_end)
		return (cmap);
	is_end = 0;
	y = 0;
	while (y < row)
	{
		x = 0;
		while (x < col)
		{
			if (cmap[y][x] == 'P' - 48)
			{
				is_end = check_finishable(cmap, is_end, x, y);
			}
			x ++;
		}
		y ++;
	}
	return (fill_map(cmap, is_end, row, col));
}

t_map	map_fill(char buf[2], int fd, int ret, t_game *game)
{
	t_map	map;

	map = game->map;
	while (ret)
	{
		map.col = -1;
		while (ret && buf[0] != '\n')
		{
			if (buf[0] == 'H' || buf[0] == 'V' || buf[0] == 'G')
				game->nb_enemies ++;
			map.col ++;
			map.map[map.row][map.col] = buf[0] - 48;
			ret = read(fd, buf, 1);
		}
		ret = read(fd, buf, 1);
		map.row ++;
	}
	return (map);
}

int	**clone_map(t_map map)
{
	int	y;
	int	x;
	int	**cmap;

	y = 0;
	cmap = malloc(sizeof(int *) * map.row);
	while (y < map.row)
	{
		x = 0;
		cmap[y] = malloc(sizeof(int) * map.col);
		while (x < map.col)
		{
			cmap[y][x] = map.map[y][x];
			x ++;
		}
		y ++;
	}
	return (cmap);
}
