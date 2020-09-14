/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_keyboard.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/09/14 19:03:53 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void		draw_im(t_game *game, int *im_data)
{
	SDL_Point	pos;
	int			index;

	pos.y = -1;
	while (++pos.y < S_H)
	{
		index = pos.y * S_W;
		pos.x = -1;
		while (++pos.x < S_W)
		{
			game->data[index + pos.x] = im_data[index + pos.x];
		}
	}
	SDL_UpdateWindowSurface(game->win);
	SDL_Delay(4000);
}

static void		check_door_block(t_game *game)
{
	SDL_Point	p;

	p.x = (int)(game->player.obj.pos.x + game->player.obj.dir.x);
	p.y = (int)(game->player.obj.pos.y + game->player.obj.dir.y);
	if (p.x <= 63 && p.x >= 0 && p.y <= 63 && p.y >= 0 &&
		(game->level.map.elem[p.y][p.x].number == 98 ||
		game->level.map.elem[p.y][p.x].number == 102 ||
		game->level.map.elem[p.y][p.x].number == 104))
	{
		game->level.map.elem[p.y][p.x].number = -1;
		game->level.map.elem[p.y][p.x].lock = 0;
		if (p.y < 63 && game->level.map.elem[p.y + 1][p.x].number != -1)
			game->level.map.elem[p.y + 1][p.x].side[0] = 100;
		if (p.y > 0 && game->level.map.elem[p.y - 1][p.x].number != -1)
			game->level.map.elem[p.y - 1][p.x].side[2] = 100;
		if (p.x < 63 && game->level.map.elem[p.y][p.x + 1].number != -1)
			game->level.map.elem[p.y][p.x + 1].side[3] = 101;
		if (p.x > 0 && game->level.map.elem[p.y][p.x - 1].number != -1)
			game->level.map.elem[p.y][p.x - 1].side[1] = 101;
	}
}

static int		check_exit_block(t_game *game)
{
	SDL_Point	p;
	int			i;

	p.x = (int)(game->player.obj.pos.x + game->player.obj.dir.x);
	p.y = (int)(game->player.obj.pos.y + game->player.obj.dir.y);
	if (p.x <= 63 && p.x >= 0 && p.y <= 63 && p.y >= 0 &&
		game->level.map.elem[p.y][p.x].number == 40)
	{
		i = -1;
		while (++i < 4)
			if (game->level.map.elem[p.y][p.x].side[i] == 41)
				game->level.map.elem[p.y][p.x].side[i] += 2;
		redraw(game);
		SDL_Delay(1000);
		return (1);
	}
	return (0);
}

static void		check_map_block(t_game *game, int *quit)
{
	check_door_block(game);
	if (check_exit_block(game))
	{
		game->delay = 11;
		game->comeback = 0;
		++game->level.num;
		if (game->level.num > MAX_LEVEL)
		{
			*quit = 1;
			game->status = 4;
			draw_im(game, game->data_win);
		}
		else
			draw_im(game, game->data_n_level);
	}
}

void			check_keyboard(t_game *game, float d_time, int *quit)
{
	const	Uint8 *state = SDL_GetKeyboardState(NULL);

	game->comeback = 1;
	if (state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_W])
		move_forward(&(game->player.obj), &game->level.map, d_time);
	else if (state[SDL_SCANCODE_DOWN] || state[SDL_SCANCODE_S])
		move_back(&(game->player.obj), &game->level.map, d_time);
	if (state[SDL_SCANCODE_LEFT])
		turn_left(&(game->player.obj), d_time);
	else if (state[SDL_SCANCODE_RIGHT])
		turn_right(&(game->player.obj), d_time);
	if (state[SDL_SCANCODE_A])
		move_left(&(game->player.obj), &game->level.map, d_time);
	else if (state[SDL_SCANCODE_D])
		move_right(&(game->player.obj), &game->level.map, d_time);
	else if (state[SDL_SCANCODE_SPACE])
		check_map_block(game, quit);
}
