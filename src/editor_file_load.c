/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_file_load.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/09/15 09:20:45 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		hex_to_int(char sym)
{
	static char	*hex = {"0123456789ABCDEF"};
	int			i;

	i = -1;
	while (++i < 16)
	{
		if (sym == hex[i])
			return (i);
	}
	return (-1);
}

int		read_base_color(t_map *map, char *data)
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

int		read_map(t_editor *ed, char *data, int cell)
{
	int			cmp[16];
	SDL_Point	p;
	SDL_Point	ind;

	if (cell == -1)
		return (read_base_color(&ed->map, data));
	ind.x = -1;
	while (++ind.x < 17)
		if ((cmp[ind.x] = hex_to_int(data[ind.x])) == -1)
			return (0);
	p.y = cell / 64;
	p.x = cell - p.y * 64;
	if ((ed->type_map[p.y][p.x] = cmp[0]))
	{
		ed->map.elem[p.y][p.x].number = (cmp[1] << 8) | (cmp[2] << 4) | cmp[3];
		ed->map.elem[p.y][p.x].modify = cmp[4];
		ind.x = 2;
		ind.y = 0;
		while ((ind.x += 3) < 15)
			ed->map.elem[p.y][p.x].side[ind.y++] = (cmp[ind.x] << 8) |
				(cmp[ind.x + 1] << 4) | cmp[ind.x + 2];
	}
	else
		ed->map.elem[p.y][p.x].number = -1;
	return (1);
}

int		read_file(int fd, t_editor *ed, int *cell)
{
	int			n;
	char		buf[18];

	*cell = -2;
	while ((n = read(fd, buf, 18)))
	{
		++(*cell);
		if (*cell == 4096 || n != 18 || buf[17] != '\n' || !read_map(ed, buf,
			*cell))
		{
			close(fd);
			return (0);
		}
	}
	return (1);
}

int		load_ed_map(t_editor *ed)
{
	char		file[11];
	int			fd;
	int			cell;

	ft_strcpy(file, "maps/map00");
	file[8] = ed->level / 10 + '0';
	file[9] = ed->level % 10 + '0';
	if (check_segv(file) || ((fd = open(file, 0x0000)) < 0) ||
		!read_file(fd, ed, &cell))
		return (0);
	close(fd);
	if (cell < 4095)
		return (0);
	return (1);
}
