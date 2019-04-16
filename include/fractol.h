/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/14 03:25:40 by cmartine          #+#    #+#             */
/*   Updated: 2018/09/21 00:24:44 by cmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../minilibx/mlx.h"
# include "../libft/libft.h"
# include <math.h>
# include <stdlib.h>
# include <pthread.h>

# define WIDTH 800.0
# define HEIGHT 800.0

# define NBTHREAD 20

# define MOTIONNOTIFY 6
# define PMOTIONMASK (1L<<6)
# define KEYPRESS 2
# define KEYRELEASE 3
# define KEYPRESSMASK (1L<<0)
# define KEYRELEASEMASK (1L<<1)

typedef struct	s_complex
{
	double r;
	double i;
}				t_complex;

typedef struct	s_key
{
	int	space;
	int i;
}				t_key;

typedef struct	s_options
{
	char		fract;
	double		zoom;
	double		ite_max;
	double		move_x;
	double		move_y;
	t_complex	j;
	double		x_th;
	int			nb_th;
	char		*img_str;
}				t_options;

typedef struct	s_struct
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	t_options	opt;
	t_key		key;
	t_options	th_opt[NBTHREAD];
}				t_struct;

void			*celtic(t_options *opt, double x, double y, int color);
void			*douady(t_options *opt, double x, double y, int color);
void			draw_fractal(t_struct *p);
void			draw_pixel(char *img_str, int x, int y, int color);
int				*fill_with_color(int *str, int x, int y, int c);
void			*fractals(t_options *th_opt);
void			*galaxy(t_options *opt, double x, double y, int color);
void			hook_types(t_struct *p);
void			infos(t_struct *param);
void			*newton(t_options *opt, double x, double y, int color);
void			strings(t_struct *param);
void			threads(t_struct *param);
void			*tricorn(t_options *opt, double x, double y, int color);

#endif
