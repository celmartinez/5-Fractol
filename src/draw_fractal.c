/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fractal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 22:43:53 by cmartine          #+#    #+#             */
/*   Updated: 2018/09/20 02:17:44 by cmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

int		*fill_with_color(int *str, int x, int y, int c)
{
	if (str[x + (int)WIDTH * y] != c && x + WIDTH * y < WIDTH * HEIGHT)
	{
		str[x + (int)WIDTH * y] = c;
		if (str[x + 1 + (int)WIDTH * y] != c)
			str = fill_with_color(str, x + 1, y, c);
		if (str[x - 1 + (int)WIDTH * y] != c)
			str = fill_with_color(str, x - 1, y, c);
		if (str[x + (int)WIDTH * (y + 1)] != c)
			str = fill_with_color(str, x, y + 1, c);
		if (str[x + (int)WIDTH * (y - 1)] != c)
			str = fill_with_color(str, x, y - 1, c);
	}
	return (str);
}

void	draw_pixel(char *img_str, int x, int y, int color)
{
	int *str;

	str = (int *)img_str;
	if (x + y * WIDTH < HEIGHT * WIDTH)
		str[x + y * (int)WIDTH] = color;
}

void	draw_fractal(t_struct *p)
{
	threads(p);
	infos(p);
	mlx_clear_window(p->mlx_ptr, p->win_ptr);
	mlx_put_image_to_window(p->mlx_ptr, p->win_ptr, p->img_ptr, 0, 0);
	strings(p);
}
