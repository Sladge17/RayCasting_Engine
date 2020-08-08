/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_object.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/07/27 18:14:25 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	check_x(t_game_obj *obj, t_map *map, t_vec2 *test)
{
	int x1;
	int x2;
	int y;
	
	y = (int)test->y;
	x1 = (int)(test->x - obj->border);
	x2 = (int)(test->x + obj->border);
	if (x1 >= 0 && x1 < 64 && y >= 0 && y < 64 && map->elem[y][x1].lock == 1)
		test->x = (int)(test->x - obj->border) + obj->border + 1.0;
	else if (x2 >= 0 && x2 < 64 && y >= 0 && y < 64 && map->elem[y][x2].lock == 1)
		test->x = (int)(test->x + obj->border) - obj->border;
}

void	check_y(t_game_obj *obj, t_map *map, t_vec2 *test)
{
	int y1;
	int y2;
	int x;

	x = (int)test->x;
	y1 = (int)(test->y - obj->border);// * map->width + (int)(test->x);
	y2 = (int)(test->y + obj->border);// * map->width + (int)(test->x);
	if (y1 >= 0 && y1 < 64 && x >= 0 && x < 64 && map->elem[y1][x].lock == 1)
		test->y = (int)(test->y - obj->border) + obj->border + 1.0;
	else if (y2 >= 0 && y2 < 64 && x >= 0 && x < 64 && map->elem[y2][x].lock == 1)
		test->y = (int)(test->y + obj->border) - obj->border;
}

void	move_forward(t_game_obj *obj, t_map *map, float koeff)
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
		check_x(obj, map, &(test));
		check_y(obj, map, &(test));
		koeff -= step;
	}
	obj->pos.x = test.x;
	obj->pos.y = test.y;
}

void	move_back(t_game_obj *obj, t_map *map, float koeff)
{
	t_vec2	test;

	koeff *= obj->speed;
	test.x = obj->pos.x - koeff * obj->dir.x;
	test.y = obj->pos.y - koeff * obj->dir.y;
	check_x(obj, map, &(test));
	check_y(obj, map, &(test));
	obj->pos.x = test.x;
	obj->pos.y = test.y;

	//obj->pos.x -= obj->speed * (obj->dir.x);// - obj->pos.x);
	//obj->pos.y -= obj->speed * (obj->dir.y);// - obj->pos.y);
}

void	move_left(t_game_obj *obj, t_map *map, float koeff)
{
	float rad;
	t_vec2	test;

	koeff *= obj->speed;
	rad = (obj->rot + 90) * M_PI / 180;
	test.x = obj->pos.x + koeff * sin(rad);
	test.y = obj->pos.y + koeff * cos(rad);
	check_x(obj, map, &(test));
	check_y(obj, map, &(test));
	obj->pos.x = test.x;
	obj->pos.y = test.y;	
}

void	move_right(t_game_obj *obj, t_map *map, float koeff)
{
	float rad;
	t_vec2	test;

	koeff *= obj->speed;
	rad = (obj->rot - 90) * M_PI / 180;
	test.x = obj->pos.x + koeff * sin(rad);
	test.y = obj->pos.y + koeff * cos(rad);
	check_x(obj, map, &(test));
	check_y(obj, map, &(test));
	obj->pos.x = test.x;
	obj->pos.y = test.y;	
}

void	turn_left(t_game_obj *obj, float koeff)
{
	float rad;

	obj->rot += obj->rot_speed * koeff;
	rad = obj->rot * M_PI / 180;
	obj->dir.x = sin(rad);
	obj->dir.y = cos(rad);
}

void	turn_right(t_game_obj *obj, float koeff)
{
	float rad;

	obj->rot -= obj->rot_speed * koeff;
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
