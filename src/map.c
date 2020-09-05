/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/08/13 20:20:38 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"


static int		hex_to_int(char sym)
{
	static char *hex = {"0123456789ABCDEF"};
	int i;

	i = -1;
	while (++i < 16)
	{
		if (sym == hex[i])
			return (i);
	}
	return (-1);
}

static int		read_base_color(t_map *map, char *data)
{
	int i;
	int	cmp[16];
	
	i = -1;
	while (++i < 16)
		if ((cmp[i] = hex_to_int(data[i])) == -1)
			return (0);
	map->roof = (Uint32)(0xFF000000 | (cmp[2] << 20) | (cmp[3] << 16) |
	(cmp[4] << 12) | (cmp[5] << 8) | (cmp[6] << 4) | cmp[7]);
	map->floor = (Uint32)(0xFF000000 | (cmp[10] << 20) | (cmp[11] << 16) |
	(cmp[12] << 12) | (cmp[13] << 8) | (cmp[14] << 4) | cmp[15]);
	return (1);
}

void			add_enm(t_map * map, SDL_Point pos, int num)
{
	static int number = 0;
	t_vec2 p;
	
	if (number > 127)
		return ;
	map->enm[number].status = 1;
	p.x = pos.x + 0.5;
	p.y = pos.y + 0.5;
	map->enm[number].obj.pos = p;
	map->enm[number].sprt.pos = p;
	map->enm[number++].sprt.numb = num;
}

void			add_bar(t_map * map, SDL_Point pos, int num)
{
	static int number = 0;
	t_vec2 p;
	
	if (number > 63)
		return ;
	map->bar[number].status = 1;
	p.x = pos.x + 0.5;
	p.y = pos.y + 0.5;
	//map->bar[number].obj.pos = p;
	map->bar[number].sprt.pos = p;
	map->bar[number++].sprt.numb = num;
	map->elem[pos.y][pos.x].lock = 1;
}

static int		read_map(t_map *map, char *data, int cell, t_player *pl)
{
	int			s;
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
	if (t == WALL)
	{
		map->elem[p.y][p.x].number = (cmp[1] << 8) | (cmp[2] << 4) | cmp[3];
		map->elem[p.y][p.x].modify = cmp[4];
		map->elem[p.y][p.x].lock = 1;
		i = 2;
		s = 0;
		if (cmp[4])
		{
			while ((i += 3) < 15)
				map->elem[p.y][p.x].side[s++] = (cmp[i] << 8) | (cmp[i + 1] << 4) | cmp[ i + 2];
		}
		else
		{
			map->elem[p.y][p.x].side[0] = map->elem[p.y][p.x].number;
			map->elem[p.y][p.x].side[2] = map->elem[p.y][p.x].number;
			map->elem[p.y][p.x].side[1] = map->elem[p.y][p.x].number + 1;
			map->elem[p.y][p.x].side[3] = map->elem[p.y][p.x].number + 1;
		}
	}
	else
	{
		map->elem[p.y][p.x].number = -1;
		map->elem[p.y][p.x].lock = 0;
		if (t == PLAYER)
		{
			pl->obj.pos.x = p.x + 0.5;
			pl->obj.pos.y = p.y + 0.5;
		}
		else if (t == ENEMY)
			add_enm(map, p,  (cmp[1] << 8) | (cmp[2] << 4) | cmp[3]);
		else if (t == BARIER)
			add_bar(map, p,  (cmp[1] << 8) | (cmp[2] << 4) | cmp[3]);
	}
	return (1);
}
//*
void	load_map(t_level *level, t_player *pl)
{
	int			number;
	char 		file[11];
	int			fd;
	char		buf[18];
	int			n;
	int 		cell;

	number = 1;
	ft_strcpy(file, "maps/map00");
	file[8] = number / 10 + '0';
	file[9] = number % 10 + '0';
	check_segv(file);

	if ((fd = open(file, 0x0000)) < 0)
		ft_exit("Hey man! It is are not a map!!!");
	cell = -2;
	while ((n = read(fd, buf, 18)))
	{
		++cell;
		if (cell == 4096 || n != 18 || buf[17] != '\n' || !read_map(&(level->map), buf, cell, pl))
		{
			close(fd);
			//printf("in %d\n",cell);
			ft_exit("not valid map!");
		}
	}
	close(fd);
	//printf("out %d\n",cell);
	if (cell < 4095)
		ft_exit("not valid map!");
}

