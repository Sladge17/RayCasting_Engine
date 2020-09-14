/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/09/14 16:13:45 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

# define S_W 1400
# define S_H 780
# define H_W 700
# define H_H 390
# define THREADS 16
# define PI2 6.283185307179586

# define OK 1
# define ERROR 0



# define U 300

# define GAME 1
# define GUN_SCALE 200

# define MAX_LEVEL 3

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
	double			x;
	double			y;
}					t_vec2;

typedef struct		s_ivec4
{
	int				a;
	int				b;
	int				c;
	int				d;
}					t_ivec4;

typedef struct		s_isec
{
	SDL_Color		col;
	double			dist;
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
	double			rot;
	double			speed;
	double			rot_speed;
	double			border;
	int				status;
}					t_game_obj;

typedef struct		s_sprt
{
	t_vec2			pos;
	int				numb;
	t_vec2			dist2;
	double			rot;
	double			dist;
	double			size;
	double 			dir;
	SDL_Point		offset;
	SDL_Point		cursor;
	int				tile;
	SDL_Point		pix_pos;
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
	int				enms;
	int				achs;
	int				bars;
	int				ants;
	t_game_obj		player;
}					t_map;

typedef struct		s_level
{
	int				num;
	t_map			map;
}					t_level;

typedef struct		s_sector
{
	int				fov;
	double			ang_step;
	t_vec2			l_ang;
	t_vec2			r_ang;
}					t_sector;

typedef struct		s_player
{
	t_game_obj		obj;
	t_sector		sec;
	int				ray_depth;
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

typedef struct	s_drawer
{
	int			cursor[2];
	double		ray_angle;
	double		ray_tan[2];
	double		raylen[2];
	double		barrier_f[2][2];
	int			barrier_d[2];
	double		texel[2];
	int			mapid;
	int			wall_tile;
	int			tex_u;
	char		wall_part;
	int			wall_len;
	int			tex_d[2];
	int			pix_img;
}				t_drawer;

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
	SDL_Point		m_pos;
	int				click_time;
	int				press_l;
	int				press_r;
	Uint32			sel_col;
	int				status;
	int				cur_elem;
	int				level;
}					t_editor;

typedef struct		s_music
{
	Mix_Music		*music;
	int				play;
}					t_music;

typedef struct		s_game
{
	SDL_Window		*win;
	SDL_Surface		*surf;
	SDL_Surface		*athlas;
	SDL_Surface		*menu;
	SDL_Surface		*n_level;
	SDL_Surface		*s_win;
	int				*data;
	int				*data_img;
	int				*data_menu;
	int				*data_n_level;
	int				*data_win;
	double			*z_buffer;
	int				status;
	int				draw_map;
	int				fps;
	unsigned int	f_time;
	unsigned int	last_time;
	int				comeback;
	Uint32			delay;
	int				cheat;
	int				dummy;
	t_level			level;
	t_player		player;
	int				menu_flag;
	int				menu_item;
	int				level_edit;
	t_music			music;
}					t_game;

typedef struct		s_flow
{
	t_game			*game;
	int				flow;
}					t_flow;

//events
int			key_press(SDL_Keycode key, t_game *game);
void		mouse_move(SDL_MouseMotionEvent *e, t_game *game);
int			close_window(void *game);
void		mouse_weel(Sint32 y, t_game *game);
void		mouse_press(SDL_MouseButtonEvent *e, t_game *game);

//init
int			init_sdl(t_game *game);
int			check_segv(char *file);
int			free_word_line(char **line, char **word);
int			check_res(void);

//exit
void		ft_exit(char *line);
void		close_sdl(t_game *game);
int			free_init_sdl(t_game *game);

//run
void		check_keyboard(t_game *game, float d_time, int *quit);
void		redraw(t_game *game);
void		sdl_cycle(t_game *game);
void		draw_game(t_game *game);

//game object
void		move_forward(t_game_obj *obj, t_map *map, double koeff);
void		move_back(t_game_obj *obj, t_map *map, double koeff);
void		move_left(t_game_obj *obj, t_map *map, double koeff);
void		move_right(t_game_obj *obj, t_map *map, double koeff);
void		turn_left(t_game_obj *obj, double koeff);
void		turn_right(t_game_obj *obj, double koeff);
void		init_object(t_game_obj *obj, t_vec2 pos, double rot, double speed,
		double rot_speed);
		
//map
int			load_map(t_level *level, t_player *pl);

//player
void		init_player(t_game *game);

//engine
void		engine(t_game *game, t_isec *isec, int x);

//create color
void 		set_color(SDL_Color *col, int r, int g, int b);

//music
void		load_music(t_game *game);
void		close_music(t_game *game);
void		check_play_music(t_game *game);

//draw map
void		draw_map(t_game *game);

/*
** draw_gui.c
*/
void		draw_gui(t_game *game);
void		draw_back(t_game *game, t_drawer *dr, int tile_u, int tile_v);
void		draw_face(t_game *game, t_drawer *dr, int tile_u, int tile_v);
void		draw_gun(t_game *game, t_drawer *dr, int tile_u, int tile_v);

// void		draw_uitext(t_game *game);
void	draw_uitext(t_game *game, SDL_Rect* pos);


//color
void 		set_color(SDL_Color *col, int r, int g, int b);
int			clamp_col(int col);

//map editor
void		map_editor(t_game *game);
void		save_ed_map(t_editor *ed);
int			load_ed_map(t_editor *ed);
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
void		draw_editor_menu(t_game *game, t_editor *ed);
int			check_frame(SDL_MouseButtonEvent *e, t_game *game, t_editor *ed);
void		select_cursor_sprite(t_editor *ed);
void		editor_set_cell(t_editor *ed);
void		draw_editor_help(t_game *game);
void		draw_editor_select(t_game *game, t_editor *ed);
void		draw_editor_modify_wall(t_game *game, t_editor *ed);
void		draw_editor_side_wall(t_game *game, t_editor *ed, int side);
void		draw_cursor_info(t_game *game, t_editor *ed);

//draw sprites
void		draw_sprites(t_game *game);
void		def_spriteparam(t_game *game, t_sprt *sprite);
void		draw_vertline(t_game *game, t_sprt *sprite);

//new engine
/*
** door_sprite.c
*/
void	def_raylen(t_map *map, t_player *player, t_drawer *drawer);
char	check_barrier(t_map *map, t_drawer *drawer);
double	calc_raylen(t_player *player, t_drawer *drawer, char index);
void	def_barrierparam(t_player *player, t_drawer *drawer, char n_quad);
void	def_walltile(t_map *map, t_drawer *drawer);
void	def_walltile_u(t_drawer *drawer);

/*
** calc_quads.c
*/
void	calc_firstquad(t_map *map, t_player *player, t_drawer *drawer);
void	calc_secondquad(t_map *map, t_player *player, t_drawer *drawer);
void	calc_thirdquad(t_map *map, t_player *player, t_drawer *drawer);
void	calc_fourthquad(t_map *map, t_player *player, t_drawer *drawer);

//main menu
void	main_menu(t_game *game);
void	sld_events_menu(t_game *game, SDL_Event e, SDL_Point *flags);
void	print_wolf(SDL_Surface *sdest, const char *text, SDL_Rect *dest, int f_size);
	
#endif
