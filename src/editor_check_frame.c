/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_check_frame.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/08/25 23:10:19 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	check_wall(SDL_MouseButtonEvent *e, t_editor *ed)
{
	SDL_Rect i;
	int index;

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

void	check_color(SDL_MouseButtonEvent *e, t_game *game, t_editor *ed,
	Uint32 *col)
{
	if (e->x >= H_W - 256 && e->x < H_W + 284 && e->y >= H_H - 100 &&
		e->y < H_H + 156)
		*col = game->data[e->y * S_W + e->x];
}

int		check_frame(SDL_MouseButtonEvent *e, t_game *game, t_editor *ed)
{
	if (ed->status > 0 && ed->mouse_pos.x > H_W - 320 &&
		ed->mouse_pos.x < H_W + 320 && ed->mouse_pos.y > H_H - 240 &&
		ed->mouse_pos.y < H_H + 240)
	{
		if (ed->status == 1)
			check_color(e, game, ed, &ed->map.roof);
		if (ed->status == 2)
			check_color(e, game, ed, &ed->map.floor);
		if (ed->status > 2 && ed->status < 9)
			check_wall(e, ed);
		if (ed->status > 0 && ed->mouse_pos.x > H_W - 40 &&
		ed->mouse_pos.x < H_W + 40 && ed->mouse_pos.y > H_H + 180 &&
		ed->mouse_pos.y < H_H + 230)
			ed->status = 0;
		return (1);
	}
	return (0);
}
