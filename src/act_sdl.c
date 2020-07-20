/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   act_sdl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/07/20 18:18:50 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	close_sdl(t_game *game)
{
	SDL_FreeSurface(game->surf);
	game->surf = 0;
	SDL_DestroyWindow(game->win);
	game->win = 0;
	TTF_Quit();
	SDL_Quit();
}

void	sld_events2(t_game *game, SDL_Event e, int *repaint)
{
	if (e.type == SDL_MOUSEMOTION)
	{
		mouse_move(&(e.motion), game);
		if (game->status)
			*repaint = 1;
	}
	else if (e.type == SDL_MOUSEWHEEL)
	{
		mouse_weel(e.wheel.y, game);
		*repaint = 1;
	}
}

void	sld_events1(t_game *game, SDL_Event e, int *quit, int *repaint)
{
	if (e.type == SDL_QUIT)
		*quit = 1;
	else if (e.type == SDL_KEYDOWN)
	{
		if (e.key.keysym.sym == SDLK_ESCAPE)
			*quit = 1;
		else
		{
			if (key_press(e.key.keysym.sym, game))
				*repaint = 1;
			else
			{
				SDL_UpdateWindowSurface(game->win);
			}
		}
	}
	else if (e.type == SDL_MOUSEBUTTONDOWN)
	{
		mouse_press(&(e.button), game);
		*repaint = 1;
	}
}

void	sdl_cycle(t_game *game)
{
	int			quit;
	SDL_Event	e;
	int			repaint;
	int			first;

	quit = 0;
	first = 1;
	while (!quit)
	{
		repaint = 0;
		if (SDL_PollEvent(&e) != 0 || repaint)
		{
			sld_events1(game, e, &quit, &repaint);
			sld_events2(game, e, &repaint);
			if (repaint || first)
			{
				run(game);
				printf("x=%f,y=%f\n", game->player.obj.pos.x, game->player.obj.pos.y);
				SDL_UpdateWindowSurface(game->win);
				first = 0;
			}
		}
	}
}
