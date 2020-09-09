/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/08/25 16:49:23 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	init_editor_map_ent(t_editor *ed)
{
	const int	entourage[] = {108, 111, 112, 117, 122, 123, 127, 142, 146,
	149, 150, 151, 152};
	int			i;
	int			j;

	j = -1;
	while (++j < 64)
	{
		i = -1;
		while (++i < 64)
		{
			if (i == 0 || i == 63 || j == 0 || j == 63)
				ed->map.elem[j][i].number = 0;
			else
				ed->map.elem[i][j].number = -1;
		}
	}
	ed->entourage.max = 12;
	i = -1;
	while (++i <= ed->entourage.max)
		ed->entourage.it[i] = entourage[i];
	ed->entourage.cur = 0;
	ed->entourage.type = ENTOURAGE;
}

void	init_editor_wall_pl_bar(t_editor *ed)
{
	const int	wall[] = {-1, 0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26,
	28, 30, 32, 34, 36, 38, 40, 42, 44, 46, 48, 50, 52, 54, 56, 58, 60, 62,
	64, 66, 68, 70, 72, 74, 76, 78, 80, 82, 84, 86, 88, 90, 92, 94, 96, 542,
	544, 546, 548, 550, 552, 554, 556, 558, 560, 562, 564, 566, 568, 570};
	const int	barier[] = {109, 110, 113, 115, 116, 118, 119, 120, 121, 124,
	125, 126, 130, 143, 144, 145, 147, 153, 154, 155, 570, 571, 572, 574,
	575, 576, 577, 578, 579, 580};
	int			i;

	i = -1;
	ed->wall.max = 63;
	while (++i < ed->wall.max + 1)
		ed->wall.it[i] = wall[i];
	ed->wall.cur = 0;
	ed->wall.type = WALL;
	ed->barier.max = 29;
	i = -1;
	while (++i <= ed->barier.max)
		ed->barier.it[i] = barier[i];
	ed->barier.cur = 0;
	ed->barier.type = BARIER;
	ed->player.it[0] = 514;
	ed->player.max = 0;
	ed->player.cur = 0;
	ed->player.type = PLAYER;
}

void	init_editor_enemy_ach_door(t_editor *ed)
{
	const int	enemy[] = {156, 205, 244, 344, 394, 396, 398, 400, 402, 413,
	427, 440, 466, 491, 502, 600, 611, 623, 636, 651, 659};
	const int	achiv[] = {114, 128, 129, 132, 133, 134, 135, 136, 137, 138,
	139, 140, 141};
	int			i;

	ed->enemy.max = 20;
	i = -1;
	while (++i <= ed->enemy.max)
		ed->enemy.it[i] = enemy[i];
	ed->enemy.cur = 0;
	ed->enemy.type = ENEMY;
	ed->achiv.max = 12;
	i = -1;
	while (++i <= ed->achiv.max)
		ed->achiv.it[i] = achiv[i];
	ed->achiv.cur = 0;
	ed->achiv.type = ACHIV;
	ed->door.it[0] = 98;
	ed->door.it[1] = 102;
	ed->door.it[2] = 104;
	ed->door.max = 2;
	ed->door.cur = 0;
	ed->door.type = DOOR;
}

void	init_type_map(t_editor *ed)
{
	int i;
	int j;

	j = -1;
	while (++j < 64)
	{
		i = -1;
		while (++i < 64)
		{
			if (i == 0 || i == 63 || j == 0 || j == 63)
				ed->type_map[j][i] = WALL;
			else
				ed->type_map[j][i] = NONE;
			ed->map.elem[i][j].modify = 0;
		}
	}
	ed->map.player.pos.x = 1.5;
	ed->map.player.pos.y = 1.5;
	ed->type_map[1][1] = PLAYER;
	ed->map.elem[1][1].number = ed->player.it[0];
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
	ed->enemies = 0;
	ed->bariers = 0;
	ed->achivs = 0;
	ed->entours = 0;
	init_editor_map_ent(ed);
	init_editor_wall_pl_bar(ed);
	init_editor_enemy_ach_door(ed);
	init_type_map(ed);
	select_cursor_sprite(ed);
}
