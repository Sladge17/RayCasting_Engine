/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 17:49:36 by jthuy             #+#    #+#             */
/*   Updated: 2020/08/12 17:51:31 by jthuy            ###   ########.fr       */
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
	sprite->dist2[0] = sprite->pos.x - game->player.obj.pos.x;
	sprite->dist2[1] = sprite->pos.y - game->player.obj.pos.y;
	sprite->rot = atan2(sprite->dist2[0], sprite->dist2[1]);
	while (sprite->rot - (game->player.obj.rot * M_PI / 180)  > M_PI)
		sprite->rot -= 2 * M_PI; 
	while (sprite->rot - (game->player.obj.rot * M_PI / 180) < -M_PI)
		sprite->rot += 2 * M_PI;
	sprite->dir = sprite->rot - (game->player.obj.rot * M_PI / 180);
	sprite->dist = sqrt(pow(sprite->dist2[0], 2) + pow(sprite->dist2[1], 2));
	sprite->size = (int)(S_H * 2 / sprite->dist);
	if (sprite->size > 4000) // dont need if exist collision
		sprite->size = 4000;
	sprite->offset[0] = S_W / 2 - sprite->size / 2 -
		(sprite->dir * (S_W) / (game->player.sec.fov * M_PI / 180));
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
	// t_sprt s[3];

	// s[0].numb = 156;
	// s[0].pos.x = 8.5;
	// s[0].pos.y = 9.5;

	// s[1].numb = 115;
	// s[1].pos.x = 10.5;
	// s[1].pos.y = 10.5;
	
	// s[2].numb = 116;
	// s[2].pos.x = 15.5;
	// s[2].pos.y = 12.5;
	
	// int i = -1;
	// while (++i < 3)
	// {
	// 	draw_sprite(game, &s[i]);
	// }

	t_sprt s;
	
	s.numb = 156;
	s.pos.x = 8.5;
	s.pos.y = 9.5;
	draw_sprite(game, &s);

	s.numb = 115;
	s.pos.x = 10.5;
	s.pos.y = 10.5;
	draw_sprite(game, &s);

	s.numb = 116;
	s.pos.x = 15.5;
	s.pos.y = 12.5;
	draw_sprite(game, &s);
}