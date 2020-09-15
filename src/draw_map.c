/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/09/15 08:58:11 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		draw_rect(t_game *game, t_ivec4 p, int d, int n)
{
	int			y_index;
	SDL_Point	ind;

	ind.y = p.b * d - p.d - 1;
	while (++ind.y < (p.b + 1) * d - p.d - 1)
	{
		if (ind.y >= H_H || ind.y < 0)
			continue ;
		y_index = ind.y * game->surf->w;
		ind.x = p.a * d - 1 - p.c;
		while (++ind.x < (p.a + 1) * d - p.c - 1)
		{
			if (ind.x >= H_W || ind.x < 0)
				continue ;
			game->data[y_index + ind.x] =
				game->data_img[(((n / 16) * 65) + 1) * game->athlas->w +
					(n % 16) * 65 + 1];
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
	max = S_W * S_H;
	j = (int)((pos->y) * scale) - rad - 1 - p.d;
	while (++j <= (int)((pos->y) * scale) + rad - p.d)
	{
		i = (int)((pos->x) * scale) - rad - 1 - p.c;
		while (++i <= (int)((pos->x) * scale) + rad - p.c)
		{
			if ((j * game->surf->w + i) < max)
				game->data[j * game->surf->w + i] = 0xffff00ff;
		}
	}
}

void		draw_line(t_game *game, t_vec2 *start, int scale, t_ivec4 p)
{
	t_vec2		len;
	SDL_Point	tool;
	SDL_Point	ind;
	t_vec2		end;
	SDL_Point	pos;

	end.x = game->player.obj.pos.x + game->player.obj.dir.x;
	end.y = game->player.obj.pos.y + game->player.obj.dir.y;
	tool.x = game->surf->w * game->surf->h;
	len.x = (end.x - start->x) * scale;
	len.y = (end.y - start->y) * scale;
	tool.y = fabs(len.x) > fabs(len.y) ? (int)fabs(len.x) : (int)fabs(len.y);
	ind.x = -1;
	while (++ind.x < tool.y)
	{
		pos.x = (int)(start->x * scale + len.x * (float)ind.x / tool.y) - p.c;
		pos.y = (int)(start->y * scale + len.y * (float)ind.x / tool.y) - p.d;
		if (pos.x < 0 || pos.x >= H_W || pos.y < 0 || pos.y >= H_H)
			continue ;
		ind.y = pos.y * S_W + pos.x;
		if (ind.y > 0 && ind.y < tool.x)
			game->data[ind.y] = 0xff00ffff;
	}
}

void		draw_fon(t_game *game)
{
	SDL_Point	pos;
	int			y_index;
	Uint32		col;
	SDL_Color	sc;

	pos.y = -1;
	while (++pos.y < H_H)
	{
		y_index = pos.y * S_W;
		pos.x = -1;
		while (++pos.x < H_W)
		{
			col = game->data[y_index + pos.x];
			sc.r = ((col & 0xFF0000) >> 16) / 2;
			sc.g = ((col & 0xFF00) >> 8) / 2;
			sc.b = (col & 0xFF) / 2;
			game->data[y_index + pos.x] = (sc.r << 16) | (sc.g << 8) | sc.b;
		}
	}
}

void		draw_map(t_game *game)
{
	int		scale;
	t_ivec4	p;

	scale = 20;
	p.c = 0;
	p.d = 0;
	draw_fon(game);
	p.b = -1;
	if ((int)(game->player.obj.pos.x * scale) > (H_W - scale * 2))
		p.c = game->player.obj.pos.x * scale - H_W + scale * 2;
	if ((int)(game->player.obj.pos.y * scale) > (H_H - scale * 2))
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
	draw_dot(game, &(game->player.obj.pos), scale, p);
	draw_line(game, &(game->player.obj.pos), scale, p);
}
