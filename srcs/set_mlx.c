/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_mlx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-segu <sde-segu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/25 07:09:38 by sde-segu          #+#    #+#             */
/*   Updated: 2014/02/25 07:09:39 by sde-segu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		set_mlx(t_env *e, t_data *scene)
{
	e->mlx = mlx_init();
	e->win = mlx_new_window(e->mlx, WIDTH, HEIGHT, "raytracer");
	e->img = mlx_new_image(e->mlx, WIDTH, HEIGHT);
	e->data = mlx_get_data_addr(e->img, &(e->bpp), &(e->line), &(e->endian));
	e->screen_length = 20;
	e->screen_width = 20;
	e->screen_height = 10;
	e->cam_x = scene->x;
	e->cam_y = scene->y;
	e->cam_z = scene->z;
	e->angle[0] = scene->angle_x;
	e->angle[1] = scene->angle_y;
	e->angle[2] = scene->angle_z;
	return (0);
}

int		key_hook(int keycode)
{
	if (keycode == 65307)
		exit(0);
	return (0);
}

int		expose_hook(t_env *e)
{
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	return (0);
}

int		mlx_put_px_img(t_env *e, int x, int y, int color)
{
	if (x >= 0 && x <= WIDTH && y >= 0 && y <= HEIGHT)
		ft_memcpy(&(e->data[y * WIDTH * 4 + x * 4]), &color, 4);
	return (0);
}