/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/07/27 18:11:42 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		key_press4(SDL_Keycode key, t_game *game)
{
	if (key == SDLK_f)
	{
		game->dummy = 22;
		return (0);
	}
	return (1);
}

int		key_press3(SDL_Keycode key, t_game *game)
{
	return (key_press4(key, game));
}

int			key_press2(SDL_Keycode key, t_game *game)
{
	if (key == SDLK_m)
	{
		if (game->draw_map)
			game->draw_map = 0;
		else
			game->draw_map = 1;
	}
	//	turn_left(&(game->player.obj));
	//else if (key == SDLK_RIGHT)
	//	turn_right(&(game->player.obj));
	//else if (key == SDLK_UP)
		//move_forward(&(game->player.obj), &game->level.map);
	//else if (key == SDLK_DOWN)
	//	move_back(&(game->player.obj), &game->level.map);
	//else if (key == SDLK_a)
	//	move_left(&(game->player.obj), &game->level.map);
	//else if (key == SDLK_d)
	//	move_right(&(game->player.obj), &game->level.map);
	//else 
	if (key == SDLK_k)
		game->dummy = 7;
	return (key_press3(key, game));
}

int		key_press(SDL_Keycode key, t_game *game)
{
	return (key_press2(key, game));
}
