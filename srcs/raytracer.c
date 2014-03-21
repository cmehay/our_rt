/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmehay <cmehay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/25 07:09:13 by sde-segu          #+#    #+#             */
/*   Updated: 2014/03/21 20:54:50 by cmehay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		raytracer(t_env *e, t_data **scene)
{
	int		color;

	e->ray.go.h = -(int)e->screen.render.h / 2;
	while (e->ray.go.h < (int)e->screen.render.h / 2)
	{
		e->ray.go.w = -(int)e->screen.render.w / 2;
		while (e->ray.go.w < (int)e->screen.render.w / 2)
		{
			size_ray(e);
			id_object(e, *scene);
			if (e->color.red != 0 || e->color.green != 0 || e->color.blue != 0)
				check_light(e, scene);
			color = rgb_to_pixel(e->color);
			mlx_put_px_img_render(e, e->ray.go.w + (int)e->screen.render.w / 2,
				e->ray.go.h + (int)e->screen.render.h / 2, color);
			e->ray.go.w++;
		}
		e->ray.go.h++;
	}
	return (0);
}

int		size_ray(t_env *e)
{
	float	ratio;

	e->pos.x = 20;
	e->pos.y = 20 * e->ray.go.w / e->screen.render.w;
	ratio = e->screen.render.w / e->screen.render.h;
	if (ratio == 0.00)
		ratio = 0.01;
	e->pos.z = (20 / ratio) * e->ray.go.h / e->screen.render.h;
	e->ray.len = sqrt(e->pos.x * e->pos.x + e->pos.y * e->pos.y
		+ e->pos.z * e->pos.z);
	e->vect.x = e->pos.x / e->ray.len;
	e->vect.y = e->pos.y / e->ray.len;
	e->vect.z = -e->pos.z / e->ray.len;
	return (0);
}

int		id_object(t_env *e, t_data *scene)
{
	e->ray.inter = -1;
	e->color.red = 0;
	e->color.green = 0;
	e->color.blue = 0;
	e->object = 0;
	while (scene)
	{
		if (scene && scene->obj == SPHERE)
			rt_sphere(e, scene);
		if (scene && scene->obj == PLAN)
			rt_plan(e, scene);
		if (scene && scene->obj == CONE)
			rt_cone(e, scene);
		if (scene && scene->obj == CYLINDER)
			rt_cylinder(e, scene);
		scene = scene->next;
	}
	return (0);
}
