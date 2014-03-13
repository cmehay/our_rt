/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmehay <cmehay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/25 07:09:13 by sde-segu          #+#    #+#             */
/*   Updated: 2014/03/13 16:02:34 by cmehay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		raytracer(t_env *e, t_data **scene)
{
	int		color;

	e->ray.go_h = -HEIGHT / 2;
	while (e->ray.go_h < HEIGHT / 2)
	{
		e->ray.go_w = -WIDTH / 2;
		while (e->ray.go_w < WIDTH / 2)
		{
			size_ray(e);
			id_object(e, *scene);
			if (e->color.red != 0 || e->color.green != 0 || e->color.blue != 0)
				check_light(e, scene);
			color = (e->color.red * 256 * 256) + (e->color.green * 256)
				+ e->color.blue;
			mlx_put_px_img(e, e->ray.go_w + WIDTH / 2, e->ray.go_h + HEIGHT / 2,
				color);
			e->ray.go_w++;
		}
		e->ray.go_h++;
	}
	return (0);
}

int		size_ray(t_env *e)
{
	e->pos.x = e->screen.length;
	e->pos.y = e->screen.width * e->ray.go_w / WIDTH;
	e->pos.z = e->screen.height * e->ray.go_h / HEIGHT;
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
		scene = scene->next;
		if (scene && !ft_strcmp("sphere", scene->what))
			rt_sphere(e, scene);
		if (scene && !ft_strcmp("plan", scene->what))
			rt_plan(e, scene);
		if (scene && !ft_strcmp("cone", scene->what))
			rt_cone(e, scene);
		if (scene && !ft_strcmp("cylinder", scene->what))
			rt_cylinder(e, scene);
	}
	return (0);
}
