/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/07/20 19:54:39 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	engine(t_game *game, t_isec *isec, int x)
{
	float	ang;
	t_vec2	target;
	float	step;
	t_vec2	check_pos;
	int index;

	ang = (game->player.obj.rot + game->player.sec.ang_step * x) * M_PI / 180;
	target.x = sin(ang);
	target.y = cos(ang);
	ang = (game->player.sec.ang_step * x) * M_PI / 180;
	step = 0;
	isec->height = 0;
	isec->number = 0;
	while (step < 50)
	{
		step += 0.01;
		check_pos.x = (game->player.obj.pos.x + target.x * step);
		check_pos.y = (game->player.obj.pos.y + target.y * step);
		index = (int)check_pos.y * 10 + (int)check_pos.x;
		if (index >= 0 && index <100)
		{		
			if (game->level.map[index].elem->lock) {
				isec->number = game->level.map[index].elem->number;
				isec->dist = step;
				isec->height = H_H / (isec->dist * cos(ang));
				return ;
			}
		}
	}
}
