/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_draw_menu.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/08/11 14:17:36 by vkaron           ###   ########.fr       */
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

void	draw_number(t_game *game, int n, SDL_Rect *pos)
{
	char *str;

	str = ft_itoa(n);
	if (str)
	{
		print_ttf(game->surf, str, 18, pos);
		pos->x += ft_strlen(str) * 10;
		free(str);
	}
}

void	draw_text(t_game *game, char *str, SDL_Rect *pos)
{
	print_ttf(game->surf, str, 18, pos);
	pos->x += ft_strlen(str) * 12;
}

void	draw_cursor_info(t_game *game, t_editor *ed)
{
	SDL_Rect	pos;
	t_map_elem	*el;
	
	pos.x = 10;
	pos.y = S_H - 61;
	draw_text(game, "Cursor: pos[", &pos);
	draw_number(game, ed->cursor.pos.y, &pos);
	draw_text(game, ":", &pos);
	draw_number(game, ed->cursor.pos.x, &pos);
	draw_text(game, "] select cursor type = ", &pos);
	if (ed->cursor.en->type == NONE)
		draw_text(game, "NONE", &pos);
	else if (ed->cursor.en->type == PLAYER)
		draw_text(game, "PLAYER", &pos);
	else if (ed->cursor.en->type == WALL)
		draw_text(game, "WALL", &pos);
	else if (ed->cursor.en->type == DOOR)
		draw_text(game, "DOOR", &pos);
	else if (ed->cursor.en->type == ENEMY)
		draw_text(game, "ENEMY", &pos);
	else if (ed->cursor.en->type == ACHIV)
		draw_text(game, "ACHIV", &pos);
	else if (ed->cursor.en->type == BARIER)
		draw_text(game, "BARIER", &pos);
	else if (ed->cursor.en->type == ENTOURAGE)
		draw_text(game, "ENTOURAGE", &pos);
	//
	pos.x = 10;
	pos.y = S_H - 22;
	el = &ed->map.elem[ed->cursor.pos.y][ed->cursor.pos.x];
	draw_text(game, "map type = ", &pos);
	draw_number(game, ed->type_map[ed->cursor.pos.y][ed->cursor.pos.x], &pos);
	//if (el->type == WALL)
	{
		draw_text(game, " element map = ", &pos);
		draw_number(game, el->number, &pos);
		draw_text(game, " [", &pos);
		draw_number(game, el->side[0], &pos);
		draw_text(game, ", ", &pos);
		draw_number(game, el->side[1], &pos);
		draw_text(game, ", ", &pos);
		draw_number(game, el->side[2], &pos);
		draw_text(game, ", ", &pos);
		draw_number(game, el->side[3], &pos);
		draw_text(game, "] modify = ", &pos);
		draw_number(game, el->modify, &pos);
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
	draw_cursor_info(game, ed);
}
