/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolomoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 19:39:16 by akolomoi          #+#    #+#             */
/*   Updated: 2019/01/25 19:39:17 by akolomoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

t_offset	get_offset(int fractal)
{
	return ((t_offset){-2.5, 2.5, -2.5, 2.5, 1.0});
}

static int	check_names(char *av)
{
	if (!ft_strcmp(av, "mandelbrot"))
		return (MANDELBROT);
	if (!ft_strcmp(av, "julia"))
		return (JULIA);
	if (!ft_strcmp(av, "burningship"))
		return (BRNSHP);
	if (!ft_strcmp(av, "celtic"))
		return (CELTIC);
	return (0);
}

static int	check_params(int ac, char *name)
{
	int id;

	if (ac < 2)
		die(INVALID_PARAM);
	if (!(id = check_names(name)))
		die(UNKNOWN_FRACTAL_NAME);
	return (id);
}

int			main(int ac, char **av)
{
	t_fr	fract;

	if (ac > 2)
		die(TOO_MANY_PARAMS);
	fract.id = check_params(ac, av[1]);
	create_window(&fract);
	controls();
	mlx_hook(fract.win, 2, 1L << 0, keyboard_events, &fract);
	mlx_hook(fract.win, 17, 1L << 17, exit_btn, &fract);
	mlx_hook(fract.win, 6, 1L << 6, mouse_move, &fract);
	mlx_hook(fract.win, 5, 1L << 3, m_release, &fract);
	mlx_mouse_hook(fract.win, mouse_hook, &fract);
	mlx_loop(fract.mlx);
	return (0);
}
