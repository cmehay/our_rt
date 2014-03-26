/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   progress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmehay <cmehay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/23 20:37:30 by cmehay            #+#    #+#             */
/*   Updated: 2014/03/26 22:35:53 by cmehay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	color_progress(int percent)
{
	if (percent < 33)
		ft_putstr("\33[31m");
	else if (percent < 66)
		ft_putstr("\33[33m");
	else
		ft_putstr("\33[32m");
	ft_putnbr(percent);
	ft_putstr("\33[39m");
}

void	display_progress(int height, int weight)
{
	static int	size = 0;
	static int	progress = 0;
	static int	display = 0;
	int			percent;
	int			i;

	if (!size)
	{
		size = height * weight;
		ft_putnbr(display);
		ft_putchar('%');
		return ;
	}
	percent = (((float)progress++ / (float)size) * 100);
	if (percent != display)
	{
		i = 5;
		while (i--)
			ft_putchar(8);
		display = percent;
		color_progress(display);
		ft_putchar('%');
	}
}

void	display_done(void)
{
	int	i;

	i = 5;
	while (i--)
		ft_putchar(8);
	ft_putstr("\33[32m");
	ft_putstr("\33[1m");
	ft_putendl("Done!");
	ft_putstr("\33[0m");
	ft_putstr("\33[39m");
}
