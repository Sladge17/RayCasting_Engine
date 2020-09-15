/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_pick_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/09/15 09:29:24 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		check_door(t_editor *ed)
{
	if (ed->cursor.pos.y > 0 && ed->cursor.pos.y < 63 &&
		ed->type_map[ed->cursor.pos.y + 1][ed->cursor.pos.x] == WALL &&
		ed->type_map[ed->cursor.pos.y - 1][ed->cursor.pos.x] == WALL)
		return (1);
	if (ed->cursor.pos.x > 0 && ed->cursor.pos.x < 63 &&
		ed->type_map[ed->cursor.pos.y][ed->cursor.pos.x + 1] == WALL &&
		ed->type_map[ed->cursor.pos.y][ed->cursor.pos.x - 1] == WALL)
		return (1);
	return (0);
}

void	check_player(t_editor *ed)
{
	ed->map.elem[(int)ed->map.player.pos.y][(int)ed->map.player.pos.x]
	.number = -1;
	ed->type_map[(int)ed->map.player.pos.y][(int)ed->map.player.pos.x] =
	NONE;
	ed->map.player.pos.y = ed->cursor.pos.y + 0.5;
	ed->map.player.pos.x = ed->cursor.pos.x + 0.5;
}

int		check_cell(t_editor *ed)
{
	t_type	cell;

	cell = ed->cursor.en->type;
	if (cell == PLAYER)
		return (1);
	else if (cell == NONE || cell == WALL || cell == DOOR)
		return (1);
	else if (cell == ENEMY && ed->enemies < 128)
		ed->enemies += 1;
	else if (cell == BARIER && ed->bariers < 64)
		ed->bariers += 1;
	else if (cell == ACHIV && ed->achivs < 64)
		ed->achivs += 1;
	else if (cell == ENTOURAGE && ed->entours < 64)
		ed->entours += 1;
	else
		return (0);
	return (1);
}

void	change_cell(t_editor *ed)
{
	int			cursor;
	t_map_elem	*cell;
	t_type		*c_type;

	cell = &ed->map.elem[ed->cursor.pos.y][ed->cursor.pos.x];
	c_type = &ed->type_map[ed->cursor.pos.y][ed->cursor.pos.x];
	cursor = ed->cursor.en->it[ed->cursor.en->cur];
	if (*c_type != PLAYER)
	{
		if (*c_type == ENEMY)
			ed->enemies -= 1;
		else if (*c_type == BARIER)
			ed->bariers -= 1;
		else if (*c_type == ACHIV)
			ed->achivs -= 1;
		else if (*c_type == ENTOURAGE)
			ed->entours -= 1;
		ed->map.elem[ed->cursor.pos.y][ed->cursor.pos.x].number = cursor;
		editor_set_side(c_type, cursor, ed, cell);
	}
}

void	editor_set_cell(t_editor *ed)
{
	t_type		cur_type;

	cur_type = ed->cursor.en->type;
	if (cur_type == PLAYER)
		check_player(ed);
	else if (cur_type == DOOR && !check_door(ed))
		return ;
	if (!check_cell(ed))
		return ;
	change_cell(ed);
}
