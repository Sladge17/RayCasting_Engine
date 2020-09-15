/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 13:06:28 by jthuy             #+#    #+#             */
/*   Updated: 2020/09/15 13:27:58 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

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
	double			dir;
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

typedef struct		s_drawer
{
	int				cursor[2];
	double			ray_angle;
	double			ray_tan[2];
	double			raylen[2];
	double			barrier_f[2][2];
	int				barrier_d[2];
	double			texel[2];
	int				mapid;
	int				wall_tile;
	int				tex_u;
	char			wall_part;
	int				wall_len;
	int				tex_d[2];
	int				pix_img;
}					t_drawer;

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

#endif
