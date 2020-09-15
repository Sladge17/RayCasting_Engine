/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/09/15 10:27:35 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		set_read_wall(t_map *map, int *cmp, SDL_Point *p)
{
	int			s;
	int			i;

	map->elem[p->y][p->x].number = (cmp[1] << 8) | (cmp[2] << 4) | cmp[3];
	map->elem[p->y][p->x].modify = cmp[4];
	map->elem[p->y][p->x].lock = 1;
	i = 2;
	s = 0;
	if (cmp[4])
	{
		while ((i += 3) < 15)
			map->elem[p->y][p->x].side[s++] = (cmp[i] << 8) |
				(cmp[i + 1] << 4) | cmp[i + 2];
	}
	else
	{
		map->elem[p->y][p->x].side[0] = map->elem[p->y][p->x].number;
		map->elem[p->y][p->x].side[2] = map->elem[p->y][p->x].number;
		map->elem[p->y][p->x].side[1] = map->elem[p->y][p->x].number + 1;
		map->elem[p->y][p->x].side[3] = map->elem[p->y][p->x].number + 1;
	}
}

static int	read_map(t_map *map, char *data, int cell, t_player *pl)
{
	int			i;
	int			cmp[16];
	SDL_Point	p;
	t_type		t;

	if (cell == -1)
		return (read_base_color(map, data));
	i = -1;
	while (++i < 17)
		if ((cmp[i] = hex_to_int(data[i])) == -1)
			return (0);
	p.y = cell / 64;
	p.x = cell - p.y * 64;
	t = (t_type)cmp[0];
	if (t == WALL || t == DOOR)
		set_read_wall(map, cmp, &p);
	else
		set_read_sprite(map, cmp, pl, &p);
	return (1);
}

void		set_border(t_map *map)
{
	SDL_Point	p;
	int			s;

	p.y = -1;
	while (++p.y < 64)
	{
		p.x = -1;
		while (++p.x < 64)
		{
			if ((p.x == 0 || p.y == 0 || p.x == 63 || p.y == 63) &&
				map->elem[p.y][p.x].number == -1)
			{
				map->elem[p.y][p.x].number = 0;
				map->elem[p.y][p.x].lock = 1;
				s = -1;
				while (++s < 4)
					map->elem[p.y][p.x].side[s] = 0;
			}
		}
	}
}

int			check_file(t_level *level, int *fd)
{
	char		file[11];

	ft_strcpy(file, "maps/map00");
	file[8] = level->num / 10 + '0';
	file[9] = level->num % 10 + '0';
	if (check_segv(file) || ((*fd = open(file, 0x0000)) < 0))
		return (ERROR);
	level->map.enms = 0;
	level->map.bars = 0;
	level->map.achs = 0;
	level->map.ants = 0;
	return (OK);
}

int			load_map(t_level *level, t_player *pl)
{
	int			fd;
	char		buf[18];
	int			n;
	int			cell;

	if (!check_file(level, &fd))
		return (ERROR);
	cell = -2;
	while ((n = read(fd, buf, 18)))
	{
		++cell;
		if (cell == 4096 || n != 18 || buf[17] != '\n' ||
			!read_map(&(level->map), buf, cell, pl))
		{
			close(fd);
			return (ERROR);
		}
	}
	close(fd);
	if (cell < 4095)
		return (ERROR);
	set_border(&level->map);
	return (OK);
}
