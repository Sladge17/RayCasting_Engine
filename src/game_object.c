/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_object.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/07/27 14:38:28 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	check_x(t_game_obj *obj, t_map *map, t_vec2 *test)
{
	int index1;
	int index2;

	index1 = (int)(test->y) * map->width + (int)(test->x - obj->border);
	index2 = (int)(test->y) * map->width + (int)(test->x + obj->border);
	if (index1 > 0 && index1 < map->max && map->elem[index1].lock == 1)
		test->x = (int)(test->x - obj->border + 1) + obj->border;
	else if (index2 > 0 && index2 < map->max && map->elem[index2].lock == 1)
		test->x = (int)(test->x + obj->border) - obj->border;
}

void	check_y(t_game_obj *obj, t_map *map, t_vec2 *test)
{
	int index1;
	int index2;

	index1 = (int)(test->y - obj->border) * map->width + (int)(test->x);
	index2 = (int)(test->y + obj->border) * map->width + (int)(test->x);
	if (index1 > 0 && index1 < map->max && map->elem[index1].lock == 1)
		test->y = (int)(test->y - obj->border + 1) + obj->border;
	else if (index2 > 0 && index2 < map->max && map->elem[index2].lock == 1)
		test->y = (int)(test->y + obj->border) - obj->border;
}

void	move_forward(t_game_obj *obj, t_map *map)
{
	t_vec2	test;
	
	test.x = obj->pos.x + obj->speed * obj->dir.x;
	test.y = obj->pos.y + obj->speed * obj->dir.y;
	check_x(obj, map, &(test));
	check_y(obj, map, &(test));
	obj->pos.x = test.x;
	obj->pos.y = test.y;
}

void	move_back(t_game_obj *obj, t_map *map)
{
	t_vec2	test;
	
	test.x = obj->pos.x - obj->speed * obj->dir.x;
	test.y = obj->pos.y - obj->speed * obj->dir.y;
	check_x(obj, map, &(test));
	check_y(obj, map, &(test));
	obj->pos.x = test.x;
	obj->pos.y = test.y;

	//obj->pos.x -= obj->speed * (obj->dir.x);// - obj->pos.x);
	//obj->pos.y -= obj->speed * (obj->dir.y);// - obj->pos.y);
}

void	move_left(t_game_obj *obj, t_map *map)
{
	float rad;
	t_vec2	test;

	rad = (obj->rot - 90) * M_PI / 180;
	test.x = obj->pos.x + obj->speed * sin(rad);
	test.y = obj->pos.y + obj->speed * cos(rad);
	check_x(obj, map, &(test));
	check_y(obj, map, &(test));
	obj->pos.x = test.x;
	obj->pos.y = test.y;	
}

void	move_right(t_game_obj *obj, t_map *map)
{
	float rad;
	t_vec2	test;

	rad = (obj->rot + 90) * M_PI / 180;
	test.x = obj->pos.x + obj->speed * sin(rad);
	test.y = obj->pos.y + obj->speed * cos(rad);
	check_x(obj, map, &(test));
	check_y(obj, map, &(test));
	obj->pos.x = test.x;
	obj->pos.y = test.y;	
}

void	turn_left(t_game_obj *obj)
{
	float rad;

	obj->rot -= obj->rot_speed;
	rad = obj->rot * M_PI / 180;
	obj->dir.x = sin(rad);
	obj->dir.y = cos(rad);
}

void	turn_right(t_game_obj *obj)
{
	float rad;

	obj->rot += obj->rot_speed;
	rad = obj->rot * M_PI / 180;
	obj->dir.x = sin(rad);
	obj->dir.y = cos(rad);
}

void	init_object(t_game_obj *obj,  t_vec2 pos, int rot, float speed,
	int rot_speed)
{
	float rad;

	rad = rot * M_PI / 180;
	obj->pos.x = pos.x;
	obj->pos.y = pos.y;
	obj->rot = rot;
	obj->dir.x = sin(rad);
	obj->dir.y = cos(rad);
	obj->border = 0.4;
	//printf("init dir rad=%f x=%f, y=%f\n", rad, obj->dir.x, obj->dir.y);
	
	obj->rot_speed = rot_speed;
	obj->speed = speed;
}
