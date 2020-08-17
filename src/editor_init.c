/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/08/17 20:46:17 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	init_editor_map(t_editor *ed)
{
	int i;
	int j;

	j = -1;
	while (++j < 64)
	{
		i = -1;
		while (++i < 64)
		{
			if (i == 0 || i == 63 || j == 63 || j == 63)
				ed->map.elem[j][i].number = 0;
			else
				ed->map.elem[i][j].number = -1;
		}
	}
}

void	init_editor_wall(t_editor *ed)
{
	const int wall[] = {-1, 0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28,
	30, 32, 34, 36, 38, 40, 42, 44, 46, 48, 50, 52, 54, 56, 58, 60, 62, 64, 66,
	68, 70, 72, 74, 76, 78, 80, 82, 84, 86, 88, 90, 92, 94, 96, 558, 560, 562,
	564, 566, 568, 570, 572, 574, 576, 578, 580, 582, 584};
	int i;

	i = -1;
	ed->wall.max = 62;
	while(++i < ed->wall.max + 1)
		ed->wall.it[i] = wall[i];
	ed->wall.cur = 0;
	ed->wall.type = WALL;
}

void	init_editor_door(t_editor *ed)
{
	ed->door.it[0] = 98;
	ed->door.it[1] = 102;
	ed->door.it[2] = 104;
	ed->door.max = 2;
	ed->door.cur = 0;
	ed->door.type = DOOR;
}

void	init_editor_player(t_editor *ed)
{
	ed->player.it[0] = 514;
	ed->player.max = 0;
	ed->player.cur = 0;
	ed->player.type = PLAYER;
}

void	init_editor_enemy(t_editor *ed)
{
	ed->enemy.it[0] = 156;
	ed->enemy.it[1] = 205;
	ed->enemy.it[2] = 244;
	ed->enemy.it[3] = 293;
	ed->enemy.it[4] = 344;
	ed->enemy.it[5] = 394;
	ed->enemy.it[6] = 396;
	ed->enemy.it[7] = 398;
	ed->enemy.it[8] = 400;
	ed->enemy.it[9] = 402;
	ed->enemy.it[10] = 413;
	ed->enemy.it[11] = 427;
	ed->enemy.it[12] = 440;
	ed->enemy.it[13] = 466;
	ed->enemy.it[14] = 491;
	ed->enemy.it[15] = 502;
	ed->enemy.it[16] = 600;
	ed->enemy.it[17] = 611;
	ed->enemy.it[18] = 623;
	ed->enemy.it[19] = 636;
	ed->enemy.it[20] = 651;
	ed->enemy.it[21] = 659;
	ed->enemy.max = 21;
	ed->enemy.cur = 0;
	ed->enemy.type = ENEMY;
}

void	init_editor_achiv(t_editor *ed)
{
	int i;

	ed->achiv.it[0] = 114;
	ed->achiv.it[1] = 128;
	ed->achiv.it[2] = 129;
	i = 2;
	while (++i < 13)	
		ed->achiv.it[i] = i + 129;
	ed->achiv.max = 12;
	ed->achiv.cur = 0;
	ed->achiv.type = ACHIV;
}

void	init_editor_barier(t_editor *ed)
{
	const int barier[] = {109, 110, 113, 115, 116, 118, 119, 120, 121, 124, 
		125, 126, 130, 143, 144, 145, 147, 153, 154, 155, 570, 571, 572,
		574, 575, 576, 577, 578, 579, 580};
	int i;

	ed->barier.max = 29;
	i = -1;
	while (++i <= ed->barier.max)
		ed->barier.it[i] = barier[i];
	ed->barier.cur = 0;
	ed->barier.type = BARIER;
}

void	init_editor(t_editor *ed)
{
	ed->offset.x = 0;
	ed->offset.y = 0;
	ed->cursor.pos.x = 3;
	ed->cursor.pos.y = 1;
	ed->panel.x = ((S_W - 320) / 64) * 64;
	ed->panel.y = ((S_H - 64) / 64) * 64;
	
	ed->put = 0;
	ed->scale = 32;
	ed->press_l = 0;
	ed->press_r = 0;
	ed->cur_elem = 3;
	
	ed->status = 0;
	ed->map.floor = 0xFF707070;
	ed->map.roof = 0xFF323246;
	init_editor_map(ed);
	init_editor_player(ed);
	init_editor_wall(ed);
	init_editor_door(ed);
	init_editor_enemy(ed);
	init_editor_achiv(ed);
	init_editor_barier(ed);
	select_cursor_sprite(ed);
}
