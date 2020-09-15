/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/09/15 08:59:55 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	def_walltile(t_map *map, t_drawer *drawer)
{
	int	n;

	drawer->barrier_d[0] = drawer->barrier_f[0][0];
	drawer->barrier_d[1] = drawer->barrier_f[0][1];
	n = map->elem[drawer->barrier_d[1]][drawer->barrier_d[0]].number;
	drawer->wall_tile = n;
}

int		check_start(t_game *game)
{
	if (game->comeback == 0)
	{
		if (game->level.num > MAX_LEVEL || game->level.num <= 0)
			game->level.num = 1;
		if (!load_map(&game->level, &game->player))
		{
			ft_putstr("Not valid map!\n");
			return (0);
		}
		game->delay = 10;
	}
	return (1);
}

void	set_color(SDL_Color *col, int r, int g, int b)
{
	col->r = r;
	col->g = g;
	col->b = b;
}

int		clamp_col(int col)
{
	if (col < 0)
		return (0);
	if (col > 255)
		return (255);
	return (col);
}
