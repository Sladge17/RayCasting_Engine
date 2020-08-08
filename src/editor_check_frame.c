/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_check_frame.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/08/08 23:11:07 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	check_ceil_color(SDL_MouseButtonEvent *e, t_game *game, t_editor *ed)
{
	
	if (e->x >= H_W - 256 && e->x < H_W + 284 && e->y >= H_H - 100 && e->y < H_H + 156)
		ed->map.roof = game->data[e->y * S_W + e->x];
}

void	check_floor_color(SDL_MouseButtonEvent *e, t_game *game, t_editor *ed)
{
	
	if (e->x >= H_W - 256 && e->x < H_W + 284 && e->y >= H_H - 100 && e->y < H_H + 156)
		ed->map.floor= game->data[e->y * S_W + e->x];
}

int		check_frame(SDL_MouseButtonEvent *e, t_game *game, t_editor *ed)
{
	if (ed->status > 0 && ed->mouse_pos.x > H_W - 320 && 
		ed->mouse_pos.x < H_W + 320 && ed->mouse_pos.y > H_H - 240 &&
		ed->mouse_pos.y < H_H + 240)
	{
		if (ed->status == 1)
			check_ceil_color(e, game, ed);
		if (ed->status == 2)
			check_floor_color(e, game, ed);
		//ed->status = 0;
		return 1;
	}
	return 0;
}
