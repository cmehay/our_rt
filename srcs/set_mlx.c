/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_mlx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmehay <cmehay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/25 07:09:38 by sde-segu          #+#    #+#             */
/*   Updated: 2014/03/13 15:38:03 by cmehay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		set_mlx(t_env *e, t_data *scene)
{
	e->mlx = (t_mlx*)malloc(sizeof(t_mlx));
	e->mlx->mlx = mlx_init();
	e->mlx->win = mlx_new_window(e->mlx->mlx, WIDTH, HEIGHT, "raytracer");
	e->mlx->img = mlx_new_image(e->mlx->mlx, WIDTH, HEIGHT);
	e->mlx->data = mlx_get_data_addr(e->mlx->img, &(e->mlx->bpp),
		&(e->mlx->line), &(e->mlx->endian));
	e->screen.length = 20;
	e->screen.width = 20;
	e->screen.height = 10;
	e->cam.x = scene->pos.x;
	e->cam.y = scene->pos.y;
	e->cam.z = scene->pos.z;
	e->angle[0] = scene->angle.x;
	e->angle[1] = scene->angle.y;
	e->angle[2] = scene->angle.z;
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
	mlx_put_image_to_window(e->mlx->mlx, e->mlx->win, e->mlx->img, 0, 0);
	return (0);
}

int		mlx_put_px_img(t_env *e, int x, int y, int color)
{
	if (x >= 0 && x <= WIDTH && y >= 0 && y <= HEIGHT)
		ft_memcpy(&(e->mlx->data[y * WIDTH * 4 + x * 4]), &color, 4);
	return (0);
}
