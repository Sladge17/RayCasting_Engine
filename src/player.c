/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/07/20 19:12:59 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	init_player(t_game *game)
{
	t_vec2 pos;
	float rad;

	pos.x = 4.5f;
	pos.y = 3.5f;
	init_object(&(game->player.obj),  pos, 0, 0.1, 2);
	game->player.sec.fov = 60;
	game->player.sec.ang_step = game->player.sec.fov / S_W;
	rad = (game->player.obj.rot + (game->player.sec.fov / 2.0f)) * M_PI / 180;
	game->player.sec.r_ang.x = sin(rad);
	game->player.sec.r_ang.y = cos(rad);
	rad = (game->player.obj.rot - (game->player.sec.fov / 2.0f)) * M_PI / 180;
	game->player.sec.l_ang.x = sin(rad);
	game->player.sec.l_ang.y = cos(rad);
}
