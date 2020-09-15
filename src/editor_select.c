/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_select.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/09/15 09:36:00 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	draw_editor_select(t_game *game, t_editor *ed)
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

void	draw_editor_side_wall_image(t_game *game, t_editor *ed, SDL_Rect p)
{
	SDL_Point	i;

	ed->scale = 37;
	i.y = (H_H - 160) * S_W + (H_W - 280);
	p.h = -1;
	p.y = -1;
	while (++p.y < 10)
	{
		p.x = -1;
		while (++p.x < 15)
		{
			if (++p.h > 569)
			{
				ed->scale = p.w;
				return ;
			}
			if (p.h == 97)
				p.h = 542;
			i.x = i.y + (p.y * S_W + p.x) * ed->scale;
			draw_box(game, i.x, p.h, ed);
		}
	}
}

void	draw_editor_side_wall(t_game *game, t_editor *ed, int side)
{
	SDL_Rect	p;
	t_map_elem	*el;

	p.w = ed->scale;
	ed->scale = 50;
	draw_frame(game, "SELECT WALL SIDE: ");
	el = &ed->map.elem[ed->cursor.pos.y][ed->cursor.pos.x];
	if (el->modify == 0)
		draw_box(game, (H_H - 230) * S_W + H_W + 100,
			el->number + side % 2, ed);
	else
		draw_box(game, (H_H - 230) * S_W + H_W + 100, el->side[side], ed);
	draw_editor_side_wall_image(game, ed, p);
}

void	draw_editor_modify_wall(t_game *game, t_editor *ed)
{
	int			scale;
	t_map_elem	*el;

	scale = ed->scale;
	ed->scale = 64;
	draw_frame(game, "MODIFY WALL:");
	el = &ed->map.elem[ed->cursor.pos.y][ed->cursor.pos.x];
	draw_box(game, (H_H - 62) * S_W + H_W - 32, el->number, ed);
	ed->scale = 100;
	if (el->modify == 1)
	{
		draw_box(game, (H_H - 180) * S_W + H_W - 50, el->side[0], ed);
		draw_box(game, (H_H + 20) * S_W + H_W - 50, el->side[2], ed);
		draw_box(game, (H_H - 80) * S_W + H_W + 50, el->side[1], ed);
		draw_box(game, (H_H - 80) * S_W + H_W - 150, el->side[3], ed);
	}
	else
	{
		draw_box(game, (H_H - 180) * S_W + H_W - 50, el->number, ed);
		draw_box(game, (H_H + 20) * S_W + H_W - 50, el->number, ed);
		draw_box(game, (H_H - 80) * S_W + H_W + 50, el->number + 1, ed);
		draw_box(game, (H_H - 80) * S_W + H_W - 150, el->number + 1, ed);
	}
	ed->scale = scale;
}
