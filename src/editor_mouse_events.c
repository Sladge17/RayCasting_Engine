/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_mouse_events.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/08/08 22:35:36 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

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

void	check_button_menu(t_editor *ed)
{
	//printf("mouse [%d,%d]\n",ed->mouse_pos.x,ed->mouse_pos.y);
	if (ed->mouse_pos.y >= 325 && ed->mouse_pos.y < 355)
	{
		if (ed->mouse_pos.x >= S_W - 300 && ed->mouse_pos.x < S_W - 200)
			ed->status = 9;
		else if (ed->mouse_pos.x >= S_W - 200 && ed->mouse_pos.x < S_W - 100)
			ed->status = 10;
		else if (ed->mouse_pos.x >= S_W - 100 && ed->mouse_pos.x < S_W)
			ed->status = 11;		
	}
	else if (ed->mouse_pos.y >= 355 && ed->mouse_pos.y < 390)
	{
		if (ed->mouse_pos.x >= S_W - 300 && ed->mouse_pos.x < S_W - 200)
			ed->status = 12;
		else if (ed->mouse_pos.x >= S_W - 200 && ed->mouse_pos.x < S_W - 100)
			ed->status = 13;
		else if (ed->mouse_pos.x >= S_W - 100 && ed->mouse_pos.x < S_W)
			ed->status = 14;		
	}
	if (ed->cur_elem > 10)
		ed->cur_elem = 0;
}

void	mouse_press_editor(SDL_MouseButtonEvent *e, t_game *game, t_editor *ed)
{
	SDL_Point pos;
	
	if (check_frame(e, game, ed))
		return ;
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
		//if ((ed->cur_elem = (ed->mouse_pos.y - 5) / 35) < 9)
		//	ed->status = ed->cur_elem;
		ed->cur_elem = (ed->mouse_pos.y - 5) / 35;
		
			
	}
	if (e->button == SDL_BUTTON_LEFT)
		ed->press_l = 1;
	else if (e->button == SDL_BUTTON_RIGHT)
		ed->press_r = 1;
	printf("ed-status=%d\n", ed->status);
}

void	mouse_dbl_editor(SDL_MouseButtonEvent *e, t_editor *ed)
{
	//printf("dbl_click [%d;%d]\n", e->x, e->y);
	if (ed->mouse_pos.x >= S_W - 320 && ed->mouse_pos.y <= ed->panel.y)
	{
			ed->status = ed->cur_elem;
			check_button_menu(ed);			
	}
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
