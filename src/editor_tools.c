/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/09/15 09:29:36 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	mouse_weel_editor(Sint32 y, t_editor *ed)
{
	SDL_Point pos;

	if (ed->m_pos.x <= ed->panel.x && ed->m_pos.y <= ed->panel.y)
	{
		if (y < 0)
			ed->scale -= 1;
		if (y > 0)
			ed->scale += 1;
		if (ed->scale < 4)
			ed->scale = 4;
		if (ed->scale > 128)
			ed->scale = 128;
		pos.x = ed->m_pos.x / ed->scale;
		pos.y = ed->m_pos.y / ed->scale;
		ed->offset.x = ed->cursor.pos.x - pos.x;
		ed->offset.y = ed->cursor.pos.y - pos.y;
	}
}

void	draw_select_col(t_game *game, t_editor *ed)
{
	SDL_Rect	rect;
	int			scale;

	if (ed->status == 1)
		draw_frame(game, "Select ceil color");
	else
		draw_frame(game, "Select floor color");
	rect.h = 50;
	rect.w = 100;
	rect.y = H_H - 230;
	rect.x = H_W + 100;
	SDL_FillRect(game->surf, &rect, ed->sel_col);
	scale = ed->scale;
	ed->scale = 350;
	draw_box(game, (H_H - 190) * S_W + H_W - 280, 687, ed);
	ed->scale = scale;
}

void	editor_set_side(t_type *c_type, int cursor, t_editor *ed,
	t_map_elem *cell)
{
	if (cursor == -1)
		*c_type = NONE;
	else
	{
		*c_type = ed->cursor.en->type;
		cell->side[0] = cursor;
		cell->side[2] = cursor;
		cell->side[1] = cursor + 1;
		cell->side[3] = cursor + 1;
	}
}
