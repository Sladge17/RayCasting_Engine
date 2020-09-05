/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/09/05 20:42:01 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

# define S_W 1400
# define S_H 700
# define H_W 700
# define H_H 350
# define RATIO 1.78f
# define THREADS 1
# define PI2 6.283185307179586

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
	NONE,
	PLAYER,
	WALL,
	DOOR,
	ENEMY,
	ACHIV,
	BARIER,
	ENTOURAGE
}					t_type;

typedef struct		s_game_obj
{
	t_vec2			pos;
	t_vec2			dir;
	float			rot;
	float			speed;
	float			rot_speed;
	float			border;
	int				status;
}					t_game_obj;

typedef struct		s_sprt
{
	t_vec2			pos;
	int				numb;
	double			dist2[2];
	double			rot;
	double			dist;
	int				size;
	double 			dir;
	int				offset[2];
	int				cursor[2];
	int				tile;
	int				pix_pos[2];
	int				pix_win;
	int				pix_img;
}					t_sprt;

typedef struct		s_enm
{
	t_game_obj		obj;
	t_sprt			sprt;
	int				status;
}					t_enm;

typedef struct		s_dr
{
	t_game_obj		obj;
	t_sprt			sprt;
	int				status;
}					t_dr;

typedef struct		s_ach
{
	t_vec2			pos;
	float			border;
	t_sprt			sprt;
}					t_ach;

typedef struct		s_bar
{
	t_sprt			sprt;
	int				status;
}					t_bar;

typedef struct		s_ant
{
	t_vec2			pos;
	t_sprt			sprt;
}					t_ant;

typedef	struct		s_map_elem
{
	int				side[4];
	int				lock;
	int				number;
	int				modify;
}					t_map_elem;

typedef struct		s_map
{
	Uint32			floor;
	Uint32			roof;
	t_map_elem		elem[64][64];
	t_enm			enm[128];
	t_ach			ach[64];
	t_bar			bar[64];
	t_ant			ant[64];
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
}					t_sector;

typedef struct		s_player
{
	t_game_obj		obj;
	t_sector		sec;
}					t_player;

typedef struct		s_message
{
	char			*text;
	SDL_Color		color;
	int				size;
}					t_message;

typedef struct		s_entity
{
	int				it[64];
	int				cur;
	int				max;
	t_type			type;
}					t_entity;

typedef struct		s_cursor
{
	SDL_Point		pos;
	t_entity		*en;
}					t_cursor;

typedef struct		s_editor
{
	SDL_Point		offset;
	t_cursor		cursor;
	t_map			map;
	SDL_Point		panel;
	t_entity		wall;
	t_entity		player;
	t_entity		door;
	t_entity		enemy;
	t_entity		barier;
	t_entity		entourage;
	t_entity		achiv;
	t_type			type_map[64][64];
	Uint8			enemies;
	Uint8			bariers;
	Uint8			achivs;
	Uint8			entours;		
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
	double			*z_buffer;//[S_W * S_H];
	int				status;
	int				draw_map;
	int				fps;
	unsigned int	f_time;
	unsigned int	last_time;
	int				cheat;
	int				dummy;
//	int				thread;
	t_level			level;
	t_player		player;
}					t_game;

typedef struct		s_thread
{
	t_game			*game;
	int				thread;
}					t_thread;

//events
int			key_press(SDL_Keycode key, t_game *game);
void		mouse_move(SDL_MouseMotionEvent *e, t_game *game);
int			close_window(void *game);
void		mouse_weel(Sint32 y, t_game *game);
void		mouse_press(SDL_MouseButtonEvent *e, t_game *game);

//init
int			init_sdl(t_game *game);
void		check_segv(char *file);
int			free_word_line(char **line, char **word);

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
void		init_object(t_game_obj *obj, t_vec2 pos, float rot,
				float speed, float rot_speed);
		
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
void		save_ed_map(t_editor *ed, char number);
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
void		select_cursor_sprite(t_editor *ed);
void		editor_set_cell(t_editor *ed);
void		draw_editor_help(t_game *game);
void		draw_editor_select(t_game *game, t_editor *ed);
void		draw_editor_modify_wall(t_game *game, t_editor *ed);
void		draw_editor_side_wall(t_game *game, t_editor *ed, int side);

//draw sprites
void		draw_sprites(t_game *game);
void		def_spriteparam(t_game *game, t_sprt *sprite);
void		draw_vertline(t_game *game, t_sprt *sprite);

#endif
