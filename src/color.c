/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/09/14 16:59:24 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	set_color(SDL_Color *col, int r, int g, int b)
{
	col->r = r;
	col->g = g;
	col->b = b;
}

int		clamp_col(int col)
{
	if (col < 0)
		return (0);
	if (col > 255)
		return (255);
	return (col);
}
