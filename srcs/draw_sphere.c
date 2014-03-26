/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sphere.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmehay <cmehay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/25 07:09:25 by sde-segu          #+#    #+#             */
/*   Updated: 2014/03/26 15:09:16 by dcouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		rt_sphere(t_env *e, t_data *scene)
{
	e->a = pow((e->vect.x), 2) + pow((e->vect.y), 2) + pow((e->vect.z), 2);
	e->b = 2 * ((e->vect.x) * (e->cam.x - scene->pos.x)
		+ e->vect.y * (e->cam.y - scene->pos.y)
			+ (e->vect.z) * (e->cam.z - scene->pos.z));
	e->c = (pow((e->cam.x - scene->pos.x), 2)
		+ pow((e->cam.y - scene->pos.y), 2) + pow((e->cam.z - scene->pos.z), 2)
			- pow(scene->radius, 2));
	e->ray.delta = pow(e->b, 2) - 4 * e->a * e->c;
	if (e->ray.delta >= 0)
		get_inter_to_print(e, scene);
	return (0);
}

int		get_inter_to_print(t_env *e, t_data *scene)
{
	float	inter1;
	float	inter2;

	inter1 = (-e->b + sqrt(e->ray.delta)) / (2 * e->a);
	inter2 = (-e->b - sqrt(e->ray.delta)) / (2 * e->a);
	inter2 = (fmin(inter1, inter2) > 0.01) ? fmin(inter1, inter2)
		: fmax(inter1, inter2);
	if (((e->ray.inter == -1) || e->ray.inter > inter2) && inter2 > 0.01)
	{
		e->ray.inter = inter2;
		e->object = 1;
		e->heart_sphere[0] = scene->pos.x;
		e->heart_sphere[1] = scene->pos.y;
		e->heart_sphere[2] = scene->pos.z;
		e->color.red = scene->rgb[0];
		e->color.green = scene->rgb[1];
		e->color.blue = scene->rgb[2];
	}
	return (0);
}
