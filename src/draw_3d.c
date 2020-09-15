/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/09/15 11:17:52 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		check_index(t_game *game, int *index)
{
	if (index[0] < 0)
		index[0] = 0;
	if (index[1] < 0)
		index[1] = 0;
	if (index[0] > (S_W * S_H) - 1)
		index[0] = (S_W * S_H) - 1;
	if (index[1] > (game->athlas->w * game->athlas->h) - 1)
		index[1] = (game->athlas->w * game->athlas->h) - 1;
}

void		draw_walls(t_game *game, int x, t_isec *isec)
{
	int			y;
	SDL_Color	col;
	int			index[2];
	int			k;
	SDL_Point	im;

	y = -1;
	k = isec->dist * 1;
	while (++y <= isec->height * 2)
	{
		index[0] = (H_H - isec->height + y) * S_W + x;
		im.y = isec->number / 16;
		im.x = isec->number - im.y * 16;
		index[1] = ((y * 32 / isec->height) + im.y * 65) * game->athlas->w +
			isec->colum + (im.x * 65);
		check_index(game, index);
		set_color(&col,
			clamp_col(((game->data_img[index[1]] & 0xff)) - k),
			clamp_col(((game->data_img[index[1]] & 0xff00) >> 8) - k),
			clamp_col(((game->data_img[index[1]] & 0xff0000) >> 16) - k));
		game->data[index[0]] = (col.b << 16) | (col.g << 8) | col.r;
		game->z_buffer[index[0]] = isec->dist;
	}
}

void		*draw_block_3d(void *g)
{
	t_isec		isec;
	int			x;
	int			x_index;
	int			max_x;
	t_flow		*t;

	t = (t_flow*)g;
	x = -H_W + t->flow * S_W / THREADS;
	max_x = -H_W + (t->flow + 1) * S_W / THREADS;
	while (++x <= max_x)
	{
		engine(t->game, &isec, x);
		x_index = (H_W - x);
		draw_roof(t->game, -H_H, x_index, -isec.height);
		draw_floor(t->game, isec.height, x_index, H_H - 65);
		draw_walls(t->game, x_index, &(isec));
	}
	return (0);
}

void		draw_game(t_game *game)
{
	t_flow			data[THREADS];
	pthread_t		threads[THREADS];
	pthread_attr_t	attr;
	int				c_flow;
	void			*status;

	status = 0;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	c_flow = -1;
	while (++c_flow < THREADS)
	{
		data[c_flow].game = game;
		data[c_flow].flow = c_flow;
		pthread_create(&threads[c_flow],
			NULL, draw_block_3d, (void *)(&data[c_flow]));
	}
	pthread_attr_destroy(&attr);
	c_flow = -1;
	while (++c_flow < THREADS)
		pthread_join(threads[c_flow], &status);
	draw_sprites(game);
	if (game->draw_map)
		draw_map(game);
	draw_gui(game);
}
