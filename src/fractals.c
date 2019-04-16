/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 00:04:45 by cmartine          #+#    #+#             */
/*   Updated: 2018/09/20 01:33:34 by cmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

static void	*mandelbrot(t_options *opt, double x, double y, int color)
{
	t_complex	c;
	t_complex	z;
	double		ite;
	double		tmp;

	c.r = ((x * 4.0 / WIDTH - 2.0) / opt->zoom) + (opt->move_x / WIDTH);
	c.i = ((y * 4.0 / WIDTH - 2.0) / opt->zoom) + (opt->move_y / WIDTH);
	z.r = 0;
	z.i = 0;
	ite = -1;
	while (z.r * z.r + z.i * z.i < 4 && ++ite < opt->ite_max)
	{
		tmp = z.r;
		z.r = z.r * z.r - z.i * z.i + c.r;
		z.i = 2 * z.i * tmp + c.i;
	}
	if (ite == opt->ite_max)
		draw_pixel(opt->img_str, x, y, 0);
	else
	{
		color = (ite * 500000000 / opt->ite_max * 2);
		draw_pixel(opt->img_str, x, y, color % 0xFFFFFF);
	}
	return (0);
}

static void	*julia(t_options *opt, double x, double y, int color)
{
	t_complex	z;
	t_complex	c;
	double		ite;
	double		tmp;

	c.r = 0.285 + opt->j.r * 0.1;
	c.i = 0.01 + opt->j.i * 0.1;
	z.r = ((x * 4.0 / WIDTH - 2.0) / opt->zoom) + (opt->move_x / WIDTH);
	z.i = ((y * 4.0 / WIDTH - 2.0) / opt->zoom) + (opt->move_y / WIDTH);
	ite = 0;
	while (z.r * z.r + z.i * z.i < 4 && ite < opt->ite_max)
	{
		tmp = z.r;
		z.r = z.r * z.r - z.i * z.i + c.r;
		z.i = 2.0 * z.i * tmp + c.i;
		ite++;
	}
	if (ite == opt->ite_max)
		draw_pixel(opt->img_str, x, y, 0);
	else
	{
		color += (ite * 500000000 / opt->ite_max * 2);
		draw_pixel(opt->img_str, x, y, color);
	}
	return (0);
}

static void	*burningship(t_options *opt, double x, double y, int color)
{
	t_complex	c;
	t_complex	z;
	double		ite;
	double		tmp;

	c.r = ((x * 8.0 / WIDTH - 4.0) / opt->zoom) + (opt->move_x / WIDTH);
	c.i = ((y * 8.0 / WIDTH - 4.0) / opt->zoom) + (opt->move_y / WIDTH);
	z.r = 0;
	z.i = 0;
	ite = 0;
	while (z.r * z.r + z.i * z.i < (1 << 4) && ite < opt->ite_max)
	{
		tmp = z.r * z.r - z.i * z.i + c.r;
		z.i = fabs(2 * z.i * z.r) + c.i;
		z.r = tmp;
		ite++;
	}
	if (ite == opt->ite_max)
		draw_pixel(opt->img_str, x, y, 0);
	else
	{
		color = ite * 10;
		draw_pixel(opt->img_str, x, y, color);
	}
	return (0);
}

static void	fractal_calc(t_options *th_opt,
		void *ft_fractal(t_options *, double, double, int))
{
	double x;
	double y;
	double tmp;
	double color;

	color = 0xFFFFFF;
	x = th_opt->x_th;
	tmp = x;
	y = 0;
	while (y < HEIGHT)
	{
		x = tmp;
		while (x < (tmp + ((WIDTH / NBTHREAD))))
		{
			ft_fractal(th_opt, x, y, color);
			x++;
		}
		y++;
	}
}

void		*fractals(t_options *th_opt)
{
	if (th_opt->fract == 'm')
		fractal_calc(th_opt, &mandelbrot);
	if (th_opt->fract == 'j')
		fractal_calc(th_opt, &julia);
	if (th_opt->fract == 'b')
		fractal_calc(th_opt, &burningship);
	if (th_opt->fract == 'd')
		fractal_calc(th_opt, &douady);
	if (th_opt->fract == 'g')
		fractal_calc(th_opt, &galaxy);
	if (th_opt->fract == 'n')
		fractal_calc(th_opt, &newton);
	if (th_opt->fract == 't')
		fractal_calc(th_opt, &tricorn);
	if (th_opt->fract == 'c')
		fractal_calc(th_opt, &celtic);
	return (NULL);
}
