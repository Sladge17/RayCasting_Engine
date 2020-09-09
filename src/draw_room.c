/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_room.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 16:10:28 by jthuy             #+#    #+#             */
/*   Updated: 2020/09/05 20:25:21 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

// void	def_raylen(t_map *map, t_player *player, t_drawer *drawer)
// {
// 	drawer->ray_len = 0; // Расстояние до препятствия в направлении fRayAngle
// 	while (drawer->ray_len < player->ray_depth) // Пока не столкнулись со стеной, Или не вышли за радиус видимости
// 	{
// 		drawer->barrier_x_f = player->pos_x + drawer->ray_len * drawer->ray_sin;
// 		drawer->barrier_y_f = player->pos_y + drawer->ray_len * drawer->ray_cos;
// 		drawer->barrier_x_d = (int)drawer->barrier_x_f;
// 		drawer->barrier_y_d = (int)drawer->barrier_y_f;

// 		if (check_barrier(map, player, drawer))
// 			break ;
// 		drawer->ray_len += 0.01;
// 	}
// }

// VERSION 3 tan KVADRANT
void	def_raylen(t_map *map, t_player *player, t_drawer *drawer)
{
	drawer->ray_angle = ((drawer->cursor_x / (double)S_W) * player->sec.fov)
		+ (player->obj.rot - player->sec.fov / 2.0);
	drawer->ray_tan[0] = tan(drawer->ray_angle);
	drawer->ray_tan[1] = tan(drawer->ray_angle - M_PI_2);
	if (drawer->ray_angle >= 2 * M_PI)
		drawer->ray_angle -= 2 * M_PI;
	if (drawer->ray_angle < 0)
		drawer->ray_angle = 2 * M_PI + drawer->ray_angle;
	if (drawer->ray_angle >= 0 && drawer->ray_angle < M_PI_2)
	{
		calc_firstquad(map, player, drawer);
		return ;
	}
	if (drawer->ray_angle >= M_PI_2 && drawer->ray_angle < M_PI)
	{
		calc_secondquad(map, player, drawer);
		return ;
	}
	if (drawer->ray_angle >= M_PI && drawer->ray_angle < (M_PI + M_PI_2))
	{
		calc_thirdquad(map, player, drawer);
		return ;
	}
	calc_fourthquad(map, player, drawer);
}


// char	check_barrier(t_map *map, t_player *player, t_drawer *drawer)
// {	
// 	if (drawer->barrier_d[0] < 0 || drawer->barrier_d[0] >= map->width ||
// 		drawer->barrier_d[1] < 0 || drawer->barrier_d[1] >= map->height)
// 		return (1);
// 	drawer->mapid = drawer->barrier_d[0] + map->width * drawer->barrier_d[1];
// 	if (map->field[drawer->mapid] == '1' ||
// 		map->field[drawer->mapid] == '2' ||
// 		map->field[drawer->mapid] == '3')
// 		return (1);
// 	return (0);
// }

char	check_barrier(t_map *map, t_player *player, t_drawer *drawer)
{	
	if (drawer->barrier_d[0] < 0 || drawer->barrier_d[0] >= 64 ||
		drawer->barrier_d[1] < 0 || drawer->barrier_d[1] >= 64)
		return (1);
	//drawer->mapid = drawer->barrier_d[0] + 64 * drawer->barrier_d[1];
	if (map->elem[drawer->barrier_d[1]][drawer->barrier_d[0]].number >=0)//field[drawer->mapid] == '1' ||
		//map->field[drawer->mapid] == '2' ||
		//map->field[drawer->mapid] == '3')
		return (1);
	return (0);
}

void	def_barrierparam(t_player *player, t_drawer *drawer, char bitquad)
{
	drawer->raylen[0] = calc_raylen(player, drawer, 0);
	drawer->raylen[1] = calc_raylen(player, drawer, 1);
	if (drawer->raylen[1] < drawer->raylen[0])
	{
		drawer->raylen[0] = drawer->raylen[1];
		drawer->barrier_f[0][0] = drawer->barrier_f[1][0];
		drawer->barrier_f[0][1] = drawer->barrier_f[1][1];
		if (bitquad & 0b110)
			drawer->barrier_f[0][1] -= 1;
		return ;
	}
	if (bitquad & 0b1100)
		drawer->barrier_f[0][0] -= 1;
}

double	calc_raylen(t_player *player, t_drawer *drawer, char index)
{
	double	ray_len;

	ray_len = sqrt(pow(drawer->barrier_f[index][0] - player->obj.pos.x, 2) +
		pow(drawer->barrier_f[index][1] - player->obj.pos.y, 2));
	return (ray_len);
}

void	def_walltile(t_map *map, t_drawer *drawer)
{
	drawer->barrier_d[0] = drawer->barrier_f[0][0];
	drawer->barrier_d[1] = drawer->barrier_f[0][1];
	//drawer->mapid = drawer->barrier_d[0] + 64 * drawer->barrier_d[1];
	//if (map->field[drawer->mapid] == '1')
	//{
	//	drawer->wall_tile = '1';
	//	return ;
	//}
	//if (map->field[drawer->mapid] == '2')
	//{
	//	drawer->wall_tile = '2';
	//	return ;
	//}
	//drawer->wall_tile = '3';
	drawer->wall_tile = map->elem[drawer->barrier_d[1]][drawer->barrier_d[0]].number;
}

void	def_walltile_u(t_drawer *drawer)
{
	drawer->texel[0] = drawer->barrier_f[0][0] -
		(int)(drawer->barrier_f[0][0] + 0.5);
	drawer->texel[1] = drawer->barrier_f[0][1] -
		(int)(drawer->barrier_f[0][1] + 0.5);
	if (fabs(drawer->texel[1]) > fabs(drawer->texel[0]))
	{
		drawer->tex_u = (int)(drawer->texel[1] * 64);
		drawer->wall_part = 0;
	}
	else
	{
		drawer->tex_u = (int)(drawer->texel[0] * 64);
		drawer->wall_part = 1;
	}
	if (drawer->tex_u < 0)
		drawer->tex_u += 64;
}
