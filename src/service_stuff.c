/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   service_stuff.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/07/20 19:29:09 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	ft_exit(char *line)
{
	ft_putstr(line);
	ft_putchar('\n');
	exit(-1);
}

void	free_l(t_game *game)
{
	free(game);
}

int		free_init_sdl(t_game *game)
{
	close_sdl(game);
	free_l(game);
	ft_exit("BAD THINGS HAPPENING TO SDL");
	return (-1);
}

SDL_Color create_color(int r, int g, int b)
{
	SDL_Color col;

	col.r = r;
	col.g = g;
	col.b = b;
	return (col);
}
