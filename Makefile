# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/23 17:12:18 by vkaron            #+#    #+#              #
#    Updated: 2020/09/08 15:53:29 by vkaron           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all, clean, fclean, re, libr

PROGRAM_NAME = wolf3d

FLAGS =	-Wall -Wextra #-Werror -Ofast -g
#FLAGS =		-g

FILES =		act_sdl \
			color \
			draw_3d \
			draw_gui \
			draw_map \
			engine \
			game_object \
			init \
			key_events \
			main \
			map \
			mouse_events \
			music \
			player \
			service_stuff \
			editor \
			editor_file_load \
			editor_file_save \
			editor_mouse_events \
			editor_events \
			editor_draw_select_color \
			editor_service \
			editor_draw_menu \
			editor_draw_info \
			editor_init \
			editor_check_frame \
			editor_pick_map \
			editor_help \
			editor_select \
			sprite \
			calc_quads \
			draw_room \
			menu \
			menu_events \
			

S_DIR =		src

O_DIR =		obj

H_DIR =		include

O_FILES =	$(addprefix $(O_DIR)/, $(addsuffix .o, $(FILES)))

H_FILE =	$(H_DIR)/wolf.h

LIBS = 		-Llibft -lft \
			-lm \
			-lpthread

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	H_FIND =-I libft \
			-I $(H_DIR) \
			-I $(shell sdl2-config --prefix)/include/SDL2

	FRAME =	-lSDL2 \
			-lSDL2_mixer \
			-lSDL2_image \
			-lSDL2_ttf
endif
ifeq ($(UNAME_S),Darwin)
	H_FIND =-I libft \
			-I include \
			-I Frameworks/SDL2.framework/Headers\
			-I Frameworks/SDL2_image.framework/Headers\
			-I Frameworks/SDL2_ttf.framework/Headers\
			-I Frameworks/SDL2_mixer.framework/Headers\
			-F Frameworks/

	FRAME =	-F ./Frameworks/ \
			-framework SDL2 \
			-framework SDL2_image \
			-framework SDL2_ttf \
			-framework SDL2_mixer \
			-rpath Frameworks/
endif	

all: libr $(PROGRAM_NAME)

libr:
	make -C libft/ all

$(PROGRAM_NAME): $(O_FILES)
	gcc $(FLAGS) -o $@ $^ $(LIBS) $(FRAME)

$(O_DIR)/%.o: $(S_DIR)/%.c $(H_FILE)
	@mkdir -p $(O_DIR)
	gcc $(FLAGS) -c $< -o $@ $(H_FIND)

clean:
	make -C libft/ clean
	rm -f $(O_FILES)

fclean : clean
	make -C libft/ fclean
	rm -f $(PROGRAM_NAME)

re: fclean all
