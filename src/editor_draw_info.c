/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_draw_info.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/09/10 14:46:28 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	draw_text(t_game *game, char *str, SDL_Rect *pos)
{
	print_ttf(game->surf, str, 18, pos);
	pos->x += ft_strlen(str) * 12;
}

void	draw_number(t_game *game, int n, SDL_Rect *pos)
{
	char *str;

	str = ft_itoa(n);
	if (str)
	{
		print_ttf(game->surf, str, 18, pos);
		pos->x += ft_strlen(str) * 12;
		free(str);
	}
}

void	draw_text_number(t_game *game, char *str, int n, SDL_Rect *pos)
{
	draw_text(game, str, pos);
	draw_number(game, n, pos);
}

void	draw_cursor_info2(t_game *game, t_editor *ed)
{
	SDL_Rect	pos;
	t_map_elem	*el;

	pos.x = 10;
	pos.y = S_H - 41;
	el = &ed->map.elem[ed->cursor.pos.y][ed->cursor.pos.x];
	draw_text_number(game, "map type = ",
		ed->type_map[ed->cursor.pos.y][ed->cursor.pos.x], &pos);
	draw_text_number(game, " element map = ", el->number, &pos);
	pos.x = 10;
	pos.y = S_H - 21;
	draw_text_number(game, "[", el->side[0], &pos);
	draw_text_number(game, ", ", el->side[1], &pos);
	draw_text_number(game, ", ", el->side[2], &pos);
	draw_text_number(game, ", ", el->side[3], &pos);
	draw_text_number(game, "] modify = ", el->modify, &pos);
}

void	draw_cursor_info(t_game *game, t_editor *ed)
{
	SDL_Rect	pos;

	pos.x = 10;
	pos.y = S_H - 61;
	draw_text_number(game, "Cursor: pos[", ed->cursor.pos.y, &pos);
	draw_text_number(game, ":", ed->cursor.pos.x, &pos);
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
	draw_cursor_info2(game, ed);
}
