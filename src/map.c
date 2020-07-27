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

void	load_map(t_level *level, t_player *pl)
{
	int i;
	int j;

	level->number = 1;
	level->roof.r = 255;
	level->roof.g = 255;
	level->roof.b = 55;
	
	level->floor.r = 15;
	level->floor.g = 255;
	level->floor.b = 255;
	
	
	
	level->map.width = 11;
	level->map.height = 18;
	level->map.max = level->map.width * level->map.height;
	if (!(level->map.elem = (t_map_elem *)ft_memalloc(
		sizeof(t_map_elem) * level->map.max)))
		ft_exit("Failed to alloc t_map_elem");
	
	///*
	j = -1;
	while (++j < level->map.height)
	{
		i = -1;
		while (++i < level->map.width)
		{
			level->map.elem[j * 10 + i].lock = 0;
			level->map.elem[j * 10 + i].number = 0;
			level->map.elem[j * 10 + i].side[0] = -1;
			level->map.elem[j * 10 + i].side[1] = -1;
			level->map.elem[j * 10 + i].side[2] = -1;
			level->map.elem[j * 10 + i].side[3] = -1;
			if (i == 0 || i == 9 || j == 0 || j == 9)
			{
				level->map.elem[j * 10 + i].lock = 1;
				level->map.elem[j * 10 + i].number = 0;
				level->map.elem[j * 10 + i].side[0] = 0;
				level->map.elem[j * 10 + i].side[1] = 0;
				level->map.elem[j * 10 + i].side[2] = 0;
				level->map.elem[j * 10 + i].side[3] = 0;
			}
		}		
	}
	//*/
	///*
	const char m[] ="22222222222"\
					"21001001012"\
					"20000+00002"\
					"20000000002"\
					"21000000012"\
					"21000000012"\
					"20000000002"\
					"20000000002"\
					"22000000012"\
					"21000000012"\
					"20000000002"\
					"20000000002"\
					"21000000012"\
					"21001110012"\
					"20010001002"\
					"20010901002"\
					"21010000012"\
					"22222222212";
					
	const char m2[] ="11111111111"\
					"20000000003"\
					"20000000003"\
					"20000000003"\
					"20000000003"\
					"20000000003"\
					"20000000003"\
					"20000000003"\
					"20000000003"\
					"11111111111";
	///*
	//const char m2[] = "
	
	int k = 0;
	char c;
	int n;
	char b;
	int x,y;
	
	c = m[k];
	//ft_putchar(c);
	n = c - '0';
	printf("n=%d\n",n);
	//*
	while (c)
	{
		//b = i + '0';
		//ft_putchar(b);
		if (c == '+')
		{
			y = k/level->map.width;
			x = k - y * level->map.width;
			pl->obj.pos.x = (float)x + 0.5;
			pl->obj.pos.y = (float)y + 0.5;
			n = 0;
		}
		else
			n = c - '0';
		//printf("n=%d, i=%d\n",n, i);
		if (n)
			level->map.elem[k].lock = 1;
		else
			level->map.elem[k].lock = 0;
		if (n == 9)
			n = 10;
		else
			n = n + 13;
		level->map.elem[k].number = n;
		level->map.elem[k].side[0] = n;
		level->map.elem[k].side[1] = n;
		level->map.elem[k].side[2] = n;
		level->map.elem[k].side[3] = n;
		k++;
		c = m[k];
	}
	
	k = 60;
	n = 3;
	level->map.elem[k].lock = 1;
	level->map.elem[k].number = n;
	level->map.elem[k].side[0] = n;
	level->map.elem[k].side[1] = n+1;
	level->map.elem[k].side[2] = n+2;
	level->map.elem[k].side[3] = n+3;
		
}
