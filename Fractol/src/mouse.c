/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolomoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 16:24:36 by akolomoi          #+#    #+#             */
/*   Updated: 2019/02/26 16:24:37 by akolomoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

static double	m(double start, double end, double x)
{
	return (start + ((end - start) * x));
}

void			zoom(int x, int y, t_fr *fr, double z)
{
	int		i;
	double	mx;
	double	my;

	i = -1;
	z = 1.0 / z;
	while (++i < THREADS)
	{
		mx = x / ((double)WIN_WIDTH /
		(fr->c[0].offset.max_x - fr->c[0].offset.min_x))
		+ fr->c[0].offset.min_x;
		my = (double)y / ((double)WIN_HEIGHT /
		(fr->c[0].offset.max_y - fr->c[0].offset.min_y))
		+ fr->c[0].offset.min_y;
		fr->c[i].offset.min_x = m(mx, fr->c[i].offset.min_x, z);
		fr->c[i].offset.max_x = m(mx, fr->c[i].offset.max_x, z);
		fr->c[i].offset.min_y = m(my, fr->c[i].offset.min_y, z);
		fr->c[i].offset.max_y = m(my, fr->c[i].offset.max_y, z);
	}
}

static void		move(t_fr *fr)
{
	int		i;
	double	mx;
	double	my;

	i = -1;
	mx = (double)(fr->mouse.l_x - fr->mouse.x) / ((double)WIN_WIDTH /
	(fr->c[0].offset.max_x - fr->c[0].offset.min_x));
	my = (double)(fr->mouse.l_y - fr->mouse.y) / ((double)WIN_HEIGHT /
		(fr->c[0].offset.max_y - fr->c[0].offset.min_y));
	while (++i < THREADS)
	{
		fr->c[i].offset.min_x += mx;
		fr->c[i].offset.max_x += mx;
		fr->c[i].offset.min_y += my;
		fr->c[i].offset.max_y += my;
	}
}

int				mouse_move(int x, int y, t_fr *fr)
{
	fr->mouse.l_x = fr->mouse.x;
	fr->mouse.l_y = fr->mouse.y;
	fr->mouse.x = x;
	fr->mouse.y = y;
	if (fr->mouse.m == 1)
	{
		move(fr);
		fr->render(fr);
	}
	if (fr->id == JULIA)
		fr->render(fr);
	return (0);
}

int				mouse_hook(int code, int x, int y, t_fr *fr)
{
	if (code == 4)
		zoom(x, y, fr, 1.01);
	else if (code == 5)
		zoom(x, y, fr, 0.99);
	else if (code == 1)
	{
		fr->mouse.m = 1;
		move(fr);
	}
	fr->render(fr);
	return (0);
}
