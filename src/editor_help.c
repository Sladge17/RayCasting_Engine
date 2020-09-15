/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_help.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/09/15 09:21:15 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	draw_editor_help2(t_game *game, SDL_Rect rect, int offs)
{
	print_ttf(game->surf, "-Draw element in map with left mouse key", 18,
		&rect);
	rect.y += offs;
	print_ttf(game->surf, "-Scroll mouse for scale", 18, &rect);
	rect.y += offs;
	print_ttf(game->surf, "-Move map with right mouse key", 18, &rect);
	rect.y += offs;
	print_ttf(game->surf, "-Pick button set cursor from map", 18, &rect);
	rect.y += offs;
	print_ttf(game->surf, "-Clear button set default map", 18, &rect);
	rect.y += offs;
	print_ttf(game->surf, "-Edit button open menu for modify wall", 18, &rect);
	rect.y += offs;
	print_ttf(game->surf, "-Save and load buttons save and load map as file",
		18, &rect);
}

void	draw_editor_help(t_game *game)
{
	SDL_Rect	rect;
	int			offs;

	draw_frame(game, "HELP:");
	rect.y = H_H - 200;
	rect.x = H_W - 310;
	offs = 30;
	print_ttf(game->surf, "-For select element click right mouse key on menu.",
		18, &rect);
	rect.y += offs;
	print_ttf(game->surf, "-Double left click open menu for select", 18,
		&rect);
	rect.y += offs;
	print_ttf(game->surf, "-Arrow keys move cursor", 18, &rect);
	rect.y += offs;
	print_ttf(game->surf, "-Space pick/up cursor for walls / put for other",
		18, &rect);
	rect.y += offs;
	print_ttf(game->surf, "-Key \"A\"-\"Z\" for change element", 18, &rect);
	rect.y += offs;
	print_ttf(game->surf, "-Key \"Q\" for select first element", 18, &rect);
	rect.y += offs;
	draw_editor_help2(game, rect, offs);
}
