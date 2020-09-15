/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/09/15 13:27:11 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

# include <pthread.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>

# include "const.h"
# include "struct.h"

int		key_press(SDL_Keycode key, t_game *game);
void	mouse_move(SDL_MouseMotionEvent *e, t_game *game);
int		close_window(void *game);
void	mouse_weel(Sint32 y, t_game *game);
void	mouse_press(SDL_MouseButtonEvent *e, t_game *game);

int		init_sdl(t_game *game);
int		check_segv(char *file);
int		free_word_line(char **line, char **word);
int		check_res(void);

void	ft_exit(char *line);
void	close_sdl(t_game *game);
int		free_init_sdl(t_game *game);

void	check_keyboard(t_game *game, float d_time, int *quit);
void	redraw(t_game *game);
void	sdl_cycle(t_game *game);
int		check_start(t_game *game);
void	draw_game(t_game *game);
void	draw_floor(t_game *game, int y, int x, int max_y);
void	draw_roof(t_game *game, int y, int x, int max_y);

void	check_left_up(t_game_obj *obj, t_map *map, t_vec2 *test);
void	check_right_up(t_game_obj *obj, t_map *map, t_vec2 *test);
void	check_left_down(t_game_obj *obj, t_map *map, t_vec2 *test);
void	check_right_down(t_game_obj *obj, t_map *map, t_vec2 *test);
void	check_x(t_game_obj *obj, t_map *map, t_vec2 *test);
void	check_y(t_game_obj *obj, t_map *map, t_vec2 *test);
void	check_step(t_game_obj *obj, t_map *map, t_vec2 *test);
void	move_forward(t_game_obj *obj, t_map *map, double koeff);
void	move_back(t_game_obj *obj, t_map *map, double koeff);
void	move_left(t_game_obj *obj, t_map *map, double koeff);
void	move_right(t_game_obj *obj, t_map *map, double koeff);
void	turn_left(t_game_obj *obj, double koeff);
void	turn_right(t_game_obj *obj, double koeff);
void	init_object(t_game_obj *obj, t_vec2 pos, double rot, t_vec2 speed);

int		load_map(t_level *level, t_player *pl);
void	set_read_sprite(t_map *map, int *cmp, t_player *pl, SDL_Point *p);

void	init_player(t_game *game);

void	def_walltile(t_map *map, t_drawer *drawer);
void	def_wallparams(t_player *player, t_drawer *drawer);
void	engine(t_game *game, t_isec *isec, int x);

void	set_color(SDL_Color *col, int r, int g, int b);

void	load_music(t_game *game);
void	close_music(t_game *game);
void	check_play_music(t_game *game);

void	draw_map(t_game *game);

void	draw_gui(t_game *game);
void	draw_back(t_game *game, t_drawer *dr, int tile_u, int tile_v);
void	draw_face(t_game *game, t_drawer *dr, int tile_u, int tile_v);
void	draw_gun(t_game *game, t_drawer *dr, int tile_u, int tile_v);
void	draw_uitext(t_game *game, SDL_Rect *pos);

void	set_color(SDL_Color *col, int r, int g, int b);
int		clamp_col(int col);

void	map_editor(t_game *game);
void	save_ed_map(t_editor *ed);
int		load_ed_map(t_editor *ed);
void	mouse_up_editor(SDL_MouseButtonEvent *e, t_editor *ed);
void	mouse_press_editor(SDL_MouseButtonEvent *e, t_game *game,
			t_editor *ed);
void	mouse_move_editor(SDL_MouseMotionEvent *e, t_editor *ed);
void	mouse_weel_editor(Sint32 y, t_editor *ed);
void	sld_events_editor(t_game *game, t_editor *ed, SDL_Event e,
			SDL_Point *flags);
void	draw_select_col(t_game *game, t_editor *ed);
void	print_ttf(SDL_Surface *sdest, const char *text, int size,
			SDL_Rect *dest);
Uint32	get_img_color(t_game *game, int x, int y, int number);
void	draw_box(t_game *game, int index, int number, t_editor *ed);
void	draw_frame(t_game *game, const char *message);
void	draw_editor_menu(t_game *game, t_editor *ed);
int		check_frame(SDL_MouseButtonEvent *e, t_game *game, t_editor *ed);
void	select_cursor_sprite(t_editor *ed);
void	editor_set_cell(t_editor *ed);
void	draw_editor_help(t_game *game);
void	draw_editor_select(t_game *game, t_editor *ed);
void	draw_editor_modify_wall(t_game *game, t_editor *ed);
void	draw_editor_side_wall(t_game *game, t_editor *ed, int side);
void	editor_set_side(t_type *c_type, int cursor, t_editor *ed,
			t_map_elem *cell);
int		hex_to_int(char sym);
int		read_base_color(t_map *map, char *data);

void	init_editor_map_ent(t_editor *ed);
void	init_editor_wall_pl_bar(t_editor *ed);
void	init_editor_enemy_ach_door(t_editor *ed);
void	init_type_map(t_editor *ed);
void	init_editor(t_editor *ed);

void	draw_text(t_game *game, char *str, SDL_Rect *pos);
void	draw_number(t_game *game, int n, SDL_Rect *pos);
void	draw_text_number(t_game *game, char *str, int n, SDL_Rect *pos);
void	draw_cursor_info2(t_game *game, t_editor *ed);
void	draw_cursor_info(t_game *game, t_editor *ed);

void	draw_preview(t_game *game, t_editor *ed, int i, SDL_Rect rect);
void	draw_text_menu(t_game *game, t_editor *ed);
void	draw_editor_menu(t_game *game, t_editor *ed);

void	write_hex(int fd, char n);
void	write_char(int fd, int data);
void	write_fchar(int fd, int data);
void	write_map(int fd, t_editor *ed);
void	save_ed_map(t_editor *ed);

void	check_keyboard(t_game *game, float d_time, int *quit);

void	draw_sprites(t_game *game);
void	def_spriteparam(t_game *game, t_sprt *sprite);
void	draw_vertline(t_game *game, t_sprt *sprite);

void	def_raylen(t_map *map, t_player *player, t_drawer *drawer);
char	check_barrier(t_map *map, t_drawer *drawer);
double	calc_raylen(t_player *player, t_drawer *drawer, char index);
void	def_barrierparam(t_player *player, t_drawer *drawer, char n_quad);
void	def_walltile(t_map *map, t_drawer *drawer);
void	def_walltile_u(t_drawer *drawer);

void	calc_firstquad(t_map *map, t_player *player, t_drawer *drawer);
void	calc_secondquad(t_map *map, t_player *player, t_drawer *drawer);
void	calc_thirdquad(t_map *map, t_player *player, t_drawer *drawer);
void	calc_fourthquad(t_map *map, t_player *player, t_drawer *drawer);

void	main_menu(t_game *game);
void	sld_events_menu(t_game *game, SDL_Event e, SDL_Point *flags);
void	print_wolf(SDL_Surface *sdest, const char *text, SDL_Rect
			*dest, int f_size);

#endif
