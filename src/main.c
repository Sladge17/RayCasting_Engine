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




void		*draw_line(void *g)
{
	t_isec	isec;
	SDL_Color	*floor;
	SDL_Color	*roof;
	t_game	*game;
	int		x;
	int		y;

	game = (t_game*)g;
	roof = &(game->level.roof);
	floor = &(game->level.floor);
	x = -H_W + game->thread * S_W / THREADS - 1;
	while (++x < -H_W + (game->thread + 1) * S_W / THREADS)
	{
		engine(game, &isec, x);
		y = -H_H - 1;
		while (++y < -isec.height)
			game->data[(S_H - y - H_H - 1) * S_W + x + H_W] =
		(roof->r << 16) + (roof->g << 8) + roof->b;
		while (++y < isec.height)
			game->data[(S_H - y - H_H - 1) * S_W + x + H_W] =
		(255 << 16) + (255 << 8) + 255;
		while (++y < H_H)
			game->data[(S_H - y - H_H - 1) * S_W + x + H_W] =
		(floor->r << 16) + (floor->g << 8) + floor->b;
		
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
	init_player(game);
	load_map(&(game->level));
	if (!init_sdl(game))
			return (free_init_sdl(game));
	ft_putstr("Hello wolf\n");
	sdl_cycle(game);
	close_sdl(game);
	return (0);
}


