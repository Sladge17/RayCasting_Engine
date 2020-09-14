/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   service_stuff.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/09/09 12:20:58 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	close_sdl(t_game *game)
{
	//write(1,"OK\n", 3);
	if (game->surf)
		SDL_FreeSurface(game->surf);
	
	game->surf = 0;
	//if (game->athlas)
	//	SDL_FreeSurface(game->athlas);
	//write(1,"OK2\n", 4);
	if (game->menu)
		SDL_FreeSurface(game->menu);
	if (game->n_level)
		SDL_FreeSurface(game->n_level);
	if (game->s_win)
		SDL_FreeSurface(game->s_win);
	if (game->win)
		SDL_DestroyWindow(game->win);
	game->win = 0;
	TTF_Quit();
	SDL_Quit();
	
}

int		check_segv(char *file)
{
	int		fd;
	int		ret;
	char	buff[6];

	fd = open(file, O_RDONLY);
	if (!fd)
	{
		//ft_putstr("U TRYINA SEGV ME?\n");
		return (1);
	}
	ret = read(fd, buff, 5);
	if (!ret || ret < 0)
	{
		//ft_putstr("U GIVING BAD FILES ARENT YA?\n");
		return (1);
	}
	return (0);
}

void	ft_exit(char *line)
{
	//close_sdl(t_game *game);
	ft_putstr(line);
	ft_putchar('\n');
	exit(-1);
}

//void	free_l(t_game *game)
//{
//	free(game);
//}

int		free_init_sdl(t_game *game)
{
	close_sdl(game);
	//free_l(game);
	ft_exit("BAD THINGS HAPPENING TO SDL");
	return (-1);
}

int		check_res(void)
{
	static char	*res[7] = {"res/athlas2.png", "res/main_screen.png", "res/music.mp3", "res/next_level.png", "res/win.png", "prgres/courier.ttf", "prgres/wf.otf"};
	int			i;

	i = -1;
	while (++i < 7)
	{
		if (check_segv(res[i]))
		{
			ft_putstr("Resource \"");
			ft_putstr(res[i]);
			ft_putstr("\" are not available!\n");
			return (ERROR);
		}
	}
	return (OK);
}

/*
int		free_word_line(char **line, char **word)
{
	int i;

	i = 0;
	if (word)
	{
		if (word[i])
		{
			while (word[i])
			{
				free(word[i]);
				word[i] = NULL;
				++i;
			}
		}
		free(word);
		word = NULL;
	}
	if (*line)
	{
		free(*line);
		*line = NULL;
	}
	return (i);
}
//*/
