/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   music.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/09/15 10:38:32 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	check_play_music(t_game *game)
{
	if (!game->music.music)
		return ;
	if (game->music.play == 0)
	{
		game->music.play = 1;
		Mix_ResumeMusic();
	}
	else
	{
		game->music.play = 0;
		Mix_PauseMusic();
	}
}

void	close_music(t_game *game)
{
	if (game->music.music)
		Mix_FreeMusic(game->music.music);
	Mix_CloseAudio();
}

void	load_music(t_game *game)
{
	game->music.play = 0;
	game->music.music = NULL;
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
		return ;
	game->music.music = Mix_LoadMUS("res/music.mp3");
	if (game->music.music == NULL)
		return ;
	if (Mix_PlayMusic(game->music.music, -1) == -1)
	{
		Mix_FreeMusic(game->music.music);
		game->music.music = NULL;
		return ;
	}
	while (!Mix_PlayingMusic())
	{
		SDL_Delay(1000);
	}
	game->music.play = 1;
}
