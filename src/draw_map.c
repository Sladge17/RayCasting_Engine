/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/09/05 17:44:19 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		draw_rect(t_game *game, SDL_Point p, int d, int n)
{
	SDL_Color col;
	int y_index;
	int max;
	int i;
	int j;
	
	max = game->surf->w * game->surf->h;
	set_col_by_num(&col, n);
	j = p.y * d - 1;
	while (++j < (p.y + 1) * d)
	{
		y_index = j * game->surf->w;
		i = p.x * d - 1;
		while (++i < (p.x + 1) * d)
		{
			if (y_index + i < max)
				game->data[y_index + i] = (col.r << 16) | (col.g << 8) | col.b;
		}
	}
}

void		draw_dot(t_game *game, t_vec2 *pos, int d, Uint32 col)
{
	int max;
	int i;
	int j;
	int rad;
	
	rad = 2;
	max = game->surf->w * game->surf->h;
	j = (int)((pos->y) * d) - rad - 1;
	while (++j <= (int)((pos->y) * d) + rad)
	{
		i = (int)((pos->x) * d) - rad - 1;
		while (++i <= (int)((pos->x) * d) + rad)
		{ 
			if (j * game->surf->w + i < max)
				game->data[j * game->surf->w + i] = col;
		}
	}
}

void		draw_line(t_game *game, t_vec2 *start, t_vec2 *end, int d)
{
	t_vec2 len;
	int steps;
	int max;
	int index;
	int i;
	
	max = game->surf->w * game->surf->h;
	len.x = (end->x - start->x) * d;
	len.y = (end->y - start->y) * d;
	steps = fabs(len.x) > fabs(len.y) ? (int)fabs(len.x) : (int)fabs(len.y);
	i = -1;
	while (++i < steps)
	{
		index = (int)(start->y * d + len.y * (float)i / steps) *
			game->surf->w + (int)(start->x * d + len.x * (float)i / steps);
		if (index > 0 && index < max)
			game->data[index] = 0xff00ffff;
	}
}

void		draw_player(t_game *game, int d)
{
	t_vec2	dir;
	
	dir.x = game->player.obj.pos.x + game->player.obj.dir.x;
	dir.y = game->player.obj.pos.y + game->player.obj.dir.y;
	draw_dot(game, &(game->player.obj.pos), d, 0xffff00ff);
	draw_line(game, &(game->player.obj.pos), &(dir), d);
}

void		draw_map(t_game *game)
{
	int d;
	int max;
	SDL_Point p;

	d = 10;
	max = game->surf->w * game->surf->h;
	p.y = -1;
	while (++p.y < 64)
	{
		p.x = -1;
		while (++p.x < 64)
		{
			if (game->level.map.elem[p.y][p.x].lock == 1)
				draw_rect(game, p, d, 
					game->level.map.elem[p.y][p.x].number);
		}
	}
	draw_player(game, d);
}
