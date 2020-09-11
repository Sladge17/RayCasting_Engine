/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_gui.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/09/11 15:19:56 by jthuy            ###   ########.fr       */
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
	dr->cursor[0] = -1;
	while (++dr->cursor[0] < S_W)
	{
		dr->cursor[1] = -1;
		while (++dr->cursor[1] < 65)
		{
			game->data[dr->cursor[0] +
				S_W * (dr->cursor[1] + S_H - 64)] =
				game->data_img[dr->cursor[0] % 64 + 65 * tile_u +
				1039 * (dr->cursor[1] + 64 * tile_v)];
		}
	}
}

void	draw_uitext(t_game *game, SDL_Rect* pos)
{
	pos->x = S_W / 2 + 100;
	pos->y = S_H - 55;
	print_ttf(game->surf, "w - move forward", 18, pos);
	pos->y += 25;
	print_ttf(game->surf, "s - move back", 18, pos);
	pos->x += 220;
	pos->y -= 25;
	print_ttf(game->surf, "a - move left", 18, pos);
	pos->y += 25;
	print_ttf(game->surf, "d - move right", 18, pos);
	pos->x += 200;
	pos->y -= 25;
	print_ttf(game->surf, "q - rot left", 18, pos);
	pos->y += 25;
	print_ttf(game->surf, "e - rot right", 18, pos);
	pos->x += 190;
	pos->y -= 25;
	print_ttf(game->surf, "m - on/off map", 18, pos);
	pos->y += 25;
	print_ttf(game->surf, "enter - action", 18, pos);
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
	if (S_W == 1920)
		draw_uitext(game, &pos);
	pos.x = 50;
	pos.y = S_H - 40;
	print_ttf(game->surf, game->map, 30, &pos);
}
