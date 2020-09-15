/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_mouse_events.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/09/15 09:22:20 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	mouse_move_editor(SDL_MouseMotionEvent *e, t_editor *ed)
{
	SDL_Point pos;

	ed->m_pos.x = e->x;
	ed->m_pos.y = e->y;
	if (ed->m_pos.x <= ed->panel.x && ed->m_pos.y <= ed->panel.y)
	{
		if (ed->press_l == 1 && ed->cur_elem == 3)
		{
			pos.x = e->x / ed->scale + ed->offset.x;
			pos.y = e->y / ed->scale + ed->offset.y;
			if (pos.x >= 0 && pos.x < 64 && pos.y >= 0 && pos.y < 64)
			{
				ed->cursor.pos = pos;
				editor_set_cell(ed);
			}
		}
		else if (ed->press_r == 1)
		{
			ed->offset.x = ed->cursor.pos.x - e->x / ed->scale;
			ed->offset.y = ed->cursor.pos.y - e->y / ed->scale;
		}
	}
}

void	check_button_menu(t_editor *ed)
{
	if (ed->m_pos.y >= 325 && ed->m_pos.y < 355)
	{
		if (ed->m_pos.x >= S_W - 300 && ed->m_pos.x < S_W - 200)
			ed->status = 9;
		else if (ed->m_pos.x >= S_W - 200 && ed->m_pos.x < S_W - 100)
			ed->status = 10;
		else if (ed->m_pos.x >= S_W - 100 && ed->m_pos.x < S_W)
			ed->status = 11;
	}
	else if (ed->m_pos.y >= 355 && ed->m_pos.y < 390)
	{
		if (ed->m_pos.x >= S_W - 300 && ed->m_pos.x < S_W - 200)
			ed->status = 12;
		else if (ed->m_pos.x >= S_W - 200 && ed->m_pos.x < S_W - 100)
			ed->status = 13;
		else if (ed->m_pos.x >= S_W - 100 && ed->m_pos.x < S_W)
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
	if (ed->m_pos.x <= ed->panel.x && ed->m_pos.y <= ed->panel.y)
	{
		pos.x = e->x / ed->scale + ed->offset.x;
		pos.y = e->y / ed->scale + ed->offset.y;
		if (pos.x >= 0 && pos.x < 64 && pos.y >= 0 && pos.y < 64)
		{
			ed->cursor.pos = pos;
			if (e->button == SDL_BUTTON_LEFT)
				editor_set_cell(ed);
		}
	}
	else if (ed->m_pos.x >= S_W - 320 && ed->m_pos.y <= ed->panel.y)
	{
		ed->cur_elem = (ed->m_pos.y - 5) / 35;
		select_cursor_sprite(ed);
	}
	if (e->button == SDL_BUTTON_LEFT)
		ed->press_l = 1;
	else if (e->button == SDL_BUTTON_RIGHT)
		ed->press_r = 1;
}

void	mouse_dbl_editor(t_editor *ed)
{
	if (ed->m_pos.x >= S_W - 320 && ed->m_pos.y <= ed->panel.y)
	{
		ed->status = ed->cur_elem;
		check_button_menu(ed);
	}
	if (ed->status == 12)
		save_ed_map(ed);
	else if (ed->status == 10)
		init_editor(ed);
	else if (ed->status == 13)
		load_ed_map(ed);
	if (ed->status != 11 && ed->status > 8 && ed->status < 14)
		ed->status = 0;
	printf("ed-status=%d\n", ed->status);
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
			mouse_dbl_editor(ed);
			return ;
		}
		ed->click_time = cur_time;
	}
	else if (e->button == SDL_BUTTON_RIGHT)
		ed->press_r = 0;
}
