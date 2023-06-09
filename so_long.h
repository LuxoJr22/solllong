/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboyer <mboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 14:05:19 by mboyer            #+#    #+#             */
/*   Updated: 2023/06/09 17:21:21 by mboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <mlx.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include <unistd.h>

typedef struct s_anim {
	void			*img;
	struct s_anim	*next;
}				t_anim;

typedef struct s_head {
	void	*up;
	void	*down;
	void	*left;
	void	*right;
}		t_head;

typedef struct s_enemy {
	t_anim	**anims;
	int		gy;
	int		gx;
	int		px;
	int		py;
	int		cy;
	int		cx;
}		t_enemy;

typedef struct s_pos {
	int	x;
	int	y;
}				t_pos;

typedef struct s_player {
	t_anim		**anims;
	int			score;
	int			nbmv;
	int			cy;
	int			cx;
	int			gy;
	int			gx;
	int			px;
	int			py;
	int			cur;
	t_head		*head;
}				t_player;

typedef struct s_map {
	int	**map;
	int	row;
	int	col;
}				t_map;

typedef struct s_sprites {
	void	*ground;
	void	*menu;
	void	*wall;
	void	*wallc;
	void	*wallb;
	void	*wallr;
	void	*wall1;
	void	*wallctl;
	void	*wallcbl;
	void	*wallcbr;
	void	*rock;
	void	**numbers;
	void	*main_menu;
	t_anim	*trapdoor;
	t_anim	*penny;
	void	*win;
}				t_sprites;

typedef struct s_collec {
	int		py;
	int		px;
	int		lx;
	int		ly;
	int		is_active;
}				t_collec;

typedef struct s_game {
	int			realf;
	t_enemy		**enemies;
	int			scene;
	t_player	*player;
	t_collec	*collec;
	t_sprites	*sprites;
	int			is_win;
	int			nbc;
	void		*mlx;
	void		*mlx_win;
	int			frame;
	t_map		map;
	int			nb_enemies;
	int			length;
	int			heigth;
}			t_game;

void		**get_number(t_game *game, char *folder);
void		display_numbers(t_game *game, int nb, void **numbers, t_pos pos);
int			exit_game(t_game *game);
char		*ft_itoa(int nb);
void		menu(t_game *game);
void		finish(t_game *game);
t_game		*get_map(char *file, t_game *game);
int			scene_manager(t_game *game);
t_sprites	*get_sprites(t_game *game);
char		*ft_strjoin(char *s1, char *s2);
t_sprites	*anim(t_sprites *sprite, t_game *game);
t_anim		*get_anim(t_game *game, char *folder, int nbsprites, int is_loop);
t_game		*get_elem(t_game *game);
void		put_img(t_game *game, void *img, int x, int y);
void		*get_img(t_game *game, char *file);
t_game		*init_pos(t_game *game);
t_game		*init_player(t_game *game);
int			fill(t_game *game);
int			approach(int current, int goal, int delta);
void		fill_ground(t_game *game);
void		fill_back(t_game *game, int x, int y);
t_map		ft_malloc_map(int **map, int fd, char buf[2]);
t_map		allocate_map(int row, int col, int i);
void		check_map(t_map map);
void		display_player(t_game *game);
void		init_game(t_game *game, char **argv);

#endif
