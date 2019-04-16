/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infos.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 22:44:06 by cmartine          #+#    #+#             */
/*   Updated: 2018/09/20 02:29:44 by cmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

static char		*buttons_click(char *str, int x, int y, int c)
{
	int alpha;
	int r;
	int x1;
	int y1;

	alpha = 0;
	r = 15;
	x1 = x;
	y1 = y;
	while (alpha <= 360)
	{
		x = x + r * cos(alpha);
		y = y + r * sin(alpha);
		((int *)str)[x + ((int)WIDTH * y)] = c;
		alpha++;
		x = x1;
		y = y1;
	}
	fill_with_color((int *)str, x1, y1, c);
	return ((char *)str);
}

static void		infos_click(char *str, int x, int y, int c)
{
	int real_x;
	int	real_y;

	real_x = x;
	real_y = y;
	while (y-- > HEIGHT - 130)
		draw_pixel(str, x, y, c);
	y = real_y + 17;
	while (y-- > HEIGHT - 130)
		draw_pixel(str, x + 230, y, c);
	x = real_x - 1;
	while (x++ < real_x + 230)
		draw_pixel(str, x, y, c);
	x = real_x + 17;
	while (x++ < real_x + 230)
		draw_pixel(str, x, real_y + 16, c);
	fill_with_color((int *)str, real_x + 20, real_y - 20, c);
}

void			infos(t_struct *param)
{
	if (param->key.i == 0)
	{
		buttons_click(param->opt.img_str, 30, HEIGHT - 30, 0xFFFFFF);
	}
	if (param->key.i == 1)
	{
		buttons_click(param->opt.img_str, 30, HEIGHT - 30, 0xFFFFFF);
		infos_click(param->opt.img_str, 15, HEIGHT - 32, 0xFFFFFF);
	}
}

static void		stringss(t_struct *p)
{
	if (p->opt.fract == 't')
		mlx_string_put(p->mlx_ptr, p->win_ptr, 25, HEIGHT - 121, 0, "TRICORN");
	if (p->opt.fract == 'n')
		mlx_string_put(p->mlx_ptr, p->win_ptr, 25, HEIGHT - 121, 0, "NEWTON");
	mlx_string_put(p->mlx_ptr, p->win_ptr, 25, HEIGHT - 73, 0, "iterations :");
	mlx_string_put(p->mlx_ptr, p->win_ptr, 148, HEIGHT - 73, 0x4682B4,
			ft_itoa(p->opt.ite_max));
	mlx_string_put(p->mlx_ptr, p->win_ptr, 25, HEIGHT - 98, 0, "zoom :");
	mlx_string_put(p->mlx_ptr, p->win_ptr, 90, HEIGHT - 98, 0x4682B4,
			ft_ftoa(p->opt.zoom));
}

void			strings(t_struct *p)
{
	mlx_string_put(p->mlx_ptr, p->win_ptr, 25, HEIGHT - 41, 0, "I");
	if (p->key.i == 1)
	{
		mlx_string_put(p->mlx_ptr, p->win_ptr, 25, HEIGHT - 41, 0,
				"INFORMATIONS");
		if (p->opt.fract == 'm')
			mlx_string_put(p->mlx_ptr, p->win_ptr, 25, HEIGHT - 121, 0,
					"MANDELBROT");
		if (p->opt.fract == 'j')
			mlx_string_put(p->mlx_ptr, p->win_ptr, 25, HEIGHT - 121, 0,
					"JULIA");
		if (p->opt.fract == 'd')
			mlx_string_put(p->mlx_ptr, p->win_ptr, 25, HEIGHT - 121, 0,
					"DOUADY");
		if (p->opt.fract == 'b')
			mlx_string_put(p->mlx_ptr, p->win_ptr, 25, HEIGHT - 121, 0,
					"BURNING SHIP");
		if (p->opt.fract == 'c')
			mlx_string_put(p->mlx_ptr, p->win_ptr, 25, HEIGHT - 121, 0,
					"CELTIC CROWN");
		if (p->opt.fract == 'g')
			mlx_string_put(p->mlx_ptr, p->win_ptr, 25, HEIGHT - 121, 0,
					"GALAXY");
		stringss(p);
	}
}
