# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mboyer <mboyer@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/09 12:18:13 by mboyer            #+#    #+#              #
#    Updated: 2023/06/09 17:27:58 by mboyer           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRCS = display.c get_map.c init.c lib.c map.c scene_manager.c so_long.c sprites.c \
		sub.c
SRCS_BONUS = bonus/srcs/so_long.c bonus/srcs/map/map.c bonus/srcs/map/map2.c\
		bonus/srcs/display/sprites.c bonus/srcs/sub.c bonus/srcs/display/display.c\
		bonus/srcs/key_manager.c bonus/srcs/player/player.c bonus/srcs/enemies/enemies.c\
		bonus/srcs/scene_manager.c bonus/srcs/player/tears.c bonus/srcs/display/lanims.c\
		bonus/srcs/display/door.c bonus/srcs/player/life.c bonus/srcs/pickups.c\
		bonus/srcs/scene.c bonus/srcs/display/display_ui.c bonus/srcs/init/init.c\
		bonus/srcs/display/get_sprites.c bonus/srcs/lib.c bonus/srcs/map/map_fill.c\
		bonus/srcs/enemies/enemies_move.c bonus/srcs/init/init_player.c bonus/srcs/init/restart.c

OBJS = ${SRCS:.c=.o}

OBJS_BONUS = ${SRCS_BONUS:.c=.o}

NAME = so_long

.c.o:
	gcc -I/usr/include -Imlx_linux -O3 -c $< -o ${<:.c=.o}


${NAME}: ${OBJS}
	gcc ${OBJS} -L /usr/local/lib/ -lmlx -framework OpenGL -framework AppKit -o ${NAME}



all:	${NAME}

clean:
	rm -f ${OBJS}

fclean:	clean
	rm -f ${NAME}

re:	fclean all
