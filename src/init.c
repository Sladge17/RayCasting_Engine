/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/07/20 15:59:16 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		reformat(t_game *game, SDL_PixelFormat *fmt)
{
	int	i;
	int	j;
	int	index;
	SDL_Color	col;
	
	j = -1;
	while (++j < game->athlas->h)
	{
		i = -1;
		while (++i < game->athlas->w)
		{
			index = j * game->athlas->w + i;
			col.r = (game->data_img[index] & 0xFF0000)>>16;
			col.g = (game->data_img[index] & 0xFF00)>>8;
			col.b = (game->data_img[index] & 0xFF);
			game->data_img[index] = (col.b << fmt->Bshift) | (col.g << fmt->Gshift) | (col.r << fmt->Rshift);
		}
	}
}

int		init_sdl(t_game *game)
{
	SDL_PixelFormat *fmt;

	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0)
		return (ERROR);
	
	if (TTF_Init() == -1)
		return (ERROR);
	game->win = 0;
	game->win = SDL_CreateWindow("WOLF", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, S_W, S_H, SDL_WINDOW_SHOWN);
	if (!game->win)
		return (ERROR);
	game->surf = SDL_GetWindowSurface(game->win);
	if (!game->surf)
		return (ERROR);
	game->data = (int *)game->surf->pixels;
	game->fps = 50;
	game->f_time = 1000 / game->fps;
	game->last_time = SDL_GetTicks();
	game->athlas = IMG_Load("res/athlas2.png");
	//printf("alias");
	if (!game->athlas)
		return (ERROR);
	game->data_img = (int *)game->athlas->pixels;
	fmt = game->athlas->format;
	reformat(game, fmt);
	

//printf("Pixel Color -> R: %d,  G: %d,  B: %d,  A: %d\n", fmt->Rshift, fmt->Gshift, fmt->Bshift, fmt->Ashift);


	
	return (OK);
}
