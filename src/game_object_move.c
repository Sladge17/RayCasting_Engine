/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_object_move.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/09/15 09:50:04 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	move_forward(t_game_obj *obj, t_map *map, double koeff)
{
	t_vec2	test;
	float	step;

	koeff *= obj->speed;
	test.x = obj->pos.x;
	test.y = obj->pos.y;
	step = obj->border;
	while (koeff > 0)
	{
		if (step > koeff)
			step = koeff;
		test.x += step * obj->dir.x;
		test.y += step * obj->dir.y;
		check_step(obj, map, &(test));
		koeff -= step;
	}
	obj->pos.x = test.x;
	obj->pos.y = test.y;
}

void	move_back(t_game_obj *obj, t_map *map, double koeff)
{
	t_vec2	test;

	koeff *= obj->speed;
	test.x = obj->pos.x - koeff * obj->dir.x;
	test.y = obj->pos.y - koeff * obj->dir.y;
	check_step(obj, map, &(test));
	obj->pos.x = test.x;
	obj->pos.y = test.y;
}

void	move_left(t_game_obj *obj, t_map *map, double koeff)
{
	float	rad;
	t_vec2	test;

	koeff *= obj->speed;
	rad = (obj->rot + M_PI_2);
	test.x = obj->pos.x + koeff * sin(rad);
	test.y = obj->pos.y + koeff * cos(rad);
	check_step(obj, map, &(test));
	obj->pos.x = test.x;
	obj->pos.y = test.y;
}

void	move_right(t_game_obj *obj, t_map *map, double koeff)
{
	float	rad;
	t_vec2	test;

	koeff *= obj->speed;
	rad = (obj->rot - M_PI_2);
	test.x = obj->pos.x + koeff * sin(rad);
	test.y = obj->pos.y + koeff * cos(rad);
	check_step(obj, map, &(test));
	obj->pos.x = test.x;
	obj->pos.y = test.y;
}
