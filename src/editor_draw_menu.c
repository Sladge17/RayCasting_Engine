/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_draw_menu.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/09/09 10:26:45 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	draw_preview(t_game *game, t_editor *ed, int i, SDL_Rect rect)
{
	int			pos;

	pos = (i * 35 + 6) * S_W - 310;
	rect.h = 30;
	rect.w = 100;
	rect.y = i * 35 + 6;
	rect.x = S_W - 310;
	if (i == 0)
		draw_box(game, pos, ed->player.it[ed->player.cur], ed);
	else if (i == 1)
		SDL_FillRect(game->surf, &rect, ed->map.roof);
	else if (i == 2)
		SDL_FillRect(game->surf, &rect, ed->map.floor);
	else if (i == 3)
		draw_box(game, pos, ed->wall.it[ed->wall.cur], ed);
	else if (i == 4)
		draw_box(game, pos, ed->door.it[ed->door.cur], ed);
	else if (i == 5)
		draw_box(game, pos, ed->enemy.it[ed->enemy.cur], ed);
	else if (i == 6)
		draw_box(game, pos, ed->achiv.it[ed->achiv.cur], ed);
	else if (i == 7)
		draw_box(game, pos, ed->barier.it[ed->barier.cur], ed);
	else if (i == 8)
		draw_box(game, pos, ed->entourage.it[ed->entourage.cur], ed);
}

void	draw_text_menu(t_game *game, t_editor *ed)
{
	const char	*labels[15] = {"Hero", "Ceil color", "Floor color", "Wall",
	"Door", "Enemy", "Achiev", "Barier", "Entourage", "PICK", "CLEAR",
	"EDIT", "SAVE", "LOAD", "HELP"};
	SDL_Rect	rect;
	int			i;
	int			scale;

	rect.x = S_W - 190;
	rect.y = 15;
	i = -1;
	scale = ed->scale;
	ed->scale = 32;
	while (++i < 15)
	{
		print_ttf(game->surf, labels[i], 18, &rect);
		if (i < 9 || i == 11)
			rect.y += 35;
		if (i > 8 && i != 11)
			rect.x += 100;
		if (i == 8 || i == 11)
			rect.x = S_W - 300;
		if (i < 9)
			draw_preview(game, ed, i, rect);
	}
	ed->scale = scale;
}

void	draw_editor_menu(t_game *game, t_editor *ed)
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
	draw_text_menu(game, ed);
	draw_cursor_info(game, ed);
}
