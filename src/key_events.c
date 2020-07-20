/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/07/20 18:31:21 by vkaron           ###   ########.fr       */
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
	if (key == SDLK_LEFT)
		turn_left(&(game->player.obj));
	else if (key == SDLK_RIGHT)
		turn_right(&(game->player.obj));
	if (key == SDLK_UP)
		move_forward(&(game->player.obj));
	else if (key == SDLK_DOWN)
		move_back(&(game->player.obj));
	if (key == SDLK_i)
		game->dummy = 5;
	else if (key == SDLK_o)
		game->dummy = 6;
	else if (key == SDLK_k)
		game->dummy = 7;
	return (key_press3(key, game));
}

int		key_press(SDL_Keycode key, t_game *game)
{
	return (key_press2(key, game));
}
