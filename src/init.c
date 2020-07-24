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

int		init_sdl(t_game *game)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		return (ERROR);
	if (TTF_Init() == -1)
		return (ERROR);
		
	// load support for the JPG and PNG image formats
	//int flags=IMG_INIT_JPG|IMG_INIT_PNG;
	//int initted=IMG_Init(IMG_INIT_PNG);//flags);
	//printf("inited img=%d\n"+initted);
	//if((initted) != 1)
	//{
		
	//	return (ERROR);
	//}
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
	return (OK);
}
