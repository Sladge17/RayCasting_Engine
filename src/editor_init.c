/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/08/11 16:35:24 by vkaron           ###   ########.fr       */
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
	int i;
	int d;

	i = 0;
	d = -2;
	ed->wall.it[0] = -1;
	while(++i < 64)
	{
		if (i == 49)
			d = 444;
		ed->wall.it[i] = i * 2 + d;
	}
	ed->wall.max = 62;
	ed->wall.cur = 0;
}

void	init_editor_door(t_editor *ed)
{
	ed->door.it[0] = 98;
	ed->door.it[1] = 102;
	ed->door.it[2] = 104;
	ed->door.max = 2;
	ed->door.cur = 0;
}

void	init_editor_player(t_editor *ed)
{
	ed->player.it[0] = 514;
	ed->player.max = 0;
	ed->player.cur = 0;
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
	
	select_cursor_sprite(ed);
}
