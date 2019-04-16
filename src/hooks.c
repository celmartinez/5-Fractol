/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/07 23:48:34 by cmartine          #+#    #+#             */
/*   Updated: 2018/09/20 23:27:14 by cmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

static int		mouse_hook(int button, int x, int y, t_struct *p)
{
	if (button == 1 && p->opt.ite_max >= 1)
		p->opt.ite_max += 5.0;
	if (button == 2 && p->opt.ite_max >= 0)
		p->opt.ite_max -= 5.0;
	if (button == 4)
	{
		x = x - (WIDTH / 2);
		y = y - (WIDTH / 2);
		p->opt.zoom = (p->opt.zoom + 1.0) * 1.1;
		p->opt.move_x += (double)x / p->opt.zoom / 1.5;
		p->opt.move_y += (double)y / p->opt.zoom / 1.5;
	}
	if (button == 5 && p->opt.zoom >= 1 && p->opt.ite_max > 10)
	{
		if (p->opt.zoom == 1)
			p->opt.zoom = 1.5;
		p->opt.zoom = (p->opt.zoom - 1.0) / 1.1;
	}
	draw_fractal(p);
	return (0);
}

static int		mouse_move_hook(int x, int y, t_struct *p)
{
	if (p->key.space == 0 && x > 0 && x < WIDTH && y > 0 && y < HEIGHT)
	{
		p->opt.j.r = 4.0 * (double)x / (WIDTH - 2.0);
		p->opt.j.i = 4.0 * (double)y / (HEIGHT - 2.0);
	}
	draw_fractal(p);
	return (0);
}

static int		key_press_hook(int key, t_struct *p)
{
	if (key == 53)
	{
		mlx_destroy_image(p->mlx_ptr, p->img_ptr);
		mlx_destroy_window(p->mlx_ptr, p->win_ptr);
		ft_memdel((void *)p);
		exit(EXIT_SUCCESS);
	}
	if (key == 49 && p->key.space == 1)
		p->key.space = 0;
	else if (key == 49 && p->key.space == 0)
		p->key.space = 1;
	if (key == 34)
		p->key.i = 1;
	if (key == 124)
		p->opt.move_x -= 20.0 / p->opt.zoom;
	if (key == 123)
		p->opt.move_x += 20.0 / p->opt.zoom;
	if (key == 126)
		p->opt.move_y += 20.0 / p->opt.zoom;
	if (key == 125)
		p->opt.move_y -= 20.0 / p->opt.zoom;
	draw_fractal(p);
	return (0);
}

static int		key_release_hook(int key, t_struct *p)
{
	if (key == 34)
		p->key.i = 0;
	draw_fractal(p);
	return (0);
}

void			hook_types(t_struct *p)
{
	mlx_mouse_hook(p->win_ptr, mouse_hook, p);
	mlx_hook(p->win_ptr, KEYPRESS, KEYPRESSMASK, key_press_hook, p);
	mlx_hook(p->win_ptr, KEYRELEASE, KEYRELEASEMASK, key_release_hook, p);
	if (p->opt.fract == 'j' && p->key.space == 0)
		mlx_hook(p->win_ptr, MOTIONNOTIFY, PMOTIONMASK, mouse_move_hook, p);
}
