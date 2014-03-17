/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmehay <cmehay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/17 11:26:16 by cmehay            #+#    #+#             */
/*   Updated: 2014/03/17 18:49:04 by cmehay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		key_hook(int keycode)
{
	if (keycode == 65307)
		exit(0);
	return (0);
}

int		expose_hook(t_env *e)
{
	downscale(e);
	mlx_put_image_to_window(e->mlx->mlx, e->mlx->win,
		e->mlx->img_display, 0, 0);
	return (0);
}

int		mlx_put_px_img_render(t_env *e, int x, int y, int color)
{
	t_size	size;

	size = e->screen.render;
	if (x >= 0 && x <= (int)size.w && y >= 0 && y <= (int)size.h)
		ft_memcpy(&(e->mlx->data_render[y * (int)size.w * 4 + x * 4]),
			&color, 4);
	return (0);
}

int		mlx_get_px_img_render(t_env *e, int x, int y)
{
	int		pixel;
	t_size	size;

	pixel = 0;
	size = e->screen.render;
	if (x >= 0 && x <= (int)size.w && y >= 0 && y <= (int)size.h)
		ft_memcpy(&pixel, &(e->mlx->data_render[y * (int)size.w * 4 + x * 4]),
			4);
	return (pixel);
}

int		mlx_put_px_img_display(t_env *e, int x, int y, int color)
{
	t_size	size;

	size = e->screen.display;
	if (x >= 0 && x <= (int)size.w && y >= 0 && y <= (int)size.h)
		ft_memcpy(&(e->mlx->data_display[y * (int)size.w * 4 + x * 4]),
			&color, 4);
	return (0);
}
