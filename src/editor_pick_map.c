/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_pick_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/08/17 18:59:10 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	editor_set_cell(t_editor *ed)
{
	ed->map.elem[ed->cursor.pos.y][ed->cursor.pos.x].number = 
		ed->cursor.en->it[ed->cursor.en->cur];
	
//	ed->map.elem[ed->cursor.pos.y][ed->cursor.pos.x].type = 
	//if (ed->cursor.pos.y > 0)
//	{
		//if ()
//	}
}
