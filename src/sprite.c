/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 16:24:05 by jthuy             #+#    #+#             */
/*   Updated: 2020/08/11 19:46:00 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	draw_sprite(t_game *game, t_sprt *sprite)//t_map *map, t_player *player, int *pixel, int *img, int sprite_poz, int tile_numb, double *z_buff)
{
	t_player *player = &game->player;
	int *pixel = game->data;
	int *img = game->data_img;
	double *z_buff = game->z_buffer;
	
	
	//t_sprite sprite;

	//sprite.x = sprite_poz % map->width + 0.5;
	//sprite.y = sprite_poz / map->width + 0.5;
	double rad = player->obj.rot * M_PI / 180;
	double fov_rad = player->sec.fov * M_PI / 180;
	// printf("%f\n", player->sec.fov);
	
	double	sprite_dir = atan2(sprite->pos.x - player->obj.pos.x, sprite->pos.y - player->obj.pos.y);
	//printf("d_alp=%.2f\n", sprite_dir * 180.0 / M_PI);
	while (sprite_dir - rad  > M_PI)
	 	sprite_dir -= 2 * M_PI; 
	while (sprite_dir - rad < -M_PI)
	 	sprite_dir += 2 * M_PI;
	
	double	sprite_dist = sqrt(pow(sprite->pos.x - player->obj.pos.x, 2) + pow(sprite->pos.y - player->obj.pos.y, 2));
	int		sprite_screen_size = (int)(S_H / sprite_dist) < 2000 ? (int)(S_H * 2 / sprite_dist) : 2000;
	
	
	
	double sp_dir_pl = sprite_dir - rad;
	int shift_x = S_W / 2 - (sp_dir_pl * (S_W) / (fov_rad));
	int h_offset = shift_x - sprite_screen_size / 2;

	int v_offset = S_H / 2 - sprite_screen_size / 2;

	int		cursor_x;
	int		cursor_y;
	cursor_x = 0;

	while (cursor_x < sprite_screen_size)
	{
		if (h_offset + cursor_x < 0 || h_offset + cursor_x >= S_W)
		{
			cursor_x += 1;
			continue;
		}
		cursor_y = 0;
		while (cursor_y < sprite_screen_size)
		{
			if (v_offset + cursor_y < 0 || v_offset + cursor_y >= S_H)
			{
				cursor_y += 1;
				continue;
			}
			if (img[(int)(65 * (cursor_x / (double)sprite_screen_size)) + 1039 * (int)(65 * (cursor_y / (double)sprite_screen_size)) + sprite->number % 16 * 65 + sprite->number / 16 * 1039 * 65] != 0x980088 &&
				(int)(65 * (cursor_x / (double)sprite_screen_size)) != 64 && (int)(65 * (cursor_y / (double)sprite_screen_size)) != 64 &&
				sprite_dist < z_buff[h_offset + cursor_x + S_W * (v_offset + cursor_y)])
			{
				pixel[h_offset + cursor_x + S_W * (v_offset + cursor_y)] = img[(int)(65 * (cursor_x / (double)sprite_screen_size)) + 1039 * (int)(65 * (cursor_y / (double)sprite_screen_size)) + sprite->number % 16 * 65 + sprite->number / 16 * 1039 * 65];
				z_buff[h_offset + cursor_x + S_W * (v_offset + cursor_y)] = sprite_dist;
			}
			cursor_y += 1;
		}
		cursor_x += 1;
	}
}

void	draw_sprites(t_game *game)
{
	t_sprt s[3];

	s[0].number = 156;
	s[0].pos.x = 8.5;
	s[0].pos.y = 9.5;

	s[1].number = 115;
	s[1].pos.x = 10.5;
	s[1].pos.y = 10.5;
	
	s[2].number = 116;
	s[2].pos.x = 15.5;
	s[2].pos.y = 12.5;
	
	int i = -1;
	while (++i < 3)//sprite_pos < map->width * map->height)
	{
		//if (map->field[sprite_pos] == 'B')
		draw_sprite(game, &s[i]);//map, player, pixel, img, sprite_pos, 156, z_buffdr);
		//sprite_pos += 1;
	}
}