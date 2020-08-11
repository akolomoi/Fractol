/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolomoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 19:42:15 by akolomoi          #+#    #+#             */
/*   Updated: 2019/02/19 19:42:17 by akolomoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

static void	iters(t_fr *fr, int c)
{
	int i;

	i = -1;
	while (++i < THREADS)
		fr->c[i].iterations += fr->c[i].iterations + c != 20 ||
		fr->c[i].iterations + c != 150 ? c : 0;
}

static void	swap(t_fr *fr, int val)
{
	int i;

	i = -1;
	while (++i < THREADS)
		fr->c[i].col_scheme = val;
}

static void	change_color(t_fr *fr, int change)
{
	if (change)
		fr->col++;
	fr->col %= 9;
	if (fr->col == 0)
		swap(fr, SCH_BLACK_WHITE);
	else if (fr->col == 1)
		swap(fr, SCH_ACID_GREEN);
	else if (fr->col == 2)
		swap(fr, SCH_ACID_RED);
	else if (fr->col == 3)
		swap(fr, SCH_ACID_BLUE);
	else if (fr->col == 4)
		swap(fr, SCH_ACID_PURP);
	else if (fr->col == 5)
		swap(fr, SCH_RAINBOW);
	else if (fr->col == 6)
		swap(fr, SCH_BWY);
	else if (fr->col == 7)
		swap(fr, SCH_BWL);
	else if (fr->col == 8)
		swap(fr, SCH_BWP);
}

int			keyboard_events(int k, t_fr *fr)
{
	if (k == 53)
		exit_btn(fr);
	else if (k == 69)
		iters(fr, 10);
	else if (k == 78)
		iters(fr, -10);
	else if (k == 49)
		change_color(fr, 1);
	else if (k == 126)
		zoom(fr->mouse.l_x, fr->mouse.l_y, fr, 1.01);
	else if (k == 125)
		zoom(fr->mouse.l_x, fr->mouse.l_y, fr, 0.99);
	fr->render(fr);
	return (0);
}

int			exit_btn(void *param)
{
	t_fr	*f;

	f = (t_fr*)param;
	system("leaks -quiet fractol | grep \"total leaked bytes\"");
	exit(1);
	return (0);
}
