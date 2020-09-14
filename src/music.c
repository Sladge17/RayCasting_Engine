/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   music.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/09/14 13:55:22 by jthuy            ###   ########.fr       */
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
	//Mix_FreeMusic(music);
	//Mix_CloseAudio();
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

	//	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) < 0)
	//	return -1;
			
	//Initialize SDL_mixer 
	if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 ) 
		return;// -1; 
	
	// Load our sound effect
	//wave = Mix_LoadWAV(WAV_PATH);
	//if (wave == NULL)
		//return -1;
	
	// Load our music
	game->music.music = Mix_LoadMUS("res/music.mp3");
	if (game->music.music == NULL)
		return ;// -1;
	
	//if ( Mix_PlayChannel(-1, wave, 0) == -1 )
		//return -1;
	
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
	//while ( 
	//Mix_PlayingMusic();// ) ;
	
	// clean up our resources
	//Mix_FreeChunk(wave);
	//Mix_FreeMusic(music);
	
	// quit SDL_mixer
	//
	
	//return 0;
	//*/
}
