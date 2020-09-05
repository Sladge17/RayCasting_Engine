/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/09/05 19:51:14 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		draw_roof(t_game *game, int y, int x, int max_y)
{
	int g;

	g = 10;
	y = y - 1;
	while (++y <= max_y)
	{
		game->data[(H_H + y) * S_W + x] = game->level.map.roof;
	}
}

void		draw_floor(t_game *game, int y, int x, int max_y)
{
	int g;

	g = 10;
	y = y - 1;
	while (++y <= max_y)
	{
		game->data[(H_H + y) * S_W + x] = game->level.map.floor;
	}
}

void		draw_walls(t_game *game, int x, t_isec *isec)
{
	int			y;
	SDL_Color	col;
	int			index[2];
	int			k;
	SDL_Point	im;

	y = - 1;
	k = isec->dist * 1;
	while (++y <= isec->height * 2)
	{
		index[0] = (H_H - isec->height + y) * S_W + x;
		im.y = isec->number / 16;
		im.x = isec->number - im.y * 16;
		index[1] = ((y * 32 / isec->height) + im.y * 65) * game->athlas->w +
			isec->colum + (im.x * 65);
		if (index[0] < 0)
			index[0] = 0;
		if (index[1] < 0)
			index[1] = 0;
		if (index[0] > (S_W * S_H) - 1)
			index[0] = (S_W * S_H) - 1;
		if (index[1] > (game->athlas->w * game->athlas->h) - 1)
			index[1] = (game->athlas->w * game->athlas->h) - 1;
		set_color(&col, 
			clamp_col(((game->data_img[index[1]] & 0xff)) - k), 
			clamp_col(((game->data_img[index[1]] & 0xff00)>>8) - k),
			clamp_col(((game->data_img[index[1]] & 0xff0000)>>16) - k));
		game->data[index[0]] = (col.b << 16) | (col.g << 8) | col.r;
		game->z_buffer[index[0]] = isec->dist;
	}
}

void		*draw_block_3d(void *g)
{
	t_isec		isec;
	t_game		*game;
	SDL_Rect	ind;
	t_thread	*t;

	t = (t_thread*)g;
	game = t->game;
	ind.x = -H_W + t->thread * S_W / THREADS - 1;
	ind.h = -H_W + (t->thread + 1) * S_W / THREADS;
	while (++ind.x < ind.h)
	{
		engine(game, &isec, ind.x);
		set_col_by_num(&(isec.col), isec.number);
		ind.w = (H_W - ind.x);
		draw_roof(game, -H_H, ind.w, -isec.height);
		draw_floor(game, isec.height, ind.w, H_H - 1);
		draw_walls(game, ind.w, &(isec));
	}
	return (0);
}

void		draw_game(t_game *game)
{
	t_thread		data[THREADS];
	pthread_t		threads[THREADS];
	pthread_attr_t	attr;
	int				thread;
	void			*status;

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	thread= -1;
	while (++thread < THREADS)
	{
		data[thread].game = game;
		data[thread].thread = thread;
		pthread_create(&threads[thread],
			NULL, draw_block_3d, (void *)(&data[thread]));
	}
	pthread_attr_destroy(&attr);
	thread = -1;
	while (++thread < THREADS)
		pthread_join(threads[thread], &status);
	if (game->draw_map)
		draw_map(game);
	//draw_sprites(game);
}
