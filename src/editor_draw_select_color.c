/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_draw_select_color.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/09/08 10:44:14 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	set_grad(t_game *game, int index, SDL_Rect tmp, SDL_Color *col)
{
	if (tmp.x > 512)
		tmp.w = tmp.h;
	game->data[index] = (clamp_col(col->r + tmp.w) << 16) |
		(clamp_col(col->g + tmp.w) << 8) | (clamp_col(col->b + tmp.w));
	if (tmp.x < 85)
		col->g += 3;
	else if (tmp.x < 171)
	{
		if (col->r > 3)
			col->r -= 3;
		else
			col->r = 0;
	}
	else if (tmp.x < 256)
		col->b += 3;
	else if (tmp.x < 341)
		col->g -= 3;
	else if (tmp.x < 427)
	{
		if (col->r < 253)
			col->r += 3;
		else
			col->r = 255;
	}
	else if (tmp.x < 512)
		col->b -= 3;
	else if (tmp.x < 600)
	{
		col->r = 0;
		col->g = 0;
		col->b = 0;
	}
}

void	draw_grad(t_game *game, int px, int py)
{
	SDL_Rect	tmp;
	SDL_Color	col;

	tmp.w = 256;
	tmp.h = 256;
	tmp.y = 0;
	while (tmp.y < 256)
	{
		col.r = 255;
		col.g = 0;
		col.b = 0;
		tmp.x = 0;
		while (tmp.x < 540)
		{
			set_grad(game, (py + tmp.y) * S_W + tmp.x + px, tmp, &col);
			++tmp.x;
		}
		--tmp.h;
		tmp.w -= 2;
		++tmp.y;
	}
}

void	draw_select_col(t_game *game, t_editor *ed)
{
	SDL_Rect rect;
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
