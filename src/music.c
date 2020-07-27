/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   music.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/07/20 19:54:39 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	load_music(t_game *game)
{
	Mix_Music *music = NULL;

	//	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) < 0)
	//	return -1;
			
	//Initialize SDL_mixer 
	if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 ) 
		return -1; 
	
	// Load our sound effect
	//wave = Mix_LoadWAV(WAV_PATH);
	//if (wave == NULL)
		//return -1;
	
	// Load our music
	music = Mix_LoadMUS("res/music.mp3");
	if (music == NULL)
		return -1;
	
	//if ( Mix_PlayChannel(-1, wave, 0) == -1 )
		//return -1;
	
	if ( Mix_PlayMusic( music, -1) == -1 )
		return -1;
		
	//while ( 
	Mix_PlayingMusic();// ) ;
	
	// clean up our resources
	//Mix_FreeChunk(wave);
	//Mix_FreeMusic(music);
	
	// quit SDL_mixer
	//Mix_CloseAudio();
	
	//return 0;
}
