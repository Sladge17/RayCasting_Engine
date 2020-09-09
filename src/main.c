/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/09/09 12:27:21 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		main_selector(t_game *game)
{
	double		*z_buffer;//[S_W * S_H];
	
	game->z_buffer = 0;
	if (!(z_buffer = (double*)ft_memalloc(sizeof(double) * S_W * S_H)))
		return ;
	game->z_buffer = z_buffer;
	while (game->status > 0) {
		if (game->status == 1)
		{
			//load_music(game);
			sdl_cycle(game);
		}
		else if (game->status == 2)
			map_editor(game);
		else if (game->status == 3)
			main_menu(game);
		else if (game->status == 4)
		{
			printf("U WIN!!!\n");
			break ;
		}
	}
	
	if (z_buffer)
		free(z_buffer);
	
	game->z_buffer = 0;
	
}

int			main(int ac, char *av[])
{
	t_game		*game;
	int			cheat;
	int			status;
	//double		z_buffer[S_W * S_H];
	
	status = 3;
	if (S_W < 640 || S_H < 480)// || S_W * S_H > 960000)
		ft_exit("Bad resolution! Use from 640x480 to 1200x800!");
	if (ac == 2) {
		cheat = ft_strcmp(av[1], "cheat");
		if (!ft_strcmp(av[1], "editor"))
			status = 2;
	}
	if (!(game = (t_game*)ft_memalloc(sizeof(t_game))))
		ft_exit("Memory was not allocated!");
	init_player(game);
	//load_map(&game->level, &game->player);
	if (!init_sdl(game))
		return (free_init_sdl(game));
	game->status = status;
	main_selector(game);
	
	close_sdl(game);
	
	if (game)
		free(game);
	
	
	return (0);
}


