/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/09/10 12:35:52 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		draw_rect(t_game *game, t_ivec4 p, int d, int n)
{
	int			y_index;
	int			ind[2];

	ind[1] = p.b * d - p.d - 1;
	while (++ind[1] < (p.b + 1) * d - p.d - 1)
	{
		if (ind[1] >= H_H || ind[1] < 0)
			continue ;
		y_index = ind[1] * game->surf->w;
		ind[0] = p.a * d - 1 - p.c;
		while (++ind[0] < (p.a + 1) * d - p.c - 1)
		{
			if (ind[0] >= H_W || ind[0] < 0)
				continue ;
			game->data[y_index + ind[0]] =
				game->data_img[(n / 16 + 1) * game->athlas->w + (n % 16) + 1];
		}
	}
}

void		draw_dot(t_game *game, t_vec2 *pos, int scale, t_ivec4 p)
{
	int max;
	int i;
	int j;
	int rad;

	rad = 2;
	max = game->surf->w * game->surf->h;
	j = (int)((pos->y) * scale) - rad - 1 - p.d;
	while (++j <= (int)((pos->y) * scale) + rad - p.d)
	{
		i = (int)((pos->x) * scale) - rad - 1 - p.c;
		while (++i <= (int)((pos->x) * scale) + rad - p.c)
		{
			if (j * game->surf->w + i < max)
				game->data[j * game->surf->w + i] = 0xffff00ff;
		}
	}
}

void		draw_line(t_game *game, t_vec2 *start, int scale, t_ivec4 p)
{
	
	t_vec2 len;
	int steps;
	int max;
	int index;
	int i;
	t_vec2	end;
	SDL_Point	pos;

	end.x = game->player.obj.pos.x + game->player.obj.dir.x;
	end.y = game->player.obj.pos.y + game->player.obj.dir.y;

	max = game->surf->w * game->surf->h;
	len.x = (end.x - start->x) * scale;
	len.y = (end.y - start->y) * scale;
	steps = fabs(len.x) > fabs(len.y) ? (int)fabs(len.x) : (int)fabs(len.y);
	i = -1;
	while (++i < steps)
	{
		pos.x = (int)(start->x * scale + len.x * (float)i / steps) - p.c;
		pos.y = (int)(start->y * scale + len.y * (float)i / steps) - p.d;
		if (pos.x < 0 || pos.x >= H_W || pos.y < 0 || pos.y >= H_H)
			continue ;
		index = pos.y * S_W + pos.x;
		if (index > 0 && index < max)
			game->data[index] = 0xff00ffff;
	}
}

void		draw_player(t_game *game, int scale, t_ivec4 p)
{
	
	draw_dot(game, &(game->player.obj.pos), scale, p);
	draw_line(game, &(game->player.obj.pos), scale, p);
}

void		draw_map(t_game *game)
{
	int		scale;
	t_ivec4	p;

	scale = 30;
	p.b = -1;
	if (game->player.obj.pos.x * scale > H_W - scale * 2)
		p.c = game->player.obj.pos.x * scale - H_W + scale * 2;
	if (game->player.obj.pos.y * scale > H_H - scale * 2)
		p.d = game->player.obj.pos.y * scale - H_H + scale * 2;
	while (++p.b < 64)
	{
		p.a = -1;
		while (++p.a < 64)
		{
			if (game->level.map.elem[p.b][p.a].lock == 1)
				draw_rect(game, p, scale,
					game->level.map.elem[p.b][p.a].number);
		}
	}
	draw_player(game, scale, p);
}
