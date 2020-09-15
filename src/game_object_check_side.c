/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_object_check_side.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/09/15 09:47:40 by vkaron           ###   ########.fr       */
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
	else if (x2 >= 0 && x2 < 64 && y >= 0 && y < 64 &&
		map->elem[y][x2].lock == 1)
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
	else if (y2 >= 0 && y2 < 64 && x >= 0 && x < 64 &&
		map->elem[y2][x].lock == 1)
		test->y = (int)(test->y + obj->border) - obj->border;
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
	if (y >= 64 && test->y > 64.0 - obj->border)
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
