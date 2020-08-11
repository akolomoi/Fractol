/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal-julia.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolomoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 17:34:33 by akolomoi          #+#    #+#             */
/*   Updated: 2019/03/06 17:34:34 by akolomoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

static void		iter(int c, t_param p, void *img_ptr, int col)
{
	int		n;
	double	p_r;
	double	p_i;

	n = -1;
	while (++n < c)
	{
		p_r = p.real * p.real;
		p_i = p.img * p.img;
		p.doub = 2 * p.real * p.img;
		p.real = p_r - p_i + p.prime_real;
		p.img = p.doub + p.prime_img;
		if (p.real * p.real + p.img * p.img > 4.0)
			break ;
	}
	if (n != c)
		*(int*)(img_ptr + (sizeof(int) * (p.x + p.y * WIN_WIDTH))) =
		get_col(n, col);
}

static void		*thread_magic(void *data)
{
	t_calc	c;
	int		i;
	int		x;
	t_param	p;

	c = *(t_calc*)data;
	i = -1;
	c.sx = (c.offset.max_x - c.offset.min_x) / (double)WIN_WIDTH;
	c.sy = (c.offset.max_y - c.offset.min_y) / (double)WIN_HEIGHT;
	while (++i < c.rows_in_process)
	{
		x = -1;
		while (++x < WIN_WIDTH)
		{
			p.real = x * c.sx + c.offset.min_x;
			p.img = (i + c.starting_row) * c.sy + c.offset.min_y;
			p.prime_img = c.julia.prime_img;
			p.prime_real = c.julia.prime_real;
			p.x = x;
			p.y = i + c.starting_row;
			iter(c.iterations, p, c.img_ptr, c.col_scheme);
		}
	}
	pthread_exit(NULL);
}

void			do_julia(t_fr *fr)
{
	pthread_t	t[THREADS];
	int			i;

	i = -1;
	while (++i < THREADS)
	{
		fr->c[i].julia.prime_img = (double)(fr->mouse.l_y)
		/ ((double)WIN_HEIGHT /
		(fr->c[i].offset.max_y - fr->c[i].offset.min_y))
		+ fr->c[i].offset.min_y;
		fr->c[i].julia.prime_real = (double)(fr->mouse.l_x)
		/ ((double)WIN_HEIGHT /
		(fr->c[i].offset.max_x - fr->c[i].offset.min_x))
		+ fr->c[i].offset.min_x;
		pthread_create(&t[i], NULL, thread_magic, (void*)&fr->c[i]);
	}
	i = -1;
	while (++i < THREADS)
		pthread_join(t[i], NULL);
	mlx_put_image_to_window(fr->mlx, fr->win, fr->img, 0, 0);
	ft_bzero(fr->img_adr, WIN_HEIGHT * WIN_WIDTH * sizeof(int));
}
