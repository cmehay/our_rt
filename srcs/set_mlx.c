/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_mlx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmehay <cmehay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/25 07:09:38 by sde-segu          #+#    #+#             */
/*   Updated: 2014/03/21 20:49:03 by cmehay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	set_screen(t_env *e)
{
	e->screen.upscale = (e->screen.upscale) ? e->screen.upscale : 0;
	e->screen.length = (e->screen.length) ? e->screen.length : PRESET_WIDTH;
	e->screen.display.w = (e->screen.display.w) ? e->screen.display.w
		: PRESET_WIDTH;
	e->screen.display.h = (e->screen.display.h) ? e->screen.display.h
		: PRESET_HEIGHT;
	e->screen.render.w = (int)e->screen.display.w << e->screen.upscale;
	e->screen.render.h = (int)e->screen.display.h << e->screen.upscale;
	e->screen.length = 20;
}

static void	set_mlx_struct(t_env *e)
{
	t_size	dsp;
	t_size	render;


	dsp = e->screen.display;
	render = e->screen.render;
	e->mlx = (t_mlx*)safe_malloc(sizeof(t_mlx));
	e->mlx->mlx = mlx_init();
	e->mlx->win = mlx_new_window(e->mlx->mlx, dsp.w, dsp.h, "raytracer");
	e->mlx->img_display = mlx_new_image(e->mlx->mlx, dsp.w, dsp.h);
	e->mlx->img_render = mlx_new_image(e->mlx->mlx, render.w, render.h);
	e->mlx->data_display = mlx_get_data_addr(e->mlx->img_display,
		&(e->mlx->bpp), &(e->mlx->line), &(e->mlx->endian));
	e->mlx->data_render = mlx_get_data_addr(e->mlx->img_render,
		&(e->mlx->bpp), &(e->mlx->line), &(e->mlx->endian));
}

int		set_mlx(t_env *e, t_data *scene)
{
	set_screen(e);
	set_mlx_struct(e);
	e->cam.x = scene->pos.x;
	e->cam.y = scene->pos.y;
	e->cam.z = scene->pos.z;
	e->angle[0] = scene->angle.x;
	e->angle[1] = scene->angle.y;
	e->angle[2] = scene->angle.z;
	return (0);
}
