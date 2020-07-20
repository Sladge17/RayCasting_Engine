/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_object.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/07/20 18:27:22 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	move_forward(t_game_obj *obj)
{
	obj->pos.x += obj->speed * (obj->dir.x);// - obj->pos.x);
	obj->pos.y += obj->speed * (obj->dir.y);// - obj->pos.y);
}

void	move_back(t_game_obj *obj)
{
	obj->pos.x -= obj->speed * (obj->dir.x);// - obj->pos.x);
	obj->pos.y -= obj->speed * (obj->dir.y);// - obj->pos.y);
}	

void	turn_left(t_game_obj *obj)
{
	float rad;

	rad = obj->rot * M_PI / 180.0f;
	obj->rot += obj->rot_speed;
	obj->dir.x = sin(rad);
	obj->dir.y = cos(rad);
}

void	turn_right(t_game_obj *obj)
{
	float rad;

	rad = obj->rot * M_PI / 180.0f;
	obj->rot -= obj->rot_speed;
	obj->dir.x = sin(rad);
	obj->dir.y = cos(rad);
}

void	init_object(t_game_obj *obj,  t_vec2 pos, int rot, int speed,
	int rot_speed)
{
	float rad;

	rad = rot * M_PI / 180.0f;
	obj->pos.x = pos.x;
	obj->pos.y = pos.y;
	obj->rot = rot;
	obj->dir.x = sin(rad);
	obj->dir.y = cos(rad);
	printf("init dir rad=%f x=%f, y=%f\n", rad, obj->dir.x, obj->dir.y);
	
	obj->rot_speed = rot_speed;
	obj->speed = speed;
}
