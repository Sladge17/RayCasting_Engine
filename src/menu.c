/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/09/10 16:19:55 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	print_wolf(SDL_Surface *sdest, const char *text,
	SDL_Rect *dest)
{
	SDL_Color	col;
	TTF_Font	*fnt;
	SDL_Surface	*stext;
	const char	*f = "prgres/wf.otf";

	col = (SDL_Color){171, 32, 46, 255};
	fnt = NULL;
	fnt = TTF_OpenFont(f, H_H / 5);
	if (!fnt)
	{
		write(1, "Not open font!\n", 15);
		exit(0);
	}
	stext = TTF_RenderText_Blended(fnt, text, col);
	SDL_BlitSurface(stext, NULL, sdest, dest);
	SDL_FreeSurface(stext);
	TTF_CloseFont(fnt);
	dest->y += H_H / 5;
}

void	draw_menu(t_game *game)
{
	SDL_Point	pos;
	int			index;
	SDL_Rect	r;
	int flag = 1;
	
	pos.y = -1;
	while (++pos.y < S_H)
	{
		index = pos.y * S_W;
		pos.x = -1;
		while(++pos.x < S_W)
		{
			game->data[index + pos.x] = game->data_menu[index + pos.x];
		}
	}
	r = (SDL_Rect){H_W + H_W / 2, H_H - 20, 0, 0};
	if (flag)
		print_wolf(game->surf, "Continue", &r);
	else
		print_wolf(game->surf, "", &r);
	print_wolf(game->surf, "New game", &r);
	print_wolf(game->surf, "Settings", &r);
	print_wolf(game->surf, "Editor", &r);
	print_wolf(game->surf, "Exit", &r);
}

void	main_menu(t_game *game)
{
	SDL_Point	flags;
	SDL_Event	e;
	SDL_Rect r;

	flags.x = 0;
	flags.y = 1;
	r.h = 100;
	r.w = 100;
	r.x = 0;
	r.y = 0;
	//init_editor(&ed);
	while (!flags.x)
	{
		if (SDL_PollEvent(&e) != 0)
			sld_events_menu(game, e, &flags);
		if (flags.y)
		{
			//SDL_FillRect(game->menu, NULL, 0xFFFF0000);
            
			//draw_map_editor(game, &ed);
			//draw_col_frame(game, &ed, ed.cursor.pos, 0xFFFF0000);
			//draw_menu(game, &ed);
			//status_selector(game, &ed);
            //SDL_BlitSurface(game->menu, NULL, game->surf, NULL);
			draw_menu(game);
			SDL_UpdateWindowSurface(game->win);
			flags.y = 0;
		}
		SDL_Delay(5);
	}
    if (flags.x == 1)
	    game->status = 0;
}