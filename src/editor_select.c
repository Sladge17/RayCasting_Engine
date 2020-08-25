/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_select.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/08/25 23:29:09 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void draw_editor_select(t_game *game, t_editor *ed)
{
	SDL_Rect	p;
	SDL_Point	i;

	p.w = ed->scale;
	ed->scale = 50;
	draw_frame(game, "SELECT: ");
	draw_box(game, (H_H - 230) * S_W + H_W,
		ed->cursor.en->it[ed->cursor.en->cur], ed);
	i.y = (H_H - 160) * S_W + (H_W - 280);
	p.h = -1;
	p.y = -1;
	while (++p.y < 10)
	{
		p.x = -1;
		while (++p.x < 11)
		{
			if (++p.h > ed->cursor.en->max)
			{
				ed->scale = p.w;
				return ;
			}
			i.x = i.y + (p.y * S_W + p.x) * ed->scale;
			draw_box(game, i.x, ed->cursor.en->it[p.h], ed);
		}
	}	
}

void draw_editor_modify_wall(t_game *game, t_editor *ed)
{
	SDL_Rect	p;
	SDL_Point	i;

	p.w = ed->scale;
	ed->scale = 50;
	draw_frame(game, "MODIFY WALL:");
	draw_box(game, (H_H - 50) * S_W + H_W - 25,
		ed->cursor.en->it[ed->cursor.en->cur], ed);
	i.y = (H_H - 160) * S_W + (H_W - 280);
	p.h = -1;
	p.y = -1;
	ed->scale = p.w;
}
