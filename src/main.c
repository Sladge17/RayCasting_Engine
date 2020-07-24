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



void		*draw_line(void *g)
{
	t_isec	isec;
	SDL_Color	*floor;
	SDL_Color	*roof;
	t_game	*game;
	int		x;

	game = (t_game*)g;
	roof = &(game->level.roof);
	floor = &(game->level.floor);
	x = -H_W + game->thread * S_W / THREADS - 1;
	while (++x < -H_W + (game->thread + 1) * S_W / THREADS)
	{

		engine(game, &isec, x);
		if (isec.height > H_H)
			isec.height = H_H;
		set_col_by_num(&(isec.col), isec.number);
		int x_index = x + H_W;
		draw_part(game, -H_H, x_index, -isec.height, floor);
		draw_part(game, -isec.height, x_index, isec.height, &(isec.col));
		draw_part(game, isec.height, x_index, H_H, roof);
		if (x_index < game->athlas->w)
		{
			for (int i = 0; i < 64; i++)
			{
				game->data[(S_H - 64 + i) * S_W + x_index] = 
				game->data_img[i*(game->athlas->w) + x_index];
			}
		}
	}
	
	return (0);
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
		//write(1,"in->",4);
		ft_memcpy((void*)&data[game->thread], (void *)game, sizeof(t_game));
		rc = pthread_create(&threads[game->thread],
			NULL, draw_line, (void *)(&data[game->thread]));
		//write(1,"out\n",4);
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
	init_player(game);
	load_map(&(game->level));
	if (!init_sdl(game))
			return (free_init_sdl(game));
	//ft_putstr("Hello wolf\n");
	sdl_cycle(game);
	close_sdl(game);
	return (0);
}


