/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmehay <cmehay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/17 16:56:53 by cmehay            #+#    #+#             */
/*   Updated: 2014/03/17 17:28:06 by cmehay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_color	pixel_to_color(int pixel)
{
	t_color	color;

	color.red = pixel >> 16;
	color.green = (pixel << 16) >> 24;
	color.blue = (pixel << 24) >> 24;
	return (color);
}

int		color_to_pixel(t_color color)
{
	int	pixel;

	pixel = color.red << 16;
	pixel += color.green << 8;
	pixel += color.blue;
	return (pixel);
}
