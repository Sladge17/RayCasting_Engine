/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/08/25 22:45:18 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	set_col_num(t_vec2 *isc_pos, t_isec *isec, t_game *game, SDL_Point index)
{
	//float		colum;
	t_vec2		delta;
	//t_vec2		box;
	//t_col_num	res;
	//float		tmp;
	int		number;
	int		number2;
	
	if (isc_pos->y < floor(isc_pos->y) + 0.5)
	{
		delta.y = isc_pos->y - floor(isc_pos->y);
		number = 0;
	}
	else
	{
		delta.y = floor(isc_pos->y) + 1.0 - isc_pos->y;
		number = 2;
	}
	if (isc_pos->x < floor(isc_pos->x) + 0.5)
	{
		delta.x = isc_pos->x - floor(isc_pos->x);
		number2 = 3;
	}
	else
	{
		delta.x = floor(isc_pos->x) + 1.0 - isc_pos->x;
		number2 = 1;
	}
	if (delta.x > delta.y)
	{
		isec->colum = (int)((isc_pos->x - (int)(isc_pos->x)) * 64);
		isec->number = game->level.map.elem[index.y][index.x].side[number];
		if (number == 0)
			isec->colum = 63 - isec->colum;
	}
	else
	{
		isec->colum = (int)((isc_pos->y - (int)(isc_pos->y)) * 64);
		isec->number = game->level.map.elem[index.y][index.x].side[number2];
		if (number2 == 1)
			isec->colum = 63 - isec->colum;
	}
	//return (res);
	/*
	res.col = 0;
	res.num = 0;
	box.x = floor(isc_pos.x);
	box.y = floor(isc_pos.y);

	if (pos->x >= box.x && pos->x <= box.x + 1.0)
	{
		if (pos->y < box.y)
		{
			tmp = isc_pos->x - ((isc_pos->x - pos->x) * 
				(box.y - pos->y) / (isc_pos->y - pos->y));
			res.col = ((int)(tmp = (int)tmp) * 64);
			res.num = 0;
		}
		
			
	}

	delta.x = abs(pos->x - isc_pos->x);
	delta.y = abs(pos->y - isc_pos->y);
	
	if ()
	
	if (delta.x <= delta.y)
	{
		if ()
		colum = (isc_pos->x - (int)isc_pos->x) * 64;
	}
	else
	{
		colum = (isc_pos->y - (int)isc_pos->y) * 64;
	}
	return ((int)colum);
	*/
}

void	engine(t_game *game, t_isec *isec, int x)
{
	float	ang;
	t_vec2	target;
	float	step;
	t_vec2	check_pos;
	SDL_Point index;

	ang = (game->player.obj.rot + game->player.sec.ang_step * x) * M_PI / 180;
	target.x = sin(ang);
	target.y = cos(ang);
	ang = (game->player.sec.ang_step * x) * M_PI / 180;
	step = 0;
	isec->height = 1;
	isec->number = 0;
	isec->dist = 100;
	while (step < 91)
	{
		step += 0.01;
		check_pos.x = (game->player.obj.pos.x + target.x * step);
		check_pos.y = (game->player.obj.pos.y + target.y * step);
		index.y = (int)check_pos.y;
		index.x = (int)check_pos.x;
		if (index.x >= 0 && index.x < 64 && index.y >= 0 && index.y < 64)
		{		
			if (game->level.map.elem[index.y][index.x].lock) {
				isec->dist = step;
				isec->height = H_W / (isec->dist * cos(ang));
				set_col_num(&check_pos, isec, game, index);
				return ;
			}
		}
	}
}
