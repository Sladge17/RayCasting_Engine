/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/07/27 18:20:52 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	save_ed_map(t_editor *ed)
{
	SDL_RWops *rw = SDL_RWFromFile("maps/map1", "wb");
	printf("File = %p\n",rw);
	if (rw == 0)
	{
		write(1, "file not save!\n", 15);
		return;
	}
	else
	{
    	size_t len = sizeof(ed->map);
    	if (SDL_RWwrite(rw, (void *)(&ed->map), len, 1) != len) {
        	printf("Couldn't fully write string\n");
    	} else {
        	printf("Wrote %ld 1-byte blocks\n", len);
    	}
    	SDL_RWclose(rw);
	}
}

void	load_ed_map(t_editor *ed)
{
	SDL_RWops *rw = SDL_RWFromFile("maps/map1", "rb");
	if(rw != NULL) 
	{
    	size_t len = sizeof(ed->map);
    	SDL_RWread(rw, &ed->map, len, 1);
    	SDL_RWclose(rw);
	}
	else
	{
		printf("not read file!");
	}
}

Uint32	get_img_color(t_game *game, int x, int y, int number)
{
	int row;
	int col;
	int index;
	
	row = number / 16;
	col = number - row * 16;
	index = (row * 65 + y) * game->athlas->w + col * 65 + x;
	return (game->data_img[index]); 
}

void	mouse_weel_editor(Sint32 y, t_editor *ed)
{
	SDL_Point pos;

	if (ed->mouse_pos.x <= ed->panel.x && ed->mouse_pos.y <= ed->panel.y)
	{
		if (y < 0) 
			ed->scale -= 1;
		if (y > 0)
			ed->scale += 1;
		if (ed->scale < 4)
			ed->scale = 4;
		if (ed->scale > 128)
			ed->scale = 128;
		pos.x = ed->mouse_pos.x / ed->scale;
		pos.y = ed->mouse_pos.y / ed->scale;
		ed->offset.x = ed->cursor.x - pos.x;
		ed->offset.y = ed->cursor.y - pos.y;
	}
}

void	mouse_move_editor(SDL_MouseMotionEvent *e, t_editor *ed)
{
	SDL_Point pos;
	
	ed->mouse_pos.x = e->x;
	ed->mouse_pos.y = e->y;
	if (ed->mouse_pos.x <= ed->panel.x && ed->mouse_pos.y <= ed->panel.y)
	{
		if (ed->press_l == 1)
		{
			pos.x = e->x / ed->scale + ed->offset.x;
			pos.y = e->y / ed->scale + ed->offset.y;
			if (pos.x >= 0 && pos.x < 64 && pos.y >= 0 && pos.y < 64)
			{
				ed->cursor = pos;
				ed->map.elem[ed->cursor.y][ed->cursor.x].number = ed->cur_wall;	
			}
		}
		else if (ed->press_r == 1)
		{
			ed->offset.x = ed->cursor.x - e->x / ed->scale;
			ed->offset.y = ed->cursor.y - e->y / ed->scale;
		}
	}
}

void	mouse_press_editor(SDL_MouseButtonEvent *e, t_editor *ed)
{
	SDL_Point pos;
	
	if (ed->mouse_pos.x <= ed->panel.x && ed->mouse_pos.y <= ed->panel.y)
	{
		pos.x = e->x / ed->scale + ed->offset.x;
		pos.y = e->y / ed->scale + ed->offset.y;
		if (pos.x >= 0 && pos.x < 64 && pos.y >= 0 && pos.y < 64)
		{
			ed->cursor = pos;
			if (e->button == SDL_BUTTON_LEFT)
				ed->map.elem[ed->cursor.y][ed->cursor.x].number = ed->cur_wall;
		}
	}
	else if (ed->mouse_pos.x >= S_W - 320 && ed->mouse_pos.y <= ed->panel.y)
	{
		ed->cur_elem = (ed->mouse_pos.y - 5) / 35;
	}
	if (e->button == SDL_BUTTON_LEFT)
		ed->press_l = 1;
	else if (e->button == SDL_BUTTON_RIGHT)
		ed->press_r = 1;
}

void	mouse_dbl_editor(SDL_MouseButtonEvent *e, t_editor *ed)
{
	printf("dbl_click [%d;%d]\n", e->x, e->y);
}

void	mouse_up_editor(SDL_MouseButtonEvent *e, t_editor *ed)
{
	Uint32 cur_time;
	
	if (e->button == SDL_BUTTON_LEFT)
	{
		ed->press_l = 0;
		cur_time = SDL_GetTicks();
		if (cur_time - ed->click_time <= 250)
		{
			mouse_dbl_editor(e, ed);
			return ;
		}	
		ed->click_time = cur_time;
	}
	else if (e->button == SDL_BUTTON_RIGHT)
		ed->press_r = 0;
	
}

int		key_press_editor(SDL_Keycode key, t_editor *ed)
{
	if (key == SDLK_UP && ed->cursor.y > 0)
	{
		ed->cursor.y -= 1;
		if (ed->cursor.y - ed->offset.y < 0)
			ed->offset.y -= 1;
	}
	else if (key == SDLK_DOWN && ed->cursor.y < 63)
	{
		ed->cursor.y += 1;
		if ((ed->cursor.y - ed->offset.y) * ed->scale >= ed->panel.y)
			ed->offset.y += 1;
	}
	else if (key == SDLK_LEFT && ed->cursor.x > 0)
	{
		ed->cursor.x -= 1;
		if (ed->cursor.x - ed->offset.x < 0)
			ed->offset.x -= 1;
	}
	else if (key == SDLK_RIGHT && ed->cursor.x < 63)
	{
		ed->cursor.x += 1;
		if ((ed->cursor.x - ed->offset.x) * ed->scale >= ed->panel.x)
			ed->offset.x += 1;
		
	}
	else if (key == SDLK_a)
	{
		ed->cur_wall += 1;
		if (ed->cur_wall >= 105)
			ed->cur_wall = -1;
	}
	else if (key == SDLK_z)
	{
		ed->cur_wall -= 1;
		if (ed->cur_wall < -1)
			ed->cur_wall = 105;
	}
	else if (key == SDLK_q)
	{
		ed->cur_wall = -1;
	}
	else if (key == SDLK_SPACE)
	{
		if (ed->put == 0)
			ed->put = 1;
		else
			ed->put = 0;
	}
	else if (key == SDLK_6)
		save_ed_map(ed);
	else if (key == SDLK_4)
		load_ed_map(ed);
	return (1);
}

void	sld_events_editor(t_editor *ed, SDL_Event e, int *quit, int *repaint)
{
	if (e.type == SDL_QUIT)
		*quit = 1;
	else if (e.type == SDL_KEYDOWN)
	{
		if (e.key.keysym.sym == SDLK_ESCAPE)
			*quit = 1;
		else
		{
			key_press_editor(e.key.keysym.sym, ed);
			if (ed->put == 1)
				ed->map.elem[ed->cursor.y][ed->cursor.x].number = ed->cur_wall;
			*repaint = 1;
		}
	}
	else if (e.type == SDL_MOUSEBUTTONDOWN)
	{
		mouse_press_editor(&(e.button), ed);
		*repaint = 1;
	}
	else if (e.type == SDL_MOUSEBUTTONUP)
	{
		mouse_up_editor(&(e.button), ed);
		*repaint = 1;
	}
	else if (e.type == SDL_MOUSEMOTION)
	{
		mouse_move_editor(&(e.motion), ed);
		*repaint = 1;
	}
	else if (e.type == SDL_MOUSEWHEEL)
	{
		mouse_weel_editor(e.wheel.y, ed);
		*repaint = 1;
	}
}

void		draw_box(t_game *game, int index, int number, int scale)
{
	SDL_Point	ofs;
	int			y_index;
	Uint32		col;
	
	ofs.y = -1;
	while (++ofs.y < scale)
	{
		y_index = ofs.y * S_W;
		ofs.x = -1;
		while(++ofs.x < scale)
		{
			if (number >= 0)
				col = get_img_color(game, ofs.x * 64 / scale,
					ofs.y * 64 / scale, number);
			else
				col = 0xFF707070;
			game->data[index + y_index + ofs.x] = col;
		}
	}
}

void		draw_map_editor(t_game *game, t_editor *ed)
{
	int i;
	int j;
	int y_index;
	int index;

	j = ed->offset.y < 0 ? -1 : ed->offset.y - 1;
	while (++j < 64)
	{
		y_index = (j - ed->offset.y) * ed->scale;
		if (y_index >= ed->panel.y)
			continue;
		y_index *= S_W;
		i = ed->offset.x < 0 ? -1 : ed->offset.x - 1;
		while (++i < 64)
		{
			index = (i - ed->offset.x) * ed->scale;
			if (index >= ed->panel.x)
				continue;
			draw_box(game, index + y_index, ed->map.elem[j][i].number, ed->scale);
		} 
	}
}

void		draw_cursor(t_game *game, t_editor *ed)
{
	int index;
	int x;
	int y;
	int	y_index;
	
	index = ((ed->cursor.y - ed->offset.y) * S_W + (ed->cursor.x - ed->offset.x)) * ed->scale;
	draw_box(game, index, ed->cur_wall, ed->scale);
	y = -1;
	while (++y < ed->scale)
	{
		y_index = y * S_W;
		x = -1;
		while (++x < ed->scale)
		{
			if (x == 0 || x == (ed->scale - 1) ||
				y == 0 || y == (ed->scale - 1))
				 game->data[index + y_index + x] = 0xFFFF0000;
		}
	}
}

void		init_editor(t_editor *ed)
{
	int i;
	int j;

	ed->offset.x = 0;
	ed->offset.y = 0;
	ed->cursor.x = 3;
	ed->cursor.y = 1;
	ed->panel.x = ((S_W - 320) / 64) * 64;
	ed->panel.y = ((S_H - 64) / 64) * 64;
	ed->cur_wall = -1;
	ed->put = 0;
	ed->scale = 32;
	ed->press_l = 0;
	ed->press_r = 0;
	ed->cur_elem = 3;
	ed->status = 0;
	ed->map.floor = 0xFF707070;
	ed->map.roof = 0xFF323246;
	j = -1;
	while(++j < 64)
	{
		i = -1;
		while (++i < 64) 
		{
			if (i == 0 || i == 63 || j == 63 || j == 63)
				ed->map.elem[j][i].number = 0;
			else
				ed->map.elem[i][j].number = -1;
		}
	}
}

void		print_ttf(SDL_Surface *sdest, const char *text, int size, SDL_Rect *dest)
{
	SDL_Color	col;
	TTF_Font	*fnt;
	SDL_Surface	*stext;
	const char	*f = "prgres/courier.ttf";

	col = (SDL_Color){255,255,200,255};
	fnt = NULL;
	fnt = TTF_OpenFont(f, size);
	if (!fnt) {
		printf("TTF_OpenFontRW: %s\n", TTF_GetError());
		exit(0);
	}
	stext = TTF_RenderText_Blended(fnt, text, col);
	SDL_BlitSurface(stext, NULL, sdest, dest);
	SDL_FreeSurface(stext);
	TTF_CloseFont(fnt);
}

void		draw_text_menu(t_game *game)
{
	SDL_Rect rect;
	const char *labels[15] = {"Hero", "Ceil color", "Floor color", "Wall", "Door", "Enemy", "Achiev", "Barier", "Entourage", "PICK", "CLEAR", "EDIT", "SAVE", "LOAD", "HELP"};
	int i;

	rect.x = S_W - 190;
	rect.y = 15;
	i = -1;
	while (++i < 9)
	{
		print_ttf(game->surf, labels[i], 18, &rect);
		rect.y += 35;
	}
	rect.x = S_W - 300;
	print_ttf(game->surf, labels[i++], 18, &rect);
	rect.x = S_W - 200;
	print_ttf(game->surf, labels[i++], 18, &rect);
	rect.x = S_W - 100;
	print_ttf(game->surf, labels[i++], 18, &rect);
	rect.y += 35;
	rect.x = S_W - 300;
	print_ttf(game->surf, labels[i++], 18, &rect);
	rect.x = S_W - 200;
	print_ttf(game->surf, labels[i++], 18, &rect);
	rect.x = S_W - 100;
	print_ttf(game->surf, labels[i], 18, &rect);
	
}

void		draw_menu(t_game *game, t_editor *ed)
{
	SDL_Rect rect;
	
	rect.h = S_H - 65;
	rect.w = 320;
	rect.y = 0;
	rect.x = S_W - 320;
	SDL_FillRect(game->surf, &rect, 0xFF505050);
	rect.h = 64;
	rect.w = S_W;
	rect.y = S_H - 64;
	rect.x = 0;
	SDL_FillRect(game->surf, &rect, 0xFF505050);
	
	rect.h = 32;
	rect.w = 300;
	rect.y = ed->cur_elem * 35 + 5;
	rect.x = S_W - 310;
	SDL_FillRect(game->surf, &rect, 0xFF707070);
	
	draw_text_menu(game);
	
}

void		map_editor(t_game *game)
{
	int			quit;
	int			repaint;
	SDL_Event	e;
	t_editor	editor;
	
	quit = 0;
	repaint = 1;
	init_editor(&editor);
	while (!quit)
	{
		if (SDL_PollEvent(&e) != 0)
			sld_events_editor(&editor, e, &quit, &repaint);
		if (repaint)
		{
			SDL_FillRect(game->surf, NULL, editor.map.roof);
			draw_map_editor(game, &editor);
			draw_cursor(game, &editor);
			draw_menu(game, &editor);
			SDL_UpdateWindowSurface(game->win);
			repaint = 0;
		}
		SDL_Delay(5);
	}
	game->status = 3;
}

