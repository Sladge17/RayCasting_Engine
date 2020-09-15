/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_add_sprite.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/09/15 10:26:23 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	add_enm(t_map *map, SDL_Point pos, int num)
{
	t_vec2 p;

	if (map->enms > 127)
		return ;
	map->enm[map->enms].status = 1;
	p.x = pos.x + 0.5;
	p.y = pos.y + 0.5;
	map->enm[map->enms].obj.pos = p;
	map->enm[map->enms].sprt.pos = p;
	map->enm[(map->enms)++].sprt.numb = num;
}

void	add_bar(t_map *map, SDL_Point pos, int num)
{
	t_vec2 p;

	if (map->bars > 63)
		return ;
	map->bar[map->bars].status = 1;
	p.x = pos.x + 0.5;
	p.y = pos.y + 0.5;
	map->bar[map->bars].sprt.pos = p;
	map->bar[(map->bars)++].sprt.numb = num;
	map->elem[pos.y][pos.x].lock = 1;
}

void	add_ant(t_map *map, SDL_Point pos, int num)
{
	t_vec2 p;

	if (map->ants > 63)
		return ;
	p.x = pos.x + 0.5;
	p.y = pos.y + 0.5;
	map->ant[map->ants].sprt.pos = p;
	map->ant[(map->ants)++].sprt.numb = num;
}

void	add_ach(t_map *map, SDL_Point pos, int num)
{
	t_vec2 p;

	if (map->achs > 63)
		return ;
	p.x = pos.x + 0.5;
	p.y = pos.y + 0.5;
	map->ach[map->achs].sprt.pos = p;
	map->ach[(map->achs)++].sprt.numb = num;
}

void	set_read_sprite(t_map *map, int *cmp, t_player *pl, SDL_Point *p)
{
	t_type t;

	t = (t_type)cmp[0];
	map->elem[p->y][p->x].number = -1;
	map->elem[p->y][p->x].lock = 0;
	if (t == PLAYER)
	{
		pl->obj.pos.x = p->x + 0.5;
		pl->obj.pos.y = p->y + 0.5;
		pl->obj.rot = 0;
		pl->obj.dir.x = 0;
		pl->obj.dir.y = 1;
	}
	else if (t == ENEMY)
		add_enm(map, *p, (cmp[1] << 8) | (cmp[2] << 4) | cmp[3]);
	else if (t == BARIER)
		add_bar(map, *p, (cmp[1] << 8) | (cmp[2] << 4) | cmp[3]);
	else if (t == ENTOURAGE)
		add_ant(map, *p, (cmp[1] << 8) | (cmp[2] << 4) | cmp[3]);
	else if (t == ACHIV)
		add_ach(map, *p, (cmp[1] << 8) | (cmp[2] << 4) | cmp[3]);
}
