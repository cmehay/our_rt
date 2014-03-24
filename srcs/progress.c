/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   progress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmehay <cmehay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/23 20:37:30 by cmehay            #+#    #+#             */
/*   Updated: 2014/03/23 21:47:14 by cmehay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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
		ft_putnbr(display);
		ft_putchar('%');
	}
}

void	display_done(void)
{
	int	i;

	i = 5;
	while (i--)
		ft_putchar(8);
	ft_putendl("Done!");
}
