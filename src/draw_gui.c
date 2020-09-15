/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_gui.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/09/15 13:41:03 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	draw_gun(t_game *game, t_drawer *dr, int tile_u, int tile_v)
{
	dr->cursor[0] = -1;
	while (++dr->cursor[0] < (S_H - GUN_SCALE))
	{
		dr->cursor[1] = -1;
		while (++dr->cursor[1] < (S_H - GUN_SCALE))
		{
			dr->tex_d[0] = (dr->cursor[0] /
				(double)(S_H - GUN_SCALE)) * 64;
			dr->tex_d[1] = (dr->cursor[1] /
				(double)(S_H - GUN_SCALE)) * 64;
			dr->pix_img =
				dr->tex_d[0] + 1039 * dr->tex_d[1] +
				(64 * tile_u) + (67535 * tile_v);
			if (game->data_img[dr->pix_img] != 0x980088)
				game->data[dr->cursor[0] +
				(S_W - S_H + GUN_SCALE) / 2 +
				S_W * (dr->cursor[1] + GUN_SCALE - 64)] =
				game->data_img[dr->pix_img];
		}
	}
}

void	draw_face(t_game *game, t_drawer *dr, int tile_u, int tile_v)
{
	dr->cursor[0] = -1;
	while (++dr->cursor[0] < 64)
	{
		dr->cursor[1] = -1;
		while (++dr->cursor[1] < 64)
			if (game->data_img[dr->cursor[0] + 65 * tile_u +
				1039 * (dr->cursor[1] + 65 * tile_v)] != 0x980088)
				game->data[dr->cursor[0] + (S_W - 64) / 2 +
				S_W * (dr->cursor[1] + S_H - 64)] =
					game->data_img[dr->cursor[0] +
					65 * (tile_u) +
					1039 * (dr->cursor[1] + 65 * tile_v)];
	}
}

void	draw_back(t_game *game, t_drawer *dr, int tile_u, int tile_v)
{
	SDL_Point	p;
	SDL_Point	m;

	dr->cursor[0] = -1;
	m.x = S_H * S_W;
	m.y = game->athlas->w * game->athlas->h;
	while (++dr->cursor[0] < S_W)
	{
		dr->cursor[1] = -1;
		while (++dr->cursor[1] < 65)
		{
			p.x = dr->cursor[0] + S_W * (dr->cursor[1] + S_H - 64);
			p.y = dr->cursor[0] % 64 + 65 * tile_u + 1039 * (dr->cursor[1]
				+ 64 * tile_v);
			if (p.x >= 0 && p.x < m.x && p.y >= 0 && p.y < m.y)
				game->data[p.x] = game->data_img[p.y];
		}
	}
}

void	draw_uitext(t_game *game, SDL_Rect *pos)
{
	char level[9];

	pos->x = H_W + 40;
	pos->y = S_H - 60;
	print_ttf(game->surf, "WASD/Arrow - move/turn", 16, pos);
	pos->y += 20;
	print_ttf(game->surf, "     Space - action", 16, pos);
	pos->y += 20;
	print_ttf(game->surf, "         M - on/off map", 16, pos);
	pos->x = 50;
	pos->y = S_H - 64;
	ft_strcpy(level, "level 00");
	level[6] = game->level.num / 10 + '0';
	level[7] = game->level.num % 10 + '0';
	print_wolf(game->surf, level, pos, 54);
}

void	draw_gui(t_game *game)
{
	t_drawer		dr;
	SDL_Rect		pos;

	draw_gun(game, &dr, 0, 33);
	draw_back(game, &dr, 0, 1);
	if (((SDL_GetTicks() / 1000) % 4))
		draw_face(game, &dr, 4, 42);
	else
		draw_face(game, &dr, 3, 42);
	draw_uitext(game, &pos);
	pos.x = 50;
	pos.y = S_H - 40;
}
