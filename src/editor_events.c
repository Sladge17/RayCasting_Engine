/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/09/15 09:18:00 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	key_press_editor3(SDL_Keycode key, t_editor *ed)
{
	if (key == SDLK_SPACE)
	{
		if (ed->put == 0)
			ed->put = 1;
		else
			ed->put = 0;
	}
	else if (key == SDLK_6)
		save_ed_map(ed);
	else if (key == SDLK_4)
		load_ed_map(ed);
}

void	key_press_editor2(SDL_Keycode key, t_editor *ed)
{
	if (key == SDLK_RIGHT && ed->cursor.pos.x < 63)
	{
		ed->cursor.pos.x += 1;
		if ((ed->cursor.pos.x - ed->offset.x) * ed->scale >= ed->panel.x)
			ed->offset.x += 1;
	}
	else if (key == SDLK_a)
	{
		ed->cursor.en->cur += 1;
		if (ed->cursor.en->cur > ed->cursor.en->max)
			ed->cursor.en->cur = 0;
	}
	else if (key == SDLK_z)
	{
		ed->cursor.en->cur -= 1;
		if (ed->cursor.en->cur < 0)
			ed->cursor.en->cur = ed->cursor.en->max;
	}
	else if (key == SDLK_q)
		ed->cursor.en->cur = 0;
	else
		key_press_editor3(key, ed);
}

int		key_press_editor(SDL_Keycode key, t_editor *ed)
{
	if (key == SDLK_UP && ed->cursor.pos.y > 0)
	{
		ed->cursor.pos.y -= 1;
		if (ed->cursor.pos.y - ed->offset.y < 0)
			ed->offset.y -= 1;
	}
	else if (key == SDLK_DOWN && ed->cursor.pos.y < 63)
	{
		ed->cursor.pos.y += 1;
		if ((ed->cursor.pos.y - ed->offset.y) * ed->scale >= ed->panel.y)
			ed->offset.y += 1;
	}
	else if (key == SDLK_LEFT && ed->cursor.pos.x > 0)
	{
		ed->cursor.pos.x -= 1;
		if (ed->cursor.pos.x - ed->offset.x < 0)
			ed->offset.x -= 1;
	}
	else
		key_press_editor2(key, ed);
	return (1);
}

void	mouse_events_editor(t_game *game, t_editor *ed, SDL_Event e,
	SDL_Point *flags)
{
	if (e.type == SDL_MOUSEBUTTONDOWN)
	{
		mouse_press_editor(&(e.button), game, ed);
		flags->y = 1;
	}
	else if (e.type == SDL_MOUSEBUTTONUP)
	{
		mouse_up_editor(&(e.button), ed);
		flags->y = 1;
	}
	else if (e.type == SDL_MOUSEMOTION)
	{
		mouse_move_editor(&(e.motion), ed);
		flags->y = 1;
	}
	else if (e.type == SDL_MOUSEWHEEL)
	{
		mouse_weel_editor(e.wheel.y, ed);
		flags->y = 1;
	}
}

void	sld_events_editor(t_game *game, t_editor *ed, SDL_Event e,
	SDL_Point *flags)
{
	if (e.type == SDL_QUIT)
	{
		flags->x = 2;
		game->status = 0;
	}
	else if (e.type == SDL_KEYDOWN)
	{
		if (e.key.keysym.sym == SDLK_ESCAPE)
			flags->x = 1;
		else
		{
			key_press_editor(e.key.keysym.sym, ed);
			if (ed->put == 1)
			{
				editor_set_cell(ed);
				if (ed->cursor.en->type != WALL)
					ed->put = 0;
			}
			flags->y = 1;
		}
	}
	else
		mouse_events_editor(game, ed, e, flags);
}
