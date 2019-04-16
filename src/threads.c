/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 01:09:22 by cmartine          #+#    #+#             */
/*   Updated: 2018/09/14 00:52:59 by cmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

pthread_t	create_threads(t_struct *param, int i, double x)
{
	pthread_t	threads;

	param->th_opt[i].x_th = x;
	param->th_opt[i].nb_th = i;
	param->th_opt[i].fract = param->opt.fract;
	param->th_opt[i].zoom = param->opt.zoom;
	param->th_opt[i].ite_max = param->opt.ite_max;
	param->th_opt[i].move_x = param->opt.move_x;
	param->th_opt[i].move_y = param->opt.move_y;
	param->th_opt[i].j.i = param->opt.j.i;
	param->th_opt[i].j.r = param->opt.j.r;
	param->th_opt[i].img_str = param->opt.img_str;
	pthread_create(&threads, NULL, (void *)fractals, (void *)&param->th_opt[i]);
	return (threads);
}

void		threads(t_struct *param)
{
	pthread_t	th[NBTHREAD];
	int			i;
	double		x;

	i = 0;
	x = 0;
	while (i < NBTHREAD)
	{
		th[i] = create_threads(param, i, x);
		x += WIDTH / NBTHREAD;
		i++;
	}
	i = 0;
	while (i < NBTHREAD)
		pthread_join(th[i++], NULL);
}
