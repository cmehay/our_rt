/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   downscale.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmehay <cmehay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/17 11:57:02 by cmehay            #+#    #+#             */
/*   Updated: 2014/03/18 19:04:34 by cmehay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	get_average(t_env *e, int x, int y)
{
	int	x_c;
	int	y_c;
	t_rgb	color;
	t_rgb	tmp;

	ft_bzero(&color, sizeof(t_rgb));
	x_c = 1 << e->screen.upscale;

	while (x_c--)
	{
		y_c = 1 << e->screen.upscale;
		while (y_c--)
		{
			tmp = pixel_to_rgb(mlx_get_px_img_render(e, x + x_c, y + y_c));
			color.red += tmp.red;
			color.green += tmp.green;
			color.blue += tmp.blue;
		}
	}
	color.red = color.red >> (e->screen.upscale << 1);
	color.green = color.green >> (e->screen.upscale << 1);
	color.blue = color.blue >> (e->screen.upscale << 1);
	return (rgb_to_pixel(color));
}

void		downscale(t_env *e)
{
	int		x;
	int		y;
	int		pixel;
	int		upscale;

	upscale = e->screen.upscale;
	x = (int)e->screen.display.w;
	while (x--)
	{
		y = (int)e->screen.display.h;
		while (y--)
		{
			pixel = get_average(e, x << upscale, y << upscale);
			mlx_put_px_img_display(e, x, y, pixel);
		}
	}
}
