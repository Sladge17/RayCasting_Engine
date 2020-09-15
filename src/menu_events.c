/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/09/15 10:36:15 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	mouse_move_menu(SDL_MouseMotionEvent *e, t_game *game)
{
	game->menu_flag = 0;
	if (e->x > H_W + H_W / 2 - 10 && e->x < S_W - 10 && e->y > H_H - 20 &&
		e->y < S_H)
	{
		game->menu_flag = 1;
		game->menu_item = ((e->y - H_H + H_H / 2) * 5 / H_H) - 2;
	}
	if ((game->comeback == 0 && game->menu_item == 0) || game->menu_item > 4 ||
		game->menu_item < 0)
		game->menu_flag = 0;
}

void	mouse_up_menu(SDL_MouseButtonEvent *e, t_game *game, SDL_Point *flags)
{
	if (game->menu_flag && e->button == SDL_BUTTON_LEFT)
	{
		flags->x = 2;
		if (game->menu_item == 0)
			game->status = 1;
		else if (game->menu_item == 1)
		{
			game->level.num = 1;
			game->comeback = 0;
			game->status = 1;
		}
		else if (game->menu_item == 2)
			check_play_music(game);
		else if (game->menu_item == 3)
		{
			game->level.num = 1;
			game->comeback = 0;
			game->status = 2;
		}
		else if (game->menu_item == 4)
			flags->x = 1;
	}
}

void	sld_events_menu2(t_game *game, SDL_Event e, SDL_Point *flags)
{
	if (e.type == SDL_MOUSEBUTTONDOWN)
		flags->y = 1;
	else if (e.type == SDL_MOUSEBUTTONUP)
		mouse_up_menu(&(e.button), game, flags);
	else if (e.type == SDL_MOUSEMOTION)
	{
		mouse_move_menu(&(e.motion), game);
		flags->y = 1;
	}
	else if (e.type == SDL_MOUSEWHEEL)
		flags->y = 1;
}

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
	else
		sld_events_menu2(game, e, flags);
}
