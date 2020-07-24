/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/07/20 19:43:59 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	load_map(t_level *level)
{
	int i;
	int j;

	level->number = 1;
	level->roof.r = 255;
	level->roof.g = 55;
	level->roof.b = 55;
	level->floor.r = 155;
	level->floor.g = 155;
	level->floor.b = 255;
	if (!(level->map = (t_map *)ft_memalloc(sizeof(t_map) * 100)))
		ft_exit("Failed to alloc t_map");
	j = -1;
	while (++j < 10)
	{
		i = -1;
		while (++i < 10)
		{
			if (!(level->map[j * 10 + i].elem = (t_map_elem *)ft_memalloc(sizeof(t_map_elem))))
				ft_exit("Failed to alloc t_map");
			level->map[j * 10 + i].elem->lock = 0;
			level->map[j * 10 + i].elem->number = 0;
			if (i == 0 || i == 9 || j == 0 || j == 9)
			{
				level->map[j * 10 + i].elem->lock = 1;
				level->map[j * 10 + i].elem->number = j;
			}
		}		
	}
	level->map[33].elem->lock = 1;
	level->map[33].elem->number = 4;
}
