/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_quads.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 15:42:21 by jthuy             #+#    #+#             */
/*   Updated: 2020/09/15 13:40:10 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	calc_firstquad(t_map *map, t_player *player, t_drawer *drawer)
{
	int		i;

	i = 0;
	while (++i < player->ray_depth)
	{
		drawer->barrier_f[0][0] = (int)(player->obj.pos.x + i);
		drawer->barrier_f[0][1] = player->obj.pos.y +
			(drawer->barrier_f[0][0] - player->obj.pos.x) / drawer->ray_tan[0];
		drawer->barrier_d[0] = (int)drawer->barrier_f[0][0];
		drawer->barrier_d[1] = (int)drawer->barrier_f[0][1];
		if (check_barrier(map, drawer))
			break ;
	}
	i = 0;
	while (++i < player->ray_depth)
	{
		drawer->barrier_f[1][1] = (int)(player->obj.pos.y + i);
		drawer->barrier_f[1][0] = player->obj.pos.x +
			(drawer->barrier_f[1][1] - player->obj.pos.y) * drawer->ray_tan[0];
		drawer->barrier_d[0] = (int)drawer->barrier_f[1][0];
		drawer->barrier_d[1] = (int)drawer->barrier_f[1][1];
		if (check_barrier(map, drawer))
			break ;
	}
	def_barrierparam(player, drawer, 0b1);
}

void	calc_secondquad(t_map *map, t_player *player, t_drawer *drawer)
{
	int		i;

	i = 0;
	while (++i < player->ray_depth)
	{
		drawer->barrier_f[0][0] = (int)(player->obj.pos.x + i);
		drawer->barrier_f[0][1] = player->obj.pos.y -
			(drawer->barrier_f[0][0] - player->obj.pos.x) * drawer->ray_tan[1];
		drawer->barrier_d[0] = (int)drawer->barrier_f[0][0];
		drawer->barrier_d[1] = (int)drawer->barrier_f[0][1];
		if (check_barrier(map, drawer))
			break ;
	}
	i = -1;
	while (++i < player->ray_depth)
	{
		drawer->barrier_f[1][1] = (int)(player->obj.pos.y) - i;
		drawer->barrier_f[1][0] = player->obj.pos.x +
			(player->obj.pos.y - drawer->barrier_f[1][1]) / drawer->ray_tan[1];
		drawer->barrier_d[0] = (int)drawer->barrier_f[1][0];
		drawer->barrier_d[1] = (int)drawer->barrier_f[1][1] - 1;
		if (check_barrier(map, drawer))
			break ;
	}
	def_barrierparam(player, drawer, 0b10);
}

void	calc_thirdquad(t_map *map, t_player *player, t_drawer *drawer)
{
	int		i;

	i = -1;
	while (++i < player->ray_depth)
	{
		drawer->barrier_f[0][0] = (int)(player->obj.pos.x) - i;
		drawer->barrier_f[0][1] = player->obj.pos.y -
			(player->obj.pos.x - drawer->barrier_f[0][0]) / drawer->ray_tan[0];
		drawer->barrier_d[0] = (int)drawer->barrier_f[0][0] - 1;
		drawer->barrier_d[1] = (int)drawer->barrier_f[0][1];
		if (check_barrier(map, drawer))
			break ;
	}
	i = -1;
	while (++i < player->ray_depth)
	{
		drawer->barrier_f[1][1] = (int)(player->obj.pos.y) - i;
		drawer->barrier_f[1][0] = player->obj.pos.x -
			(player->obj.pos.y - drawer->barrier_f[1][1]) * drawer->ray_tan[0];
		drawer->barrier_d[0] = (int)drawer->barrier_f[1][0];
		drawer->barrier_d[1] = (int)drawer->barrier_f[1][1] - 1;
		if (check_barrier(map, drawer))
			break ;
	}
	def_barrierparam(player, drawer, 0b100);
}

void	calc_fourthquad(t_map *map, t_player *player, t_drawer *drawer)
{
	int		i;

	i = -1;
	while (++i < player->ray_depth)
	{
		drawer->barrier_f[0][0] = (int)(player->obj.pos.x) - i;
		drawer->barrier_f[0][1] = player->obj.pos.y +
			(player->obj.pos.x - drawer->barrier_f[0][0]) * drawer->ray_tan[1];
		drawer->barrier_d[0] = (int)drawer->barrier_f[0][0] - 1;
		drawer->barrier_d[1] = (int)drawer->barrier_f[0][1];
		if (check_barrier(map, drawer))
			break ;
	}
	i = 0;
	while (++i < player->ray_depth)
	{
		drawer->barrier_f[1][1] = (int)(player->obj.pos.y + i);
		drawer->barrier_f[1][0] = player->obj.pos.x -
			(drawer->barrier_f[1][1] - player->obj.pos.y) / drawer->ray_tan[1];
		drawer->barrier_d[0] = (int)drawer->barrier_f[1][0];
		drawer->barrier_d[1] = (int)drawer->barrier_f[1][1];
		if (check_barrier(map, drawer))
			break ;
	}
	def_barrierparam(player, drawer, 0b1000);
}
