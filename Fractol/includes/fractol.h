/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolomoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 19:39:49 by akolomoi          #+#    #+#             */
/*   Updated: 2019/01/25 19:39:50 by akolomoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# include <math.h>
# include <mlx.h>
# include "../libft/libft.h"
# include <stdlib.h>
# include <pthread.h>

# define WIN_WIDTH				1000
# define WIN_HEIGHT				1000
# define THREADS				4

# define INVALID_PARAM			1
# define UNKNOWN_FRACTAL_NAME	2
# define MLX_FAILED				3
# define TOO_MANY_PARAMS		4

# define MANDELBROT				0xf1
# define JULIA					0xf2
# define BRNSHP					0xf3
# define CELTIC					0xf4

# define SCH_BLACK_WHITE		0xc1
# define SCH_ACID_GREEN			0x37F9a0
# define SCH_ACID_RED			0xFF1E1E
# define SCH_ACID_BLUE			0x000aFF
# define SCH_ACID_PURP			0x7900FF
# define SCH_RAINBOW			0x3C71C7
# define SCH_BWY				0xff9933
# define SCH_BWL				0xccffcc
# define SCH_BWP				0xccccff

typedef struct	s_param
{
	double		real;
	double		img;
	double		doub;
	double		prime_real;
	double		prime_img;
	int			x;
	int			y;
}				t_param;

typedef struct	s_offset
{
	double		min_x;
	double		max_x;
	double		min_y;
	double		max_y;
	double		zoom;
}				t_offset;

typedef struct	s_calc
{
	int			thread_no;
	void		*img_ptr;
	int			rows_in_process;
	int			starting_row;
	int			iterations;
	t_offset	offset;
	double		sx;
	double		sy;
	int			col_scheme;
	t_param		julia;
}				t_calc;

typedef struct	s_mouse
{
	int			x;
	int			y;
	int			l_x;
	int			l_y;
	int			m;
}				t_mouse;

typedef struct	s_fr
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*img_adr;
	int			rows_per_thread;
	t_calc		c[THREADS];
	t_mouse		mouse;
	int			id;
	int			col;
	void		(*render)(struct s_fr *fr);
}				t_fr;

void			die(int reason);
void			create_window(t_fr *fr);
void			do_mandelbrot(t_fr *fr);
void			do_julia(t_fr *fr);
void			do_celtic(t_fr *fr);
void			do_burningship(t_fr *fr);
int				keyboard_events(int k, t_fr *fr);
int				mouse_hook(int code, int x, int y, t_fr *fr);
int				exit_btn(void *param);
void			get_func(t_fr *fr);
t_offset		get_offset(int fractal);
t_param			*get_param(t_param *p, int x, int y, t_offset o);
int				get_col(int n, int scheme);
void			zoom(int x, int y, t_fr *fr, double z);
int				mouse_move(int x, int y, t_fr *fr);
int				mouse_hook(int code, int x, int y, t_fr *fr);
int				m_release(int button, int x, int y, t_fr *fr);
void			controls();

#endif
