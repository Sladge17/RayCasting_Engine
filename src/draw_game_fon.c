/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_game_fon.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/09/15 11:17:59 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		draw_roof(t_game *game, int y, int x, int max_y)
{
	y = y - 1;
	while (++y <= max_y)
		game->data[(H_H + y) * S_W + x] = game->level.map.roof;
}

void		draw_floor(t_game *game, int y, int x, int max_y)
{
	y = y - 1;
	while (++y <= max_y)
		game->data[(H_H + y) * S_W + x] = game->level.map.floor;
}
