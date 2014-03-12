/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-segu <sde-segu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/25 07:09:13 by sde-segu          #+#    #+#             */
/*   Updated: 2014/02/25 07:09:14 by sde-segu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		raytracer(t_env *e, t_data **scene)
{
	int		color;

	e->go_h = -HEIGHT / 2;
	while (e->go_h < HEIGHT / 2)
	{
		e->go_w = -WIDTH / 2;
		while (e->go_w < WIDTH / 2)
		{
			size_ray(e);
			id_object(e, *scene);
			if (e->red != 0 || e->green != 0 || e->blue != 0)
				check_light(e, scene);
			color = (e->red * 256 * 256) + (e->green * 256) + e->blue;
			mlx_put_px_img(e, e->go_w + WIDTH / 2, e->go_h + HEIGHT / 2, color);
			e->go_w++;
		}
		e->go_h++;
	}
	return (0);
}

int		size_ray(t_env *e)
{
	e->x = e->screen_length;
	e->y = e->screen_width * e->go_w / WIDTH;
	e->z = e->screen_height * e->go_h / HEIGHT;
	e->len = sqrt(e->x * e->x + e->y * e->y + e->z * e->z);
	e->vect_x = e->x / e->len;
	e->vect_y = e->y / e->len;
	e->vect_z = -e->z / e->len;
	return (0);
}

int		id_object(t_env *e, t_data *scene)
{
	e->inter = -1;
	e->red = 0;
	e->green = 0;
	e->blue = 0;
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
