/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/09/05 22:02:58 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	set_col_num(t_vec2 *isc_pos, t_isec *isec, t_game *game, SDL_Point index)
{
	t_vec2		delta;
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
}



void	engine(t_game *game, t_isec *isec, int x)
{
	float	ang;
	t_vec2	len;
	float	step;
	t_vec2	check_pos;
	SDL_Point	i;
	SDL_Point index;
	float	dist;


	isec->height = 1;
	isec->number = 0;
	isec->dist = 100;
	ang = (game->player.obj.rot + game->player.sec.ang_step * x);
	float tana = tan(ang);
	while (ang < 0)
		ang += PI2;
	while (ang >= 360)
		ang -= PI2;
	//printf("ang=%.2f tan=%f\n",ang*180.0/M_PI, tana);
	if (ang < M_PI_2)
	{
		i.x = (int)game->player.obj.pos.x;
		if (ang > 0)
		{
			while (++i.x < 64)
			{
				len.x = i.x - game->player.obj.pos.x;
				len.y = len.x / tana; 
				i.y = (int)(len.y) + (int)game->player.obj.pos.y;
				if (i.y < 64 && i.y >=0 && game->level.map.elem[i.y][i.x].number >= 0)
				{
				
					isec->dist = sqrt(len.x * len.x + len.y * len.y);
					check_pos.x = len.x + (int)game->player.obj.pos.x;
					check_pos.y = len.y + (int)game->player.obj.pos.y;
					isec->number = game->level.map.elem[i.y][i.x].side[0];
					isec->colum = (int)((check_pos.y - (int)(check_pos.y)) * 64);
					//printf("XXX cell[%d %d] = %d\n",i.y,i.x, game->level.map.elem[i.y][i.x].number);
					break ;
				}
			}
		}
		i.y = (int)game->player.obj.pos.y;
		while (++i.y < 64)
		{
			len.y = i.y - game->player.obj.pos.y;
			len.x = len.y * tana;
			i.x = (int)(len.x) + (int)game->player.obj.pos.x;
			if (i.x < 64 && i.x >=0 && game->level.map.elem[i.y][i.x].number >= 0)
			{
				dist = sqrt(len.x * len.x + len.y * len.y);
				if (dist < isec->dist)
				{
					isec->dist = dist;
					check_pos.x = len.x + (int)game->player.obj.pos.x;
					check_pos.y = len.y + (int)game->player.obj.pos.y;
					isec->number = game->level.map.elem[i.y][i.x].side[3];
					isec->colum = (int)((check_pos.x - (int)(check_pos.x)) * 64);
					//printf("YYY cell[%d %d] = %d\n", i.y, i.x, game->level.map.elem[i.y][i.x].number);
					
				}
				
				//printf("\n");
				break;
			}
		}
	}
	//*/
	
	//else if (ang < M_PI)
	//{
		
//	}
//	else if (ang < M_PI + M_PI_2)
//	{
		
//	}
//	else
//	{
		
//	}
	if (isec->dist < 100 && index.x >= 0 && index.x < 64 && index.y >= 0 && index.y < 64)
	{
		isec->height = H_W / (isec->dist * cos(ang));
		//set_col_num(&check_pos, isec, game, index);
	}	

/*	
	len.x = sin(ang);
	len.y = cos(ang);
	ang = (game->player.sec.ang_step * x);
	step = 0;
	
	while (step < 91)
	{
		step += 0.01;
		check_pos.x = (game->player.obj.pos.x + len.x * step);
		check_pos.y = (game->player.obj.pos.y + len.y * step);
		index.y = (int)check_pos.y;
		index.x = (int)check_pos.x;
		if (index.x >= 0 && index.x < 64 && index.y >= 0 && index.y < 64)
		{		
			if (game->level.map.elem[index.y][index.x].number >= 0) {
				isec->dist = step;
				isec->height = H_W / (isec->dist * cos(ang));
				set_col_num(&check_pos, isec, game, index);
				return ;
			}
		}
	}
	//*/
}

void	engine2(t_game *game, t_isec *isec, int x)
{
	float	ang;
	t_vec2	len;
	float	step;
	t_vec2	check_pos;
	SDL_Point index;

	ang = (game->player.obj.rot + game->player.sec.ang_step * x);
	
	len.x = sin(ang);
	len.y = cos(ang);
	ang = (game->player.sec.ang_step * x);
	step = 0;
	isec->height = 1;
	isec->number = 0;
	isec->dist = 100;
	while (step < 91)
	{
		step += 0.01;
		check_pos.x = (game->player.obj.pos.x + len.x * step);
		check_pos.y = (game->player.obj.pos.y + len.y * step);
		index.y = (int)check_pos.y;
		index.x = (int)check_pos.x;
		if (index.x >= 0 && index.x < 64 && index.y >= 0 && index.y < 64)
		{		
			if (game->level.map.elem[index.y][index.x].number >= 0) {
				isec->dist = step;
				isec->height = H_W / (isec->dist * cos(ang));
				set_col_num(&check_pos, isec, game, index);
				return ;
			}
		}
	}
}
