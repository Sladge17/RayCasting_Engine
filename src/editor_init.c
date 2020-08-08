/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/08/08 22:15:07 by vkaron           ###   ########.fr       */
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

void	init_editor(t_editor *ed)
{
	ed->offset.x = 0;
	ed->offset.y = 0;
	ed->cursor.x = 3;
	ed->cursor.y = 1;
	ed->panel.x = ((S_W - 320) / 64) * 64;
	ed->panel.y = ((S_H - 64) / 64) * 64;
	ed->cur_wall = -1;
	ed->put = 0;
	ed->scale = 32;
	ed->press_l = 0;
	ed->press_r = 0;
	ed->cur_elem = 3;
	ed->status = 0;
	ed->map.floor = 0xFF707070;
	ed->map.roof = 0xFF323246;
	init_editor_map(ed);
}
