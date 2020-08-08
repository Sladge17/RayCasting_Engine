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

void	save_ed_map(t_editor *ed)
{
	SDL_RWops	*rw;
	size_t		len;

	rw = SDL_RWFromFile("maps/map1", "wb");
	if (rw == 0)
	{
		write(1, "file not save!\n", 15);
		return ;
	}
	else
	{
		len = sizeof(ed->map);
		if (SDL_RWwrite(rw, (void *)(&ed->map), len, 1) != len)
			write(1, "File write success!\n", 20);
		else
			write(1, "File bad write!\n", 16);
		SDL_RWclose(rw);
	}
}

void	load_ed_map(t_editor *ed)
{
	SDL_RWops	*rw;
	size_t		len;

	rw = SDL_RWFromFile("maps/map1", "rb");
	if (rw != NULL)
	{
		len = sizeof(ed->map);
		SDL_RWread(rw, &ed->map, len, 1);
		SDL_RWclose(rw);
	}
	else
		write(1, "Not read file!\n", 15);
}
