# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/23 17:12:18 by vkaron            #+#    #+#              #
#    Updated: 2020/07/20 19:38:30 by vkaron           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all, clean, fclean, re, libr

#FLAGS = #-Wall -Wextra -Werror -Ofast -g
FLAGS = -g

C_FILES =	main.c service_stuff.c init.c act_sdl.c key_events.c mouse_events.c\
			game_object.c map.c player.c engine.c


O_FILES =	$(C_FILES:.c=.o)

H_DIR =		-I libft -I usr/L -I include -I ./ \
            -I src/ \
#            -I Frameworks/SDL2.framework/Headers -I Frameworks/SDL2_image.framework/Headers -I Frameworks/SDL2_ttf.framework/Headers -F Frameworks/


#LIBS =		-Llibft -lft #-L/usr/lib/x86_64-linux-gnu -lm-2.31#libm.a
#-Llib -lSDL2 -lSDL2_image -lSDL2_ttf
#-dynamiclib -o lib/libSDL2.dylib -o lib/libSDL2_image.dylib

#FRAME =		-F ./Frameworks/ -framework SDL2 -framework SDL2_image\
#			-framework SDL2_ttf -rpath Frameworks/

FRAME= `sdl2-config --cflags --libs` -lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_ttf


LIBS = -Llibft -lft -lm -lpthread
# -L/usr/lib/x86_64-linux-gnu -lm -lpthread
#-Llib 
#-lSDL2 -lSDL2_image -lSDL2_ttf
#-dynamiclib -o libSDL2.dylib -o libSDL2_image.dylib

S_DIR = src

OBJ = $(addprefix $(S_DIR)/, $(O_FILES))

NAME = WOLF

all: libr $(NAME)

libr:
	make -C libft/ all

$(NAME): $(OBJ)
	gcc -v $(FLAGS) -o $@ $^ $(H_DIR) $(LIBS) $(FRAME)

$(S_DIR)/%.o: $(S_DIR)/%.c include/wolf.h
	gcc $(FLAGS) -c $< -o $@ $(H_DIR)

clean:
	make -C libft/ clean
	rm -f $(OBJ)

fclean : clean
	make -C libft/ fclean
	rm -f $(NAME)

re: fclean all
