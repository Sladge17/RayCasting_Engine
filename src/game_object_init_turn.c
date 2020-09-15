/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_object_init_turn.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/09/15 09:50:12 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	turn_left(t_game_obj *obj, double koeff)
{
	obj->rot += obj->rot_speed * koeff;
	while (obj->rot > PI2)
		obj->rot -= PI2;
	obj->dir.x = sin(obj->rot);
	obj->dir.y = cos(obj->rot);
}

void	turn_right(t_game_obj *obj, double koeff)
{
	obj->rot -= obj->rot_speed * koeff;
	while (obj->rot < 0)
		obj->rot += PI2;
	obj->dir.x = sin(obj->rot);
	obj->dir.y = cos(obj->rot);
}

void	init_object(t_game_obj *obj, t_vec2 pos, double rot, t_vec2 speed)
{
	obj->pos.x = pos.x;
	obj->pos.y = pos.y;
	obj->rot = rot;
	obj->dir.x = sin(rot);
	obj->dir.y = cos(rot);
	obj->border = 0.49;
	obj->rot_speed = speed.y;
	obj->speed = speed.x;
}
