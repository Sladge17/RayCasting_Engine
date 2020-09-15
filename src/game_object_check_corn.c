/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_object_check_corn.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/09/15 09:51:17 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

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
			test->x = pos.x + 1.0 - obj->border;
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
			test->y = pos.y + 1.0 - obj->border;
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
			test->y = pos.y + 1.0 - obj->border;
		if (test->x > pos.x + 1.0 - obj->border)
			test->x = pos.x + 1.0 - obj->border;
	}
}
