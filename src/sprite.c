/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 17:49:36 by jthuy             #+#    #+#             */
/*   Updated: 2020/09/15 10:40:47 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	draw_sprite(t_game *game, t_sprt *sprite)
{
	def_spriteparam(game, sprite);
	sprite->cursor.x = 0;
	while (sprite->cursor.x < sprite->size)
	{
		if (sprite->offset.x + sprite->cursor.x < 0 ||
			sprite->offset.x + sprite->cursor.x >= S_W)
		{
			sprite->cursor.x += 1;
			continue;
		}
		sprite->pix_pos.x = (65 * (sprite->cursor.x / (double)sprite->size));
		draw_vertline(game, sprite);
		sprite->cursor.x += 1;
	}
}

void	def_spriteparam(t_game *game, t_sprt *sprite)
{
	float	dist;

	sprite->dist2.x = sprite->pos.x - game->player.obj.pos.x;
	sprite->dist2.y = sprite->pos.y - game->player.obj.pos.y;
	sprite->rot = atan2(sprite->dist2.x, sprite->dist2.y);
	while (sprite->rot - game->player.obj.rot > M_PI)
		sprite->rot -= PI2;
	while (sprite->rot - game->player.obj.rot < -M_PI)
		sprite->rot += PI2;
	dist = sprite->dist2.x * sprite->dist2.x + sprite->dist2.y *
		sprite->dist2.y;
	sprite->dir = sprite->rot - game->player.obj.rot;
	sprite->dist = sqrt(dist);
	sprite->size = (S_W / (sprite->dist));
	if (sprite->size > S_H * 4)
		sprite->size = S_H * 4;
	sprite->offset.x = S_W / 2 - sprite->size / 2 -
		(sprite->dir * (S_W) / (game->player.sec.fov));
	sprite->offset.y = S_H / 2 - sprite->size / 2;
	sprite->tile = 65 * (sprite->numb % 16 + sprite->numb / 16 *
		game->athlas->w);
}

void	draw_vertline(t_game *game, t_sprt *sprite)
{
	sprite->cursor.y = 0;
	while (sprite->cursor.y < sprite->size)
	{
		if (sprite->offset.y + sprite->cursor.y < 0 ||
			sprite->offset.y + sprite->cursor.y >= S_H)
		{
			sprite->cursor.y += 1;
			continue;
		}
		sprite->pix_pos.y = (65 * (sprite->cursor.y / (double)sprite->size));
		sprite->pix_win = sprite->offset.x + sprite->cursor.x +
			S_W * (sprite->offset.y + sprite->cursor.y);
		sprite->pix_img = sprite->tile + sprite->pix_pos.x +
			1039 * sprite->pix_pos.y;
		if (game->data_img[sprite->pix_img] != 0x980088 &&
			sprite->pix_pos.x != 64 && sprite->pix_pos.y != 64 &&
			sprite->dist < game->z_buffer[sprite->pix_win])
		{
			game->data[sprite->pix_win] = game->data_img[sprite->pix_img];
			game->z_buffer[sprite->pix_win] = sprite->dist;
		}
		sprite->cursor.y += 1;
	}
}

void	draw_sprites(t_game *game)
{
	int		i;

	i = -1;
	while (++i < 128)
	{
		if (i < game->level.map.enms)
			draw_sprite(game, &game->level.map.enm[i].sprt);
		if (i < game->level.map.bars)
			draw_sprite(game, &game->level.map.bar[i].sprt);
		if (i < game->level.map.achs)
			draw_sprite(game, &game->level.map.ach[i].sprt);
		if (i < game->level.map.ants)
			draw_sprite(game, &game->level.map.ant[i].sprt);
	}
}
