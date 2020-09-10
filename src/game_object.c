/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_object.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/09/09 15:42:35 by vkaron           ###   ########.fr       */
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
	y1 = (int)(test->y - obj->border);
	y2 = (int)(test->y + obj->border);
	if (y1 >= 0 && y1 < 64 && x >= 0 && x < 64 && map->elem[y1][x].lock == 1)
		test->y = (int)(test->y - obj->border) + obj->border + 1.0;
	else if (y2 >= 0 && y2 < 64 && x >= 0 && x < 64 && map->elem[y2][x].lock == 1)
		test->y = (int)(test->y + obj->border) - obj->border;
}

void	check_left_up(t_game_obj *obj, t_map *map, t_vec2 *test)
{
	SDL_Point	pos;
	t_vec2		offs;
	double		dist;
	double		bord;

	pos.x = (int)test->x;
	pos.y = (int)test->y;
	if (pos.x == 0 || pos.y == 0)
		return ;
	offs.y = pos.y + test->y;
	offs.x = pos.x + test->x;
	bord = obj->border * obj->border;
	dist = offs.x * offs.x + offs.y * offs.y;
	if (map->elem[pos.y - 1][pos.x - 1].lock == 1 && dist < bord)
	{
		if (test->x < pos.x + obj->border)
			test->x = pos.x + obj->border;
		if (test->y < pos.y + obj->border)
			test->y = pos.y + obj->border;
	}
}

void	check_right_up(t_game_obj *obj, t_map *map, t_vec2 *test)
{
	SDL_Point	pos;
	t_vec2		offs;
	double		dist;
	double		bord;

	pos.x = (int)test->x;
	pos.y = (int)test->y;
	if (pos.x == 63 || pos.y == 0)
		return ;
	offs.y = pos.y + test->y;
	offs.x = pos.x + 1.0 - test->x;
	bord = obj->border * obj->border;
	dist = offs.x * offs.x + offs.y * offs.y;
	if (map->elem[pos.y - 1][pos.x + 1].lock == 1 && dist < bord)
	{
		if (test->x > pos.x + 1.0 - obj->border)
			test->x = pos.x + 1.0 -  obj->border;
		if (test->y < pos.y + obj->border)
			test->y = pos.y + obj->border;
	}
}

void	check_left_down(t_game_obj *obj, t_map *map, t_vec2 *test)
{
	SDL_Point	pos;
	t_vec2		offs;
	double		dist;
	double		bord;

	pos.x = (int)test->x;
	pos.y = (int)test->y;
	if (pos.y == 63 || pos.x == 0)
		return ;
	offs.y = pos.y + 1.0 - test->y;
	offs.x = pos.x + test->x;
	bord = obj->border * obj->border;
	dist = offs.x * offs.x + offs.y * offs.y;
	if (map->elem[pos.y + 1][pos.x - 1].lock == 1 && dist < bord)
	{
		if (test->y > pos.y + 1.0 - obj->border)
			test->y = pos.y + 1.0 -  obj->border;
		if (test->x < pos.x + obj->border)
			test->x = pos.x + obj->border;
	}
}

void	check_right_down(t_game_obj *obj, t_map *map, t_vec2 *test)
{
	SDL_Point	pos;
	t_vec2		offs;
	double		dist;
	double		bord;

	pos.x = (int)test->x;
	pos.y = (int)test->y;
	if (pos.y == 63 || pos.x == 63)
		return ;
	offs.y = pos.y + 1.0 - test->y;
	offs.x = pos.x + 1.0 - test->x;
	bord = obj->border * obj->border;
	dist = offs.x * offs.x + offs.y * offs.y;
	if (map->elem[pos.y + 1][pos.x + 1].lock == 1 && dist < bord)
	{
		if (test->y > pos.y + 1.0 - obj->border)
			test->y = pos.y + 1.0 -  obj->border;
		if (test->x > pos.x + 1.0 - obj->border)
			test->x = pos.x + 1.0 -  obj->border;
	}
}

void	check_step(t_game_obj *obj, t_map *map, t_vec2 *test)
{
	int	x;
	int	y;

	x = (int)test->x;
	y = (int)test->y;
	if (x <= 0 && test->x < obj->border)
		test->x = obj->border;
	if (y <= 0 && test->y < obj->border)
		test->y = obj->border;
	if (y >= 64  && test->y > 64.0 - obj->border)
		test->y = 64.0 - obj->border;
	if (x >= 63 && test->x > 64.0 - obj->border)
		test->x = 64.0 - obj->border;	
	check_x(obj, map, test);
	check_y(obj, map, test);
	check_left_up(obj, map, test);
	check_right_up(obj, map, test);
	check_left_down(obj, map, test);
	check_right_down(obj, map, test);
}

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
	float rad;
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
	float rad;
	t_vec2	test;

	koeff *= obj->speed;
	rad = (obj->rot - M_PI_2);
	test.x = obj->pos.x + koeff * sin(rad);
	test.y = obj->pos.y + koeff * cos(rad);
	check_step(obj, map, &(test));
	obj->pos.x = test.x;
	obj->pos.y = test.y;	
}

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

void	init_object(t_game_obj *obj,  t_vec2 pos, double rot, double speed,
	double rot_speed)
{
	obj->pos.x = pos.x;
	obj->pos.y = pos.y;
	obj->rot = rot;
	obj->dir.x = sin(rot);
	obj->dir.y = cos(rot);
	obj->border = 0.49;
	obj->rot_speed = rot_speed;
	obj->speed = speed;
}
