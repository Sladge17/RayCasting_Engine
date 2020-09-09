/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 17:49:36 by jthuy             #+#    #+#             */
/*   Updated: 2020/09/09 16:05:06 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	draw_sprite(t_game *game, t_sprt *sprite)
{
	def_spriteparam(game, sprite);
	sprite->cursor[0] = 0;
	while (sprite->cursor[0] < sprite->size)
	{
		if (sprite->offset[0] + sprite->cursor[0] < 0 ||
			sprite->offset[0] + sprite->cursor[0] >= S_W)
		{
			sprite->cursor[0] += 1;
			continue;
		}
		sprite->pix_pos[0] = (65 * (sprite->cursor[0] / (double)sprite->size));
		draw_vertline(game, sprite);
		sprite->cursor[0] += 1;
	}
}

void	def_spriteparam(t_game *game, t_sprt *sprite)
{
	int	dist;

	sprite->dist2[0] = sprite->pos.x - game->player.obj.pos.x;
	sprite->dist2[1] = sprite->pos.y - game->player.obj.pos.y;
	sprite->rot = atan2(sprite->dist2[0], sprite->dist2[1]);
	while (sprite->rot - game->player.obj.rot > M_PI)
		sprite->rot -= PI2;
	while (sprite->rot - game->player.obj.rot < -M_PI)
		sprite->rot += PI2;
	dist = sprite->dist2[0] * sprite->dist2[0] + sprite->dist2[1] * sprite->dist2[1];
	
	sprite->dir = sprite->rot - game->player.obj.rot;
	sprite->dist = sqrt(dist);// + dist.y;//sqrt(pow(sprite->dist2[0], 2) + pow(sprite->dist2[1], 2));
	sprite->size = (int)(S_H * 2 / sprite->dist);
	if (sprite->size > S_H * 4)
		sprite->size = S_H * 4;
	sprite->offset[0] = S_W / 2 - sprite->size / 2 -
		(sprite->dir * (S_W) / (game->player.sec.fov));
	sprite->offset[1] = S_H / 2 - sprite->size / 2;
	sprite->tile = 65 * (sprite->numb % 16 + sprite->numb / 16 * 1039);
}

void	draw_vertline(t_game *game, t_sprt *sprite)
{
	sprite->cursor[1] = 0;
	while (sprite->cursor[1] < sprite->size)
	{
		if (sprite->offset[1] + sprite->cursor[1] < 0 ||
			sprite->offset[1] + sprite->cursor[1] >= S_H)
		{
			sprite->cursor[1] += 1;
			continue;
		}
		sprite->pix_pos[1] = (65 * (sprite->cursor[1] / (double)sprite->size));
		sprite->pix_win = sprite->offset[0] + sprite->cursor[0] +
			S_W * (sprite->offset[1] + sprite->cursor[1]);
		sprite->pix_img = sprite->tile + sprite->pix_pos[0] +
			1039 * sprite->pix_pos[1];
		if (game->data_img[sprite->pix_img] != 0x980088 &&
			sprite->pix_pos[0] != 64 && sprite->pix_pos[1] != 64 &&
			sprite->dist < game->z_buffer[sprite->pix_win])
		{
			game->data[sprite->pix_win] = game->data_img[sprite->pix_img];
			game->z_buffer[sprite->pix_win] = sprite->dist;
		}
		sprite->cursor[1] += 1;
	}
}

void	draw_sprites(t_game *game)
{
	t_sprt	s;
	int		i;

	i = -1;
	while (++i < 128)
	{
		if (i < game->level.map.enms)
			draw_sprite(game, &game->level.map.enm[i].sprt);
		if (i < game->level.map.bars)
			draw_sprite(game, &game->level.map.bar[i].sprt);
	}
}
