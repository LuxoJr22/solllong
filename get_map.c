/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboyer <mboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:45:23 by mboyer            #+#    #+#             */
/*   Updated: 2023/06/09 17:21:50 by mboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_map	allocate_map(int row, int col, int i)
{
	t_map	ret;
	int		**map;

	map = malloc(sizeof(int *) * row);
	while (i++ < row)
		map[i] = malloc(sizeof(int) * col);
	ret.map = map;
	ret.col = col;
	ret.row = row;
	return (ret);
}

void	check_elem(t_game *game, char buf[2], int ret, int fd)
{
	while (ret && buf[0] != '\n')
	{
		if (buf[0] == 'P')
		{
			game->player->py = game->map.row - 1;
			game->player->px = game->map.col;
		}
		if (buf[0] == 'C')
			game->nbc ++;
		if (buf[0] == 'M')
			game->nb_enemies ++;
		game->map.col ++;
		if (buf[0] == 'P' || buf[0] == 'C' || buf[0] == 'M'
			|| buf[0] == '0' || buf[0] == '1' || buf[0] == 'E')
			game->map.map[game->map.row][game->map.col] = buf[0] - 48;
		else
		{
			write(2, "Error\nWrong character in map\n", 29);
			exit (1);
		}
		ret = read(fd, buf, 1);
	}
}

void	get_place(t_game *game, int fd, t_map map, char buf[2])
{
	int	ret;
	int	row;
	int	col;

	ret = read(fd, buf, 1);
	col = map.col;
	row = map.row;
	map.row = 0;
	game->map = map;
	while (ret)
	{
		game->map.col = -1;
		check_elem(game, buf, ret, fd);
		if (game->map.col != col - 1)
		{
			write(2, "Error\nMap is not a rectangle\n", 29);
			exit (1);
		}
		ret = read(fd, buf, 1);
		game->map.row ++;
	}
}

t_game	*get_map(char *file, t_game *game)
{
	int		fd;
	char	buf[2];
	int		ret;
	t_map	map;

	map = game->map;
	map.row = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		write(2, "Error\nWrong file name\n", 22);
		exit(0);
	}
	map = ft_malloc_map(map.map, fd, buf);
	close(fd);
	fd = open(file, O_RDONLY);
	get_place(game, fd, map, buf);
	close(fd);
	check_map(map);
	return (game);
}

t_game	*get_elem(t_game *game)
{
	int	x;
	int	y;
	int	i_m;

	y = 0;
	i_m = 0;
	while (y < game->map.row)
	{
		x = 0;
		while (x < game->map.col)
		{
			if (game->map.map[y][x] == 'M' - 48)
			{
				game->enemies[i_m] = malloc(sizeof(t_enemy));
				game->enemies[i_m]->py = y - 1;
				game->enemies[i_m]->px = x;
				i_m ++;
			}
			x ++;
		}
		y ++;
	}
	return (game);
}
