/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/08/11 16:16:56 by vkaron           ###   ########.fr       */
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
		//((clamp_col((game->level.map.roof & 0xFF0000 >> 16) - (H_H + y) * g / H_H)) << 16) + 
		//((clamp_col((game->level.map.roof & 0xFF00 >> 8) - (H_H + y) * g / H_H)) << 8) + 
		//clamp_col((game->level.map.roof & 0xFF) - (H_H + y) * g / H_H);
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
		//((clamp_col((game->level.map.floor & 0xFF0000 >> 16) - (H_H - y) * g / H_H)) << 16) + 
		//((clamp_col((game->level.map.floor & 0xFF00 >> 8) - (H_H - y) * g / H_H)) << 8) + 
		//clamp_col((game->level.map.floor & 0xFF) - (H_H - y) * g / H_H);
	}
}

void		draw_walls(t_game *game, int x, t_isec *isec)
{
	int y;
	SDL_Color col;
	int index[2];
	int k;

	y = - 1;
	k = isec->dist * 1;
	while (++y <= isec->height * 2)
	{
		index[0] = (H_H - isec->height + y) * S_W + x;
		
		int im_y = isec->number / 16;
		int im_x = isec->number - im_y * 16;
		
		index[1] = ((y * 32 / isec->height) + im_y * 65) * game->athlas->w +
			isec->colum + (im_x * 65);
		
		if (index[0] < 0)
			index[0] = 0;
		if (index[1] < 0)
			index[1] = 0;
		if (index[0] > (S_W * S_H) - 1)
			index[0] = (S_W * S_H) - 1;
		if (index[1] > (game->athlas->w * game->athlas->h) - 1)
			index[1] = (game->athlas->w * game->athlas->h) - 1;
		//if (game->data_img[index[1]] == 0x980088)
		//	return ;
		set_color(&col, 
			clamp_col(((game->data_img[index[1]] & 0xff)) - k), 
			clamp_col(((game->data_img[index[1]] & 0xff00)>>8) - k),
			clamp_col(((game->data_img[index[1]] & 0xff0000)>>16) - k));
		game->data[index[0]] = (col.b << 16) | (col.g << 8) | col.r;
		//game->data_img[index[1]];
	}
}

void		*draw_block_3d(void *g)
{
	t_isec	isec;
	t_game	*game;
	int		x;
	int		x_index;
	int		max_x;

	game = (t_game*)g;
	x = -H_W + game->thread * S_W / THREADS - 1;
	max_x = -H_W + (game->thread + 1) * S_W / THREADS;
	while (++x < max_x)
	{
		engine(game, &isec, x);
		set_col_by_num(&(isec.col), isec.number);
		x_index =  (H_W - x);
		draw_roof(game, -H_H, x_index, -isec.height);
		draw_floor(game, isec.height, x_index, H_H - 1);
		draw_walls(game, x_index, &(isec));
	}
	return (0);
}

void		draw_game(t_game *game)
{
	t_game			data[THREADS];
	pthread_t		threads[THREADS];
	pthread_attr_t	attr;
	int				rc;
	void			*status;

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	game->thread= -1;
	while (++(game->thread) < THREADS)
	{
		ft_memcpy((void*)&data[game->thread], (void *)game, sizeof(t_game));
		rc = pthread_create(&threads[game->thread],
			NULL, draw_block_3d, (void *)(&data[game->thread]));
	}
	pthread_attr_destroy(&attr);
	game->thread = -1;
	while (++(game->thread) < THREADS)
		rc = pthread_join(threads[game->thread], &status);
	if (game->draw_map)
		draw_map(game);
	draw_gui(game);
}
