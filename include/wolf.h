/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/08/10 20:33:47 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

# define S_W 2400
# define S_H 1200
# define H_W 1200
# define H_H 600
# define RATIO 1.78f
# define THREADS 16

# define OK 1
# define ERROR 0

# define INFINITY 1e99
# define INFY 1e99
# define MIN_OFFSET 0.01f
# define RECURCE_DEPTH 3
# define REFR_DEPTH 10

# define GAME 1

# include <pthread.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft.h"
# include <fcntl.h>

# include <stdio.h>

# include <sys/types.h>
# include <sys/stat.h>

# include <SDL.h>
# include <SDL_image.h>
# include <SDL_ttf.h>
# include <SDL_mixer.h>

typedef struct		s_vec2
{
	float			x;
	float			y;
}					t_vec2;

typedef struct		s_isec
{
	SDL_Color		col;
	float			dist;
	int				height;
	int				number;
	int				colum;
}					t_isec;

typedef enum		e_type
{
	WALL,
	DOOR,
	ENEMY,
	ACHIEV,
	BARIER,
	ENTOURAGE
}					t_type;

typedef struct		s_game_obj
{
	t_vec2			pos;
	t_vec2			dir;
	float			rot;
	float				speed;
	int				rot_speed;
	float				border;
	int				status;
}					t_game_obj;

typedef struct		s_sprt
{
}					t_sprt;

typedef struct		s_enm
{
	t_game_obj		obj;
	t_sprt			*sprt;
}					t_enm;

typedef struct		s_ach
{
	t_vec2			pos;
	float			border;
	t_sprt			*sprt;
}					t_ach;

typedef struct		s_bar
{
	t_vec2			pos;
	float			border;
	t_sprt			*sprt;
}					t_bar;

typedef struct		s_antrg
{
	t_vec2			pos;
	t_sprt			*sprt;
}					t_acntrg;

typedef	struct		s_map_elem
{
	int				side[4];
	int				lock;
	int				number;
	t_type			type;
}					t_map_elem;

typedef struct		s_map
{
	Uint32			floor;
	Uint32			roof;
	t_map_elem		elem[64][64];
	t_enm			enm[128];
	t_game_obj		player;
}					t_map;

typedef struct		s_level
{
	int				number;
	t_map			map;
}					t_level;

typedef struct		s_sector
{
	float			fov;
	float			ang_step;
	t_vec2			l_ang;
	t_vec2			r_ang;
}					t_sector;

typedef struct		s_player
{
	t_game_obj		obj;
	t_sector		sec;
}					t_player;

typedef struct		s_message
{
	char *			text;
	SDL_Color		color;
	int				size;
}					t_message;

typedef struct		s_editor
{
	SDL_Point		offset;
	SDL_Point		cursor;
	t_map			map;
	SDL_Point		panel;
	int				cur_wall;
	int				put;
	int				scale;
	SDL_Point		mouse_pos;
	int				click_time;
	int				press_l;
	int				press_r;
	Uint32			sel_col;
	int				status;
	int				cur_elem;
	
}					t_editor;

typedef struct		s_game
{
	SDL_Window		*win;
	SDL_Surface		*surf;
	SDL_Surface		*athlas;
	int				*data;
	int				*data_img;
	int				status;
	int				draw_map;
	int				fps;
	unsigned int	f_time;
	unsigned int	last_time;
	int				cheat;
	int				dummy;
	int				thread;
	t_level			level;
	t_player		player;
}					t_game;



//events
int			key_press(SDL_Keycode key, t_game *game);
void		mouse_move(SDL_MouseMotionEvent *e, t_game *game);
int			close_window(void *game);
void		mouse_weel(Sint32 y, t_game *game);
void		mouse_press(SDL_MouseButtonEvent *e, t_game *game);

//init
int			init_sdl(t_game *game);

//exit
void		ft_exit(char *line);
void		close_sdl(t_game *game);
int			free_init_sdl(t_game *game);

//run
void		sdl_cycle(t_game *game);
void		draw_game(t_game *game);

//game object
void		move_forward(t_game_obj *obj, t_map *map, float koeff);
void		move_back(t_game_obj *obj, t_map *map, float koeff);
void		move_left(t_game_obj *obj, t_map *map, float koeff);
void		move_right(t_game_obj *obj, t_map *map, float koeff);
void		turn_left(t_game_obj *obj, float koeff);
void		turn_right(t_game_obj *obj, float koeff);
void		init_object(t_game_obj *obj, t_vec2 pos, int rot, float speed,
		int rot_speed);
		
//map
void		load_map(t_level *level, t_player *pl);

//player
void		init_player(t_game *game);

//engine
void		engine(t_game *game, t_isec *isec, int x);

//create color
void 		set_color(SDL_Color *col, int r, int g, int b);

//music
void		load_music(t_game *game);

//draw map
void		draw_map(t_game *game);

//draw GUI
void		draw_gui(t_game *game);

//color
void 		set_color(SDL_Color *col, int r, int g, int b);
int			clamp_col(int col);
void		set_col_by_num(SDL_Color *col, int number);

//map editor
void		map_editor(t_game *game);
void		save_ed_map(t_editor *ed);
void		load_ed_map(t_editor *ed);
void		mouse_up_editor(SDL_MouseButtonEvent *e, t_editor *ed);
void		mouse_press_editor(SDL_MouseButtonEvent *e, t_game *game, t_editor *ed);
void		mouse_move_editor(SDL_MouseMotionEvent *e, t_editor *ed);
void		mouse_weel_editor(Sint32 y, t_editor *ed);
void		sld_events_editor(t_game *game, t_editor *ed, SDL_Event e, SDL_Point *flags);
void		draw_select_col(t_game *game, t_editor *ed);
void		print_ttf(SDL_Surface *sdest, const char *text, int size, SDL_Rect *dest);
Uint32		get_img_color(t_game *game, int x, int y, int number);
void		draw_box(t_game *game, int index, int number, t_editor *ed);
void		init_editor(t_editor *ed);
void		draw_frame(t_game *game, const char *message);
void		draw_menu(t_game *game, t_editor *ed);
int			check_frame(SDL_MouseButtonEvent *e, t_game *game, t_editor *ed);
#endif
