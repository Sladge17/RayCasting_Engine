/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/09/09 15:41:42 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	sld_events_menu(t_game *game, SDL_Event e, SDL_Point *flags)
{
	if (e.type == SDL_QUIT)
	{
		game->status = 0;
		flags->x = 1;
	}
	else if (e.type == SDL_KEYDOWN)
	{
		if (e.key.keysym.sym == SDLK_ESCAPE)
			flags->x = 1;
		else if (e.key.keysym.sym == SDLK_RETURN)
		{
			game->status = 1;
			flags->x = 2;
		}
	}
	else if (e.type == SDL_MOUSEBUTTONDOWN)
	{
		//mouse_press_editor(&(e.button), game, ed);
		flags->y = 1;
	}
	else if (e.type == SDL_MOUSEBUTTONUP)
	{
		//mouse_up_editor(&(e.button), ed);
		game->status = 1;
		flags->x = 2;
	}
	else if (e.type == SDL_MOUSEMOTION)
	{
		//mouse_move_editor(&(e.motion), ed);
		flags->y = 1;
	}
	else if (e.type == SDL_MOUSEWHEEL)
	{
		//mouse_weel_editor(e.wheel.y, ed);
		flags->y = 1;
	}
}