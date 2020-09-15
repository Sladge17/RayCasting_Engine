/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   service_stuff.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/09/15 10:40:01 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	close_sdl(t_game *game)
{
	if (game->surf)
		SDL_FreeSurface(game->surf);
	game->surf = 0;
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
		return (1);
	}
	ret = read(fd, buff, 5);
	if (!ret || ret < 0)
	{
		return (1);
	}
	return (0);
}

void	ft_exit(char *line)
{
	ft_putstr(line);
	ft_putchar('\n');
	exit(-1);
}

int		free_init_sdl(t_game *game)
{
	close_sdl(game);
	ft_exit("BAD THINGS HAPPENING TO SDL");
	return (-1);
}

int		check_res(void)
{
	static char	*res[7] = {"res/athlas2.png", "res/main_screen.png",
		"res/music.mp3", "res/next_level.png", "res/win.png",
		"prgres/courier.ttf", "prgres/wf.otf"};
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
