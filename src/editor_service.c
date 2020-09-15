/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_service.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/09/15 09:36:23 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

Uint32	get_img_color(t_game *game, int x, int y, int number)
{
	int row;
	int col;
	int index;

	row = number / 16;
	col = number - row * 16;
	index = (row * 65 + y) * game->athlas->w + col * 65 + x;
	return (game->data_img[index]);
}

void	draw_box(t_game *game, int index, int number, t_editor *ed)
{
	SDL_Point	ofs;
	int			y_index;
	Uint32		col;

	ofs.y = -1;
	while (++ofs.y < ed->scale)
	{
		y_index = ofs.y * S_W;
		ofs.x = -1;
		while (++ofs.x < ed->scale)
		{
			if (number >= 0)
				col = get_img_color(game, ofs.x * 64 / ed->scale,
					ofs.y * 64 / ed->scale, number);
			else
				col = ed->map.floor;
			if (col == 0x980088)
				col = ed->map.floor;
			game->data[index + y_index + ofs.x] = col;
		}
	}
}

void	print_ttf(SDL_Surface *sdest, const char *text,
	int size, SDL_Rect *dest)
{
	SDL_Color	col;
	TTF_Font	*fnt;
	SDL_Surface	*stext;
	const char	*f = "prgres/courier.ttf";

	col = (SDL_Color){255, 255, 200, 255};
	fnt = NULL;
	fnt = TTF_OpenFont(f, size);
	if (!fnt)
	{
		write(1, "Not open font!\n", 15);
		exit(0);
	}
	stext = TTF_RenderText_Blended(fnt, text, col);
	SDL_BlitSurface(stext, NULL, sdest, dest);
	SDL_FreeSurface(stext);
	TTF_CloseFont(fnt);
}

void	draw_frame(t_game *game, const char *message)
{
	SDL_Rect rect;

	rect.h = 480;
	rect.w = 640;
	rect.y = H_H - 240;
	rect.x = H_W - 320;
	SDL_FillRect(game->surf, &rect, 0xFF606060);
	rect.x += 200;
	rect.y += 10;
	print_ttf(game->surf, message, 18, &rect);
	rect.x = H_W - 40;
	rect.y = H_H + 180;
	rect.h = 50;
	rect.w = 80;
	SDL_FillRect(game->surf, &rect, 0xFF505050);
	rect.x += 30;
	rect.y += 15;
	print_ttf(game->surf, "OK", 18, &rect);
}

void	select_cursor_sprite(t_editor *ed)
{
	if (ed->cur_elem == 0)
		ed->cursor.en = &ed->player;
	else if (ed->cur_elem == 3)
		ed->cursor.en = &ed->wall;
	else if (ed->cur_elem == 4)
		ed->cursor.en = &ed->door;
	else if (ed->cur_elem == 5)
		ed->cursor.en = &ed->enemy;
	else if (ed->cur_elem == 6)
		ed->cursor.en = &ed->achiv;
	else if (ed->cur_elem == 7)
		ed->cursor.en = &ed->barier;
	else if (ed->cur_elem == 8)
		ed->cursor.en = &ed->entourage;
}
