/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolomoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 18:10:07 by akolomoi          #+#    #+#             */
/*   Updated: 2019/02/17 18:10:09 by akolomoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	controls(void)
{
	ft_putendl("\n-----------------------------------");
	ft_putendl("Controls:");
	ft_putendl("          space - change color scheme");
	ft_putendl("  [NumPad]  +   - increase the number of iterations");
	ft_putendl("  [NumPad]  -   - decrease the number of iterations");
	ft_putendl("  [MouseWheel]  - zoom in/out");
	ft_putendl("  [Mouse]   LMB - hold & drag to move");
	ft_putendl("  [Arrows]  Up  - zoom in");
	ft_putendl("  [Arrows] Down - zoom out");
	ft_putendl("            Esc - exit");
	ft_putendl("-----------------------------------\n");
}

void	die(int reason)
{
	if (reason == INVALID_PARAM)
	{
		ft_putendl("----------------\nInvalid params.\n----------------");
	}
	if (reason == UNKNOWN_FRACTAL_NAME)
	{
		ft_putendl("----------------\nBad fractal name.\n----------------");
	}
	if (reason == TOO_MANY_PARAMS)
	{
		ft_putendl("----------------\nToo many params.\n----------------");
	}
	if (reason == MLX_FAILED)
	{
		ft_putendl("----------------\nMLX failed.\n----------------");
	}
	ft_putendl("\nUsage: ./fractol [fractal_name]");
	ft_putendl("\nAvailable fractals: mandelbrot");
	ft_putendl("                    julia");
	ft_putendl("                    burningship");
	ft_putendl("                    celtic\n");
	system("leaks -quiet fractol | grep \"total leaked bytes\"");
	exit(1);
}
