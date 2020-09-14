/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_check_frame.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/09/08 11:46:44 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	check_entity(SDL_MouseButtonEvent *e, t_editor *ed)
{
	SDL_Rect	i;
	int			index;

	i.y = H_H - 160;
	i.x = H_W - 280;
	i.h = i.y + 300;
	i.w = i.x + 550;
	if (e->x >= i.x && e->x <= i.w && e->y >= i.y && e->y <= i.h)
	{
		index = (e->y - i.y) / 50 * 11 + (e->x - i.x) / 50;
		if (index <= ed->cursor.en->max)
			ed->cursor.en->cur = index;
	}
}

void	check_side_wall(SDL_MouseButtonEvent *e, t_editor *ed)
{
	SDL_Rect	i;
	int			index;
	t_map_elem	*el;

	i.y = H_H - 160;
	i.x = H_W - 280;
	i.h = i.y + 300;
	i.w = i.x + 550;
	el = &ed->map.elem[ed->cursor.pos.y][ed->cursor.pos.x];
	if (e->x >= i.x && e->x <= i.w && e->y >= i.y && e->y <= i.h)
	{
		index = (e->y - i.y) / 37 * 15 + (e->x - i.x) / 37;
		if (index > 96)
			index += 445;
		if (index <= 569)
		{
			el->side[ed->status - 15] = index;
			if (el->side[0] == el->number && el->side[2] == el->number &&
			el->side[1] == el->number + 1 && el->side[3] == el->number + 1)
				el->modify = 0;
			else
				el->modify = 1;
		}
	}
}

void	check_modify_wall(SDL_MouseButtonEvent *e, t_editor *ed)
{
	SDL_Point	i;
	int			s;
	int			t;

	i.y = H_H - 180;
	i.x = H_W - 150;
	s = 100;
	t = 200;
	if (e->x >= i.x + s && e->x < i.x + t && e->y >= i.y && e->y < i.y + s)
		ed->status = 15;
	if (e->x >= i.x + s && e->x < i.x + t && e->y >= i.y + t && e->y < i.y + U)
		ed->status = 17;
	if (e->x >= i.x && e->x < i.x + s && e->y >= i.y + s && e->y < i.y + t)
		ed->status = 18;
	if (e->x >= i.x + t && e->x < i.x + U && e->y >= i.y + s && e->y < i.y + t)
		ed->status = 16;
	if (ed->map.elem[ed->cursor.pos.y][ed->cursor.pos.x].modify == 0)
	{
		s = ed->map.elem[ed->cursor.pos.y][ed->cursor.pos.x].number;
		ed->map.elem[ed->cursor.pos.y][ed->cursor.pos.x].side[0] = s;
		ed->map.elem[ed->cursor.pos.y][ed->cursor.pos.x].side[1] = s + 1;
		ed->map.elem[ed->cursor.pos.y][ed->cursor.pos.x].side[2] = s;
		ed->map.elem[ed->cursor.pos.y][ed->cursor.pos.x].side[3] = s + 1;
	}
}

void	check_color(SDL_MouseButtonEvent *e, t_game *game,
	Uint32 *col)
{
	if (e->x >= H_W - 280 && e->x < H_W + 70 && e->y >= H_H - 190 &&
		e->y < H_H + 160)
		*col = game->data[e->y * S_W + e->x];
}

int		check_frame(SDL_MouseButtonEvent *e, t_game *game, t_editor *ed)
{
	if (ed->status > 0 && ed->m_pos.x > H_W - 320 && ed->m_pos.x < H_W + 320
		&& ed->m_pos.y > H_H - 240 && ed->m_pos.y < H_H + 240)
	{
		if (ed->status == 1)
			check_color(e, game, &ed->map.roof);
		if (ed->status == 2)
			check_color(e, game, &ed->map.floor);
		if (ed->status > 2 && ed->status < 9)
			check_entity(e, ed);
		if (ed->status == 11)
			check_modify_wall(e, ed);
		if (ed->status >= 15 && ed->status <= 18)
			check_side_wall(e, ed);
		if (ed->status > 0 && ed->m_pos.x > H_W - 40 && ed->m_pos.x < H_W + 40
			&& ed->m_pos.y > H_H + 180 &&
		ed->m_pos.y < H_H + 230)
		{
			if (ed->status >= 15 && ed->status <= 18)
				ed->status = 11;
			else
				ed->status = 0;
		}
		return (1);
	}
	return (0);
}
