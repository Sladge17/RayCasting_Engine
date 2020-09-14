/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/09/10 17:51:32 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		reformat(int *data_img, SDL_Surface *image, SDL_PixelFormat *fmt)
{
	int	i;
	int	j;
	int	index;
	SDL_Color	col;
	
	j = -1;
	while (++j < image->h)
	{
		i = -1;
		while (++i < image->w)
		{
			index = j * image->w + i;
			col.r = (data_img[index] & 0xFF0000)>>16;
			col.g = (data_img[index] & 0xFF00)>>8;
			col.b = (data_img[index] & 0xFF);
			data_img[index] = (col.b << fmt->Bshift) | (col.g << fmt->Gshift) | (col.r << fmt->Rshift);
		}
	}
}

SDL_Surface	*load_s_image(t_game *game, const char *file)
{
	SDL_Rect	screen;
	SDL_Rect	image;
	SDL_Surface	*s;
	SDL_Surface	*im;

	screen.x = 0;
	screen.y = 0;
	screen.w = game->surf->w;
	screen.h = game->surf->h;
	s = IMG_Load(file);
	if (!s)
		return (0);
	image.x = 0;
	image.y = 0;
	image.w = s->w;
	image.h = s->h;
	im = SDL_CreateRGBSurface(s->flags, screen.w, screen.h,
		s->format->BitsPerPixel, s->format->Rmask, s->format->Gmask,
		s->format->Bmask, s->format->Amask);
	if ((SDL_BlitScaled(s, &image, im, &screen)))
		return (0);
	SDL_FreeSurface(s);
	return (im);
}

int		init_sdl(t_game *game)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) //|SDL_INIT_AUDIO
		return (ERROR);
	
	if (TTF_Init() == -1)
		return (ERROR);
	game->win = 0;
	game->win = SDL_CreateWindow("wolf3d", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, S_W, S_H, SDL_WINDOW_SHOWN);
	if (!game->win)
		return (ERROR);
	game->surf = SDL_GetWindowSurface(game->win);
	if (!game->surf)
		return (ERROR);
	game->data = (int *)game->surf->pixels;
	game->draw_map = 0;
	game->fps = 50;
	game->f_time = 1000 / game->fps;
	game->last_time = SDL_GetTicks();
	game->athlas = IMG_Load("res/athlas2.png");
	game->level.num = 1;
	game->cheat = 0;
	load_music(game);
	if (!game->athlas ||
	!(game->menu = load_s_image(game, "res/main_screen.png")) ||
	!(game->n_level = load_s_image(game, "res/next_level.png")) ||
	!(game->s_win = load_s_image(game, "res/win.png")))
		return (ERROR);
	game->data_img = (int *)game->athlas->pixels;
	game->data_menu = (int *)game->menu->pixels;
	game->data_n_level = (int *)game->n_level->pixels;
	game->data_win = (int *)game->s_win->pixels;
	
	reformat(game->data_img, game->athlas, game->athlas->format);
	reformat(game->data_menu, game->menu, game->menu->format);
	reformat(game->data_n_level, game->n_level, game->n_level->format);
	reformat(game->data_win, game->s_win, game->s_win->format);
	return (OK);
}
