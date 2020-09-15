/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/09/15 09:04:11 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	draw_col_frame(t_game *game, t_editor *ed, SDL_Point pos, Uint32 color)
{
	int index;
	int x;
	int y;
	int	y_index;

	index = ((pos.y - ed->offset.y) * S_W +
		(pos.x - ed->offset.x)) * ed->scale;
	y = -1;
	while (++y < ed->scale)
	{
		y_index = y * S_W;
		x = -1;
		while (++x < ed->scale)
		{
			if (x == 0 || x == (ed->scale - 1) ||
				y == 0 || y == (ed->scale - 1))
				game->data[index + y_index + x] = color;
		}
	}
}

void	draw_map_editor(t_game *game, t_editor *ed)
{
	SDL_Point	p;
	int			y_index;
	int			index;

	p.y = ed->offset.y < 0 ? -1 : ed->offset.y - 1;
	while (++p.y < 64)
	{
		y_index = (p.y - ed->offset.y) * ed->scale;
		if (y_index >= ed->panel.y)
			continue;
		y_index *= S_W;
		p.x = ed->offset.x < 0 ? -1 : ed->offset.x - 1;
		while (++p.x < 64)
		{
			index = (p.x - ed->offset.x) * ed->scale;
			if (index >= ed->panel.x)
				continue;
			draw_box(game, index + y_index, ed->map.elem[p.y][p.x].number,
			ed);
			if (ed->type_map[p.y][p.x] == WALL && ed->map.elem[p.y][p.x].modify)
				draw_col_frame(game, ed, p, 0xFF0000FF);
		}
	}
}

void	status_selector(t_game *game, t_editor *ed)
{
	if (ed->status == 1)
	{
		ed->sel_col = ed->map.roof;
		draw_select_col(game, ed);
	}
	else if (ed->status == 2)
	{
		ed->sel_col = ed->map.floor;
		draw_select_col(game, ed);
	}
	else if (ed->status > 2 && ed->status < 9)
		draw_editor_select(game, ed);
	else if (ed->status == 11)
	{
		if (ed->cursor.en->type == WALL &&
			ed->map.elem[ed->cursor.pos.y][ed->cursor.pos.x].number >= 0)
			draw_editor_modify_wall(game, ed);
		else
			ed->status = 0;
	}
	else if (ed->status == 14)
		draw_editor_help(game);
	else if (ed->status >= 15 && ed->status <= 18)
		draw_editor_side_wall(game, ed, ed->status - 15);
}

void	update_editor(t_game *game, t_editor *ed)
{
	SDL_FillRect(game->surf, NULL, ed->map.roof);
	draw_map_editor(game, ed);
	draw_col_frame(game, ed, ed->cursor.pos, 0xFFFF0000);
	draw_editor_menu(game, ed);
	status_selector(game, ed);
	SDL_UpdateWindowSurface(game->win);
}

void	map_editor(t_game *game)
{
	SDL_Point	flags;
	SDL_Event	e;
	t_editor	ed;

	flags = (SDL_Point){0, 1};
	ed.level = game->level.num;
	init_editor(&ed);
	if (game->cheat)
		ed.level = game->level_edit;
	if (!load_ed_map(&ed))
		init_editor(&ed);
	while (!flags.x)
	{
		if (SDL_PollEvent(&e) != 0)
			sld_events_editor(game, &ed, e, &flags);
		if (flags.y)
		{
			update_editor(game, &ed);
			flags.y = 0;
		}
		SDL_Delay(5);
	}
	game->status = 3;
	if (flags.x == 2)
		game->status = 0;
}
