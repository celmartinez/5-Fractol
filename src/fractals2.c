/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 00:49:38 by cmartine          #+#    #+#             */
/*   Updated: 2018/09/20 01:58:07 by cmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

void	*douady(t_options *opt, double x, double y, int color)
{
	t_complex	z;
	t_complex	c;
	double		ite;
	double		tmp;

	color = 0;
	c.r = -0.123;
	c.i = 0.74;
	z.r = ((x * 4.0 / WIDTH - 2.0) / opt->zoom) + (opt->move_x / WIDTH);
	z.i = ((y * 4.0 / WIDTH - 2.0) / opt->zoom) + (opt->move_y / WIDTH);
	ite = -1;
	while (z.r * z.r + z.i * z.i < 4 && ite++ < opt->ite_max)
	{
		tmp = z.r;
		z.r = z.r * z.r - z.i * z.i + c.r;
		z.i = 2.0 * z.i * tmp + c.i;
	}
	if (ite - 1 == opt->ite_max)
		draw_pixel(opt->img_str, x, y, 0);
	else
	{
		color = (int)(ite * 50000000.0 / opt->ite_max * 2);
		draw_pixel(opt->img_str, x, y, color);
	}
	return (0);
}

void	*galaxy(t_options *opt, double x, double y, int color)
{
	t_complex	z;
	t_complex	c;
	double		ite;
	double		tmp;

	c.r = -0.88;
	c.i = 0.22;
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
		color += ((int)(ite * 7000000.0 / opt->ite_max * 2));
		draw_pixel(opt->img_str, x, y, color);
	}
	return (0);
}

void	*newton(t_options *opt, double x, double y, int ite)
{
	t_complex	z;
	t_complex	n;
	double		tmp;
	double		calc;

	z.r = ((x * 4.0 / WIDTH - 2.0) / opt->zoom) + (opt->move_x / WIDTH);
	z.i = ((y * 4.0 / WIDTH - 2.0) / opt->zoom) + (opt->move_y / WIDTH);
	ite = -1;
	while (ite++ < opt->ite_max)
	{
		tmp = z.r;
		n.r = z.r * z.r;
		n.i = z.i * z.i;
		if ((calc = 3.0 * ((n.r - n.i) * (n.r - n.i) + 4.0 * (n.r * n.i))) == 0)
			calc = 0.000001;
		z.r = (2.0 / 3.0) * z.r + (n.r - n.i) / calc;
		z.i = (2.0 / 3.0) * z.i - 2.0 * tmp * z.i / calc;
	}
	if (z.r > 0.0)
		draw_pixel(opt->img_str, x, y, 0x00CCCC);
	else if (z.r < -0.3 && z.i > 0.0)
		draw_pixel(opt->img_str, x, y, 0xFF0033);
	else
		draw_pixel(opt->img_str, x, y, 0xFFCC00);
	return (0);
}

void	*tricorn(t_options *opt, double x, double y, int color)
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
		z.i = z.i * tmp * -2.0 + c.i;
	}
	if (ite == opt->ite_max)
		draw_pixel(opt->img_str, x, y, 0);
	else
	{
		color = (int)(ite * 5000000.0 / opt->ite_max * 2.0);
		draw_pixel(opt->img_str, x, y, color);
	}
	return (0);
}

void	*celtic(t_options *opt, double x, double y, int color)
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
		z.r = fabs(z.r * z.r - z.i * z.i) + c.r;
		z.i = fabs(tmp) * z.i * -2.0 + c.i;
	}
	if (ite == opt->ite_max)
		draw_pixel(opt->img_str, x, y, 0);
	else
	{
		color = (int)(ite * 50000000.0 / opt->ite_max * 2.0);
		draw_pixel(opt->img_str, x, y, color);
	}
	return (0);
}
