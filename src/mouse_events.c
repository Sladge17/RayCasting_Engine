/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/09/15 10:36:50 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		close_window(void *game)
{
	(void)game;
	exit(0);
}

void	mouse_move(SDL_MouseMotionEvent *e, t_game *game)
{
	game->dummy = e->x;
}

void	mouse_weel(Sint32 y, t_game *game)
{
	if (y < 0)
		game->dummy = 1;
}

void	mouse_press(SDL_MouseButtonEvent *e, t_game *game)
{
	game->dummy = e->x;
}
