/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/07/20 19:33:59 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		clamp_col(int col)
{
	if(col < 0)
		return (0);
	if(col > 255)
		return (255);
	return col;
}

void		set_col_by_num(SDL_Color *col, int number)
{
	if(number == 1)
		set_color(col, 255, 0, 0);
	else if(number == 2)
		set_color(col, 255, 255, 0);
	else if(number == 3)
		set_color(col, 0, 255, 255);
	else if(number == 4)
		set_color(col, 0, 0, 255);
	else if(number == 5)
		set_color(col, 255, 0, 255);
	else if(number == 6)
		set_color(col, 255, 128, 0);
	else if(number == 7)
		set_color(col, 0, 128, 255);
	else if(number == 8)
		set_color(col, 128, 128, 0);
	else if(number == 9)
		set_color(col, 255, 0, 128);
	else
		set_color(col, 255, 255, 255);
}

void		draw_part(t_game *game, int y, int x, int max_y, SDL_Color *col)
{
	y = y - 1;
	while (++y <= max_y)
	{
		game->data[(H_H + y) * S_W + x] =
		((clamp_col(col->r - 100 + y * 100 / H_H)) << 16) + 
		((clamp_col(col->g - 100 + y * 100 / H_H)) << 8) + 
		clamp_col(col->b - 100 + y * 100 / H_H);
	}
}

void		draw_walls(t_game *game, int x, t_isec *isec)
{
	int y;
	SDL_Color col;
	int index[2];

	y = - 1;
	while (++y <= isec->height * 2)
	{
		index[0] = (H_H - isec->height + y) * S_W + x;
		index[1] = (y * 32 / isec->height ) * game->athlas->w +
			isec->colum + (isec->number * 64) + isec->number;
		if (index[0] < 0)
			index[0] = 0;
		if (index[1] < 0)
			index[1] = 0;
		if (index[0] > (S_W * S_H) - 1)
			index[0] = (S_W * S_H) - 1;
		if (index[1] > (game->athlas->w * game->athlas->h) - 1)
			index[1] = (game->athlas->w * game->athlas->h) - 1;
		game->data[index[0]] = game->data_img[index[1]];
	}
}

void		draw_gui(t_game *game, int x_index)
{
	int i;
	int index1;
	int index2;
	unsigned int color;
	SDL_Color col;

	if (x_index < game->athlas->w)
	{
		i = -1;
		while (++i < 64)
		{
			index1 = (S_H - 64 + i) * S_W + x_index;
			index2 = i*(game->athlas->w) + x_index;
			if (index1 < 0)
				index1 = 0;
			if (index2 < 0)
				index2 = 0;
			if (index1 > (S_W * S_H) - 1)
				index1 = (S_W * S_H) - 1;
			if (index2 > (game->athlas->w * game->athlas->h) - 1)
				index2 = (game->athlas->w * game->athlas->h) - 1;
			color = game->data_img[index2];
			game->data[index1] = color;	
		}
	}
}

void		*draw_line(void *g)
{
	t_isec	isec;
	t_game	*game;
	int		x;
	int		x_index;

	game = (t_game*)g;
	x = -H_W + game->thread * S_W / THREADS - 1;
	while (++x < -H_W + (game->thread + 1) * S_W / THREADS)
	{
		engine(game, &isec, x);
		set_col_by_num(&(isec.col), isec.number);
		x_index = x + H_W;
		draw_part(game, -H_H, x_index, -isec.height,
			&(game->level.floor));
		draw_part(game, isec.height, x_index, H_H - 1,
			&(game->level.roof));
		draw_walls(game, x_index, &(isec));
		draw_gui(game, x_index);
	}
	return (0);
}

void		run2(t_game *game) // run without pthread
{
	draw_line((void *)game);
}

void		run(t_game *game)
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
			NULL, draw_line, (void *)(&data[game->thread]));
	}
	pthread_attr_destroy(&attr);
	game->thread = -1;
	while (++(game->thread) < THREADS)
		rc = pthread_join(threads[game->thread], &status);
}

int			main(int ac, char *av[])
{
	t_game		*game;
	int			cheat;

	if (ac == 2)
		cheat = ft_strcmp(av[1], "cheat");
	if (!(game = (t_game *)ft_memalloc(sizeof(t_game))))
		ft_exit("Failed to alloc t_game");
	load_music(game);
	init_player(game);
	load_map(&(game->level), &(game->player));
	if (!init_sdl(game))
			return (free_init_sdl(game));
	sdl_cycle(game);
	close_sdl(game);
	return (0);
}


