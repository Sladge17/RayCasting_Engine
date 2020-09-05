/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   act_sdl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/09/05 18:06:57 by vkaron           ###   ########.fr       */
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

void	sld_events(t_game *game, SDL_Event e, int *quit, int *repaint)
{
	if (e.type == SDL_QUIT)
		*quit = 1;
	else if (e.type == SDL_KEYDOWN)
	{
		if (e.key.keysym.sym == SDLK_ESCAPE)
			*quit = 1;
		else
			key_press(e.key.keysym.sym, game);
	}
	else if (e.type == SDL_MOUSEBUTTONDOWN)
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

void	check_keyboard(t_game *game, float d_time)
{
	const	Uint8 *state = SDL_GetKeyboardState(NULL);

	if (state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_W])
		move_forward(&(game->player.obj), &game->level.map, d_time);
	else if (state[SDL_SCANCODE_DOWN] || state[SDL_SCANCODE_S])
		move_back(&(game->player.obj), &game->level.map, d_time);
	if (state[SDL_SCANCODE_LEFT])
		turn_left(&(game->player.obj), d_time);
	else if (state[SDL_SCANCODE_RIGHT])
		turn_right(&(game->player.obj), d_time);
	if (state[SDL_SCANCODE_A])
		move_left(&(game->player.obj), &game->level.map, d_time);
	else if (state[SDL_SCANCODE_D])
		move_right(&(game->player.obj), &game->level.map, d_time);
}

void	redraw(t_game *game, int *fps)
{
	unsigned int	cur_time;
	int				i;

	cur_time = SDL_GetTicks();
	if (cur_time > game->last_time + game->f_time)
	{
		i = -1;
		while (++i < S_W * S_H)
			game->z_buffer[i] = 100;
		draw_game(game);
		SDL_UpdateWindowSurface(game->win);
		SDL_FlushEvent(SDL_KEYDOWN);
		game->last_time = cur_time;
		*fps += 1;
	}
}

void	sdl_cycle(t_game *game)
{
	SDL_Rect	flags;
	SDL_Rect	time;
	float		d_time;
	SDL_Event	e;

	flags.x = 0;
	flags.h = 1;
	time.x = 0;
	time.y = SDL_GetTicks();
	while (!(flags.x))
	{
		d_time = (float)(SDL_GetTicks() - time.h) / 1000.0;
		if ((time.h = SDL_GetTicks()) > (time.y + 1000))
		{
			time.y = time.h;
			time.x = 0;
		}
		flags.y = 0;
		check_keyboard(game, d_time);
		redraw(game, &(time.x));
		if (SDL_PollEvent(&e) != 0 || flags.y)
			sld_events(game, e, &(flags.x), &(flags.y));
		SDL_Delay(10);
	}
	game->status = 3;
}
