/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/08/08 22:52:16 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	draw_map_editor(t_game *game, t_editor *ed)
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
			draw_box(game, index + y_index, ed->map.elem[j][i].number,
			ed);
		}
	}
}

void	draw_cursor(t_game *game, t_editor *ed)
{
	int index;
	int x;
	int y;
	int	y_index;

	index = ((ed->cursor.y - ed->offset.y) * S_W +
		(ed->cursor.x - ed->offset.x)) * ed->scale;
	draw_box(game, index, ed->cur_wall, ed);
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
}

void	map_editor(t_game *game)
{
	SDL_Point	flags;
	SDL_Event	e;
	t_editor	editor;

	flags.x = 0;
	flags.y = 1;
	init_editor(&editor);
	while (!flags.x)
	{
		if (SDL_PollEvent(&e) != 0)
			sld_events_editor(game, &editor, e, &flags);
		if (flags.y)
		{
			SDL_FillRect(game->surf, NULL, editor.map.roof);
			draw_map_editor(game, &editor);
			draw_cursor(game, &editor);
			draw_menu(game, &editor);
			status_selector(game, &editor);
			SDL_UpdateWindowSurface(game->win);
			flags.y = 0;
		}
		SDL_Delay(5);
	}
	game->status = 3;
}
