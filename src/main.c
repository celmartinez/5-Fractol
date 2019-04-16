/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/07 23:36:43 by cmartine          #+#    #+#             */
/*   Updated: 2018/09/21 00:31:10 by cmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

static void	options(t_struct *param)
{
	param->opt.zoom = 1;
	param->opt.ite_max = 50;
	param->opt.move_x = -0.5;
	param->opt.move_y = 0;
	param->key.space = 0;
	param->key.i = 0;
	if (param->opt.fract == 'j')
	{
		param->opt.j.i = 0.1;
		param->opt.j.r = 0.3;
	}
}

static void	window(t_struct *p, int bpp, int size_l, int endian)
{
	if (!(p->mlx_ptr = mlx_init()))
	{
		ft_memdel((void *)p);
		perror("mlx init error\n");
		exit(EXIT_FAILURE);
	}
	if (!(p->win_ptr = mlx_new_window(p->mlx_ptr, WIDTH, HEIGHT, "fractol")))
	{
		ft_memdel((void *)p);
		perror("mlx new window error\n");
		exit(EXIT_FAILURE);
	}
	if (!(p->img_ptr = mlx_new_image(p->mlx_ptr, WIDTH, HEIGHT)))
	{
		mlx_destroy_window(p->mlx_ptr, p->win_ptr);
		ft_memdel((void *)p);
		perror("mlx new image error\n");
		exit(EXIT_FAILURE);
	}
	p->opt.img_str = mlx_get_data_addr(p->img_ptr, &bpp, &size_l, &endian);
	options(p);
	hook_types(p);
	draw_fractal(p);
	mlx_loop(p->mlx_ptr);
}

int			main(int argc, char **argv)
{
	t_struct *param;

	if (argc != 2 ||
			(ft_strcmp(argv[1], "m") != 0 && ft_strcmp(argv[1], "j") != 0
			&& ft_strcmp(argv[1], "d") != 0 && ft_strcmp(argv[1], "b") != 0
			&& ft_strcmp(argv[1], "c") != 0 && ft_strcmp(argv[1], "g") != 0
			&& ft_strcmp(argv[1], "n") && ft_strcmp(argv[1], "t")))
	{
		ft_putstr("usage : fractol [fractals]\n fractals :\n ");
		ft_putstr("c --> celtic crown\n b --> burning ship\n d --> douady\n ");
		ft_putstr("g --> galaxy \n j --> julia\n m --> mandelbrot\n ");
		ft_putstr("n --> newton\n t --> tricorn\n");
		return (0);
	}
	if (!(param = (t_struct *)malloc(sizeof(t_struct))))
	{
		perror("malloc error\n");
		exit(EXIT_FAILURE);
	}
	param->opt.fract = argv[1][0];
	window(param, 0, 0, 0);
	return (0);
}
