/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolomoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 17:21:28 by akolomoi          #+#    #+#             */
/*   Updated: 2019/01/28 17:21:30 by akolomoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int			get_col(int n, int scheme)
{
	if (scheme == SCH_BLACK_WHITE)
		return (n % 2 * 0xffffff);
	else if (scheme == SCH_ACID_GREEN || scheme == SCH_ACID_RED)
		return (scheme + (n % 25) * 25);
	else if (scheme == SCH_ACID_BLUE || scheme == SCH_ACID_PURP)
		return (scheme - (n % 25) * 5);
	else if (scheme == SCH_RAINBOW)
		return ((n % 7 + 1) * 0x3C71C7);
	else
	{
		n %= 3;
		if (n == 0)
			return (0);
		else if (n == 1)
			return (0xffffff);
		return (scheme);
	}
}

static void	calc_init(t_fr *fr, t_calc *c, int thread_no)
{
	int	tmp;

	c->thread_no = thread_no;
	c->img_ptr = fr->img_adr;
	c->iterations = 50;
	c->starting_row = thread_no * fr->rows_per_thread;
	tmp = c->starting_row + fr->rows_per_thread;
	c->rows_in_process = tmp <= WIN_HEIGHT ? fr->rows_per_thread :
	tmp - WIN_HEIGHT;
	c->offset = get_offset(fr->id);
	c->col_scheme = SCH_ACID_PURP;
}

int			m_release(int code, int x, int y, t_fr *fr)
{
	(void)x;
	(void)y;
	if (code == 1)
		fr->mouse.m = 0;
	return (0);
}

void		get_func(t_fr *fr)
{
	if (fr->id == MANDELBROT)
		fr->render = do_mandelbrot;
	else if (fr->id == JULIA)
		fr->render = do_julia;
	else if (fr->id == BRNSHP)
		fr->render = do_burningship;
	else if (fr->id == CELTIC)
		fr->render = do_celtic;
	fr->render(fr);
}

void		create_window(t_fr *fr)
{
	int		tmp;

	tmp = 32;
	if (!(fr->mlx = mlx_init()) ||
	!(fr->win = mlx_new_window(fr->mlx, WIN_WIDTH, WIN_HEIGHT,
	"Fractol by akolomoi")) ||
	!(fr->img = mlx_new_image(fr->mlx, WIN_WIDTH, WIN_HEIGHT)) ||
	!(fr->img_adr = mlx_get_data_addr(fr->img, &tmp, &tmp, &tmp)))
		die(MLX_FAILED);
	fr->rows_per_thread = (int)ceil((double)WIN_HEIGHT / THREADS);
	tmp = -1;
	while (++tmp < THREADS)
		calc_init(fr, &fr->c[tmp], tmp);
	fr->mouse.x = WIN_WIDTH / 2;
	fr->mouse.y = WIN_HEIGHT / 2;
	fr->mouse.m = 0;
	fr->col = 0;
	get_func(fr);
}
