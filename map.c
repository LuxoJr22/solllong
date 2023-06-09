/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboyer <mboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 16:31:10 by mboyer            #+#    #+#             */
/*   Updated: 2023/06/09 11:00:35 by mboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

int	check_finishable(int **cmap, int x, int y, int is_end)
{
	if (cmap[y][x] == 'P' - 48)
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
			is_end = check_finishable(cmap, x, y, is_end);
			x ++;
		}
		y ++;
	}
	return (fill_map(cmap, is_end, row, col));
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
