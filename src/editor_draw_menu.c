/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_draw_menu.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/08/08 21:56:33 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	draw_text_menu(t_game *game)
{
	const char	*labels[15] = {"Hero", "Ceil color", "Floor color", "Wall",
	"Door", "Enemy", "Achiev", "Barier", "Entourage", "PICK", "CLEAR",
	"EDIT", "SAVE", "LOAD", "HELP"};
	SDL_Rect	rect;
	int			i;

	rect.x = S_W - 190;
	rect.y = 15;
	i = -1;
	while (++i < 15)
	{
		print_ttf(game->surf, labels[i], 18, &rect);
		if (i < 9 || i == 11)
			rect.y += 35;
		if (i > 8 && i != 11)
			rect.x += 100;
		if (i == 8 || i == 11)
			rect.x = S_W - 300;
	}
}

void	draw_menu(t_game *game, t_editor *ed)
{
	SDL_Rect rect;

	rect.h = S_H - 65;
	rect.w = 320;
	rect.y = 0;
	rect.x = S_W - 320;
	SDL_FillRect(game->surf, &rect, 0xFF505050);
	rect.h = 64;
	rect.w = S_W;
	rect.y = S_H - 64;
	rect.x = 0;
	SDL_FillRect(game->surf, &rect, 0xFF505050);
	rect.h = 32;
	rect.w = 300;
	rect.y = ed->cur_elem * 35 + 5;
	rect.x = S_W - 310;
	SDL_FillRect(game->surf, &rect, 0xFF707070);
	draw_text_menu(game);
}
