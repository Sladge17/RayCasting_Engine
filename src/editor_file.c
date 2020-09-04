/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/08/08 22:16:05 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	write_hex(int fd, char n)
{
	static char *hex = {"0123456789ABCDEF"};
	int i;

	i = n & 0xF;
	write(fd, &hex[i], 1);
}

void	write_char(int fd, int data)
{
	static char *hex = {"0123456789ABCDEF"};
	int i;

	i = (data & 0xF00) >> 8;
	write(fd, &hex[i], 1);
	i = (data & 0xF0) >> 4;
	write(fd, &hex[i], 1);
	i = data & 0xF;
	write(fd, &hex[i], 1);
}

void	write_fchar(int fd, int data)
{
	static char *hex = {"0123456789ABCDEF"};
	int			i;
	int			shift;
	Uint32		offset;
	
	shift = 28;
	offset = 0xF0000000;
	while(shift >= 0)
	{
		i = (data & offset) >> shift;
		write(fd, &hex[i], 1);
		offset = offset >> 4;
		shift -= 4;
	}

	//i = (data & 0xF0000000) >> 28;
	//write(fd, &hex[i], 1);
	//i = (data & 0xF000000) >> 24;
	//write(fd, &hex[i], 1);
	//i = (data & 0xF00000) >> 20;
	//write(fd, &hex[i], 1);
	//i = (data & 0xF0000) >> 16;
	//write(fd, &hex[i], 1);
	//i = (data & 0xF000) >> 12;
	//write(fd, &hex[i], 1);
	//i = (data & 0xF00) >> 8;
	///write(fd, &hex[i], 1);
	//i = (data & 0xF0) >> 4;
	//write(fd, &hex[i], 1);
	//i = data & 0xF;
	//write(fd, &hex[i], 1);
}

void	write_map(int fd, t_editor *ed)
{
	SDL_Point	it;
	int			i;

	it.y = -1;
	while (++it.y < 64)
	{
		it.x = -1;
		while (++it.x < 64)
		{
			write_hex(fd, (char)ed->type_map[it.y][it.x]);
			write_char(fd, ed->map.elem[it.y][it.x].number);
			write_hex(fd, (char) ed->map.elem[it.y][it.x].modify);
			i = -1;
			while (++i < 4)
				write_char(fd, ed->map.elem[it.y][it.x].side[i]);
			write(fd, "\n", 1);
		}
	}
}

void	save_ed_map(t_editor *ed, char number)
{
	char 		file[11];
	int			fd;
	char		*buf;

	ft_strcpy(file, "maps/map00");
	file[8] = number / 10 + '0';
	file[9] = number % 10 + '0';
	if ((fd = open(file, O_WRONLY)) == -1)
		close(fd);
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC);
	write_fchar(fd, ed->map.roof);
	write_fchar(fd, ed->map.floor);
	write(fd, "0\n", 2);
	write_map(fd, ed);
	close(fd);
}

int		hex_to_int(char sym)
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

int		read_base_color(t_map *map, char *data)
{
	int tmp;
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
	int			tmp;
	int			i;
	int			cmp[16];
	SDL_Point	p;

	if (cell == -1)
		return (read_base_color(&ed->map, data));
	i = -1;
	while (++i < 16)
		if ((cmp[i] = hex_to_int(data[i])) == -1)
			return (0);
	p.y = cell / 64;
	p.x = cell - p.y * 64;
	if (ed->type_map[p.y][p.x] = cmp[0])
	{
		ed->map.elem[p.y][p.x].number = (cmp[1] << 8) | (cmp[2] << 4) | cmp[3];
		ed->map.elem[p.y][p.x].modify = ed->type_map[p.y][p.x] = cmp[4];
		i = 2;
		while ((i += 3) < 15)
			ed->map.elem[p.y][p.x].side[0] = (cmp[i] << 8) | (cmp[i + 1] << 4) | cmp[ i + 2];
	}
	else
		ed->map.elem[p.y][p.x].number = -1;
	return (1);
}
//*
void	load_ed_map(t_editor *ed)
{
	char number;
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
	//if (((n = read(fd, buf, 18)) != 18) || buf[17] != '\n' || !read_base_color(&ed->map, buf))
	//{
	//	close(fd);
	//	ft_exit("Not valid map!!!");
	//}
	cell = -2;
	while (n = read(fd, buf, 18))
	{
		++cell;
		if (cell == 4096 || n != 18 || buf[17] != '\n' || !read_map(ed, buf, cell))
		{
			close(fd);
			printf("in %d\n",cell);
			ft_exit("not valid map!");
		}
	}
	close(fd);
	printf("out %d\n",cell);
	if (cell < 4095)
		ft_exit("not valid map!");
}
