/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/07/27 18:20:52 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

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


