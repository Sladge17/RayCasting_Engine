/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/09/09 10:25:10 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	draw_menu(t_game *game)
{
	SDL_Point	pos;
	int			index;

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