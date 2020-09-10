/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_gui.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/09/10 15:11:08 by vkaron           ###   ########.fr       */
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

void	draw_gui(t_game *game)
{
	static int	counter = 0;
	static char	shift = 0;
	t_drawer	dr;

	draw_gun(game, &dr, 0, 33);
	draw_back(game, &dr, 0, 1);
	draw_face(game, &dr, 3 + shift, 42);
	if (counter == 40)
	{
		shift ^= 1;
		counter = 0;
		return ;
	}
	counter += 1;
}






/*
void	draw_gui(t_game *game)
{
	draw_back(game, 0, 1);
	draw_face(game, 3, 42);
	draw_gun(game, 0, 33);
}

void	draw_back(t_game *game, int tile_u, int tile_v)
{
	int		cursor[2];

	cursor[0] = -1;
	while (++cursor[0] < S_W)
	{
		cursor[1] = -1;
		while (++cursor[1] < 65)
		{
			game->data[cursor[0] + S_W * (cursor[1] + S_H - 64)] =
				game->data_img[cursor[0] % 64 + 65 * tile_u +
				1039 * (cursor[1] + 64 * tile_v)];
		}
	}
}

void	draw_face(t_game *game, int tile_u, int tile_v)
{
	int			cursor[2];
	static int	counter = 0;
	static char	shift = 0;

	cursor[0] = -1;
	while (++cursor[0] < 64)
	{
		cursor[1] = -1;
		while (++cursor[1] < 64)
			if (game->data_img[cursor[0] + 65 * tile_u +
				1039 * (cursor[1] + 65 * tile_v)] != 0x980088)
				game->data[cursor[0] + (S_W - 64) / 2 +
				S_W * (cursor[1] + S_H - 64)] =
					game->data_img[cursor[0] + 65 * (tile_u + shift) +
					1039 * (cursor[1] + 65 * tile_v)];
	}
	if (counter == 100)
	{
		shift ^= 1;
		counter = 0;
		return ;
	}
	counter += 1;
}

void	draw_gun(t_game *game, int tile_u, int tile_v)
{
	int		cursor[2];
	int		texel[2];
	int		gun_scale;
	int		img_pix;

	gun_scale = 200;
	cursor[0] = -1;
	while (++cursor[0] < (S_H - gun_scale))
	{
		cursor[1] = -1;
		while (++cursor[1] < (S_H - gun_scale))
		{
			texel[0] = (cursor[0] / (double)(S_H - gun_scale)) * 64;
			texel[1] = (cursor[1] / (double)(S_H - gun_scale)) * 64;
			img_pix = texel[0] + 1039 * texel[1] +
				(64 * tile_u) + (67535 * tile_v);
			if (game->data_img[img_pix] != 0x980088)
				game->data[cursor[0] + (S_W - S_H + gun_scale) / 2 +
				S_W * (cursor[1] + gun_scale - 64)] =
				game->data_img[img_pix];
		}
	}
}

//*/
