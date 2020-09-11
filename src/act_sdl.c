/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   act_sdl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/09/10 19:07:28 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	check_start(t_game *game)
{
	if (game->comeback == 0)
	{
		if (game->level.num > game->max_level || game->level.num <= 0)
			game->level.num = 1;
		printf("level = %d\n", game->level.num);
		load_map(&game->level, &game->player);
		game->delay = 10;
	}
}

void	sld_events2(t_game *game, SDL_Event e, int *repaint)
{
	if (e.type == SDL_MOUSEBUTTONDOWN)
	{
		mouse_press(&(e.button), game);
		*repaint = 1;
	}
	else if (e.type == SDL_MOUSEMOTION)
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

void	sld_events(t_game *game, SDL_Event e, int *quit, int *repaint)
{
	if (e.type == SDL_QUIT)
	{
		*quit = 1;
		game->status = 0;
	}
	else if (e.type == SDL_KEYDOWN)
	{
		if (e.key.keysym.sym == SDLK_ESCAPE)
			*quit = 1;
		else
			key_press(e.key.keysym.sym, game);
	}
	else
		sld_events2(game, e, repaint);
}

void	redraw(t_game *game)
{
	//unsigned int	cur_time;
	int				i;

	//cur_time = SDL_GetTicks();
	////if (cur_time > game->last_time + game->f_time)
	//{
		i = -1;
		while (++i < S_W * S_H)
			game->z_buffer[i] = 100;
		draw_game(game);
		SDL_UpdateWindowSurface(game->win);
		SDL_FlushEvent(SDL_KEYDOWN);
	//	game->last_time = SDL_GetTicks();
	//}
}

void	sdl_cycle(t_game *game)
{
	SDL_Event	e;
	SDL_Point	flags;
	int			first;

	flags.x = 0;
	first = 1;
	check_start(game);
	//game->f_time = 100;
	while (!flags.x)
	{
		flags.y = 0;
		check_keyboard(game, 0.3, &(flags.x));
		redraw(game);
		if (SDL_PollEvent(&e) != 0 || flags.y)
			sld_events(game, e, &(flags.x), &(flags.y));
		if (flags.x)
			break ;
		if (game->delay != 10)
		{
			SDL_Delay(game->delay);
			game->delay = 10;
			check_start(game);
		}
	}
	if (game->status != 0 && game->status != 4)
		game->status = 3;
}
