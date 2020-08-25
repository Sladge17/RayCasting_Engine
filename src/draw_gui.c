/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_gui.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/08/25 16:35:00 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		draw_gui(t_game *game)
{
	SDL_Point	p;
	int			index[2];
	SDL_Color	col;

	p.x = -1;
	while (++p.x < game->surf->w)
	{
		if (p.x >= game->athlas->w)
			continue;
		p.y = -1;
		while (++p.y < 64)
		{
			index[0] = (S_H - 64 + p.y) * S_W + p.x;
			index[1] = p.y * (game->athlas->w) + p.x;
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
}
