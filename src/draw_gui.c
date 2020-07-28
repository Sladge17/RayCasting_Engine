/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_gui.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/07/27 18:29:03 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		draw_gui(t_game *game)
{
	int i;
	int x;
	int index0;
	int	index1;
	SDL_Color col;

	x = -1;
	while (++x < game->surf->w)
	{
		if (x < game->athlas->w)
		{
			i = -1;
			while (++i < 64)
			{
				index0 = (S_H - 64 + i) * S_W + x;
				index1 = i*(game->athlas->w) + x;
				if (index0 < 0)
					index0 = 0;
				if (index1 < 0)
					index1 = 0;
				if (index0 > (S_W * S_H) - 1)
					index0 = (S_W * S_H) - 1;
				if (index1 > (game->athlas->w * game->athlas->h) - 1)
					index1 = (game->athlas->w * game->athlas->h) - 1;
				game->data[index0] = game->data_img[index1];	
			}
		}
	}
}
