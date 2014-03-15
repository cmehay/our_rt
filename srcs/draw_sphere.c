/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sphere.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmehay <cmehay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/25 07:09:25 by sde-segu          #+#    #+#             */
/*   Updated: 2014/03/14 13:33:52 by dcouly           ###   ########.fr       */
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

void	lightsphere(t_env *e)
{
	float	len;
	float	x;
	float	y;
	float	z;
	float	scal;

	x = e->inter.x - e->heart_sphere[0];
	y = e->inter.y - e->heart_sphere[1];
	z = e->inter.z - e->heart_sphere[2];
	len = sqrt(x * x + y * y + z * z);
	e->normal.x = x / len;
	e->normal.y = y / len;
	e->normal.z = z / len;
	scal = (e->normal.x * e->shadowray.x + e->normal.y * e->shadowray.y
		+ e->normal.z * e->shadowray.z);
	scal = (scal < 0.2) ? 0.2 : scal;
	e->color.red *= scal;
	e->color.green *= scal;
	e->color.blue *= scal;
}

void	size_light_on_sphere(t_env *e, t_data *scene)
{
	e->a = pow((e->shadowray.x), 2) + pow((e->shadowray.y), 2)
		+ pow((e->shadowray.z), 2);
	e->b = 2 * ((e->shadowray.x) * (e->inter.x - scene->pos.x)
		+ e->shadowray.y * (e->inter.y - scene->pos.y)
		+ (e->shadowray.z) * (e->inter.z - scene->pos.z));
	e->c = (pow((e->inter.x - scene->pos.x), 2)
		+ pow((e->inter.y - scene->pos.y), 2)
		+ pow((e->inter.z - scene->pos.z), 2) - pow(scene->radius, 2));
	e->ray.delta_light = pow(e->b, 2) - 4 * e->a * e->c;
	get_light_to_print(e);
}

void	get_light_to_print(t_env *e)
{
	float	inter;
	float	inter2;

	inter = 0;
	inter2 = 0;
	if (e->ray.delta_light >= 0)
	{
		inter2 = (-e->b + sqrt(e->ray.delta_light)) / (2 * e->a);
		inter = (-e->b - sqrt(e->ray.delta_light)) / (2 * e->a);
		inter = fmin(inter2, inter);
		if (inter > 0.1 && (inter2 < e->lenght))
		{
			e->ray.inter_light = inter;
			if (e->color.red > 20)
				e->color.red /= 2;
			if (e->color.green > 20)
				e->color.green /= 2;
			if (e->color.blue > 20)
				e->color.blue /= 2;
		}
	}
}
