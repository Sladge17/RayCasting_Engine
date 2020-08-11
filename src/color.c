/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/07/27 18:29:03 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void 	set_color(SDL_Color *col, int r, int g, int b)
{

	col->r = r;
	col->g = g;
	col->b = b;
}

int		clamp_col(int col)
{
	if(col < 0)
		return (0);
	if(col > 255)
		return (255);
	return col;
}

void	set_col_by_num(SDL_Color *col, int number)
{
	number++;
	if(number == 1)
		set_color(col, 140, 140, 140);
	else if(number == 2)
		set_color(col, 84, 84, 84);
	else if(number == 3)
		set_color(col, 140, 140, 140);
	else if(number == 4)
		set_color(col, 84, 84, 84);
	else if(number == 5)
		set_color(col, 180, 0, 0);
	else if(number == 6)
		set_color(col, 132, 0, 0);
	else if(number == 7)
		set_color(col, 240, 148, 92);
	else if(number == 8)
		set_color(col, 208, 128, 80);
	else if(number == 9)
		set_color(col, 0, 0, 176);
	else if(number == 10)
		set_color(col, 0, 0, 44);
	else if(number == 11)
		set_color(col, 236, 232, 0);
	else if(number == 12)
		set_color(col, 148, 144, 0);
	else if(number == 13)
		set_color(col, 0, 0,176);
	else if(number == 14)
		set_color(col, 0, 0, 44);
	else if(number == 15)
		set_color(col, 0, 0, 176);
	else if(number == 16)
		set_color(col, 0, 0, 44);
	else
		set_color(col, 255, 255, 255);
}

