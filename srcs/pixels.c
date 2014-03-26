/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmehay <cmehay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/17 16:56:53 by cmehay            #+#    #+#             */
/*   Updated: 2014/03/26 21:35:51 by cmehay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_rgb	pixel_to_rgb(int pixel)
{
	t_rgb			color;
	unsigned int	tmp;

	tmp = pixel;
	color.red = tmp >> 16;
	color.green = (tmp << 16) >> 24;
	color.blue = (tmp << 24) >> 24;
	return (color);
}

int		rgb_to_pixel(t_rgb color)
{
	int	pixel;

	pixel = color.red << 16;
	pixel += color.green << 8;
	pixel += color.blue;
	return (pixel);
}
