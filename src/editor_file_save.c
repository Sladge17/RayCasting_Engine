/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_file_save.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/09/08 12:32:51 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	write_hex(int fd, char n)
{
	static char	*hex = {"0123456789ABCDEF"};
	int			i;

	i = n & 0xF;
	write(fd, &hex[i], 1);
}

void	write_char(int fd, int data)
{
	static char	*hex = {"0123456789ABCDEF"};
	int			i;

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
	while (shift >= 0)
	{
		i = (data & offset) >> shift;
		write(fd, &hex[i], 1);
		offset = offset >> 4;
		shift -= 4;
	}
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
			write_hex(fd, (char)ed->map.elem[it.y][it.x].modify);
			i = -1;
			while (++i < 4)
				write_char(fd, ed->map.elem[it.y][it.x].side[i]);
			write(fd, "\n", 1);
		}
	}
}

void	save_ed_map(t_editor *ed)
{
	char		file[11];
	int			fd;

	ft_strcpy(file, "maps/map00");
	file[8] = ed->level / 10 + '0';
	file[9] = ed->level % 10 + '0';
	if ((fd = open(file, O_WRONLY)) == -1)
		close(fd);
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC);
	write_fchar(fd, ed->map.roof);
	write_fchar(fd, ed->map.floor);
	write(fd, "0\n", 2);
	write_map(fd, ed);
	close(fd);
}
