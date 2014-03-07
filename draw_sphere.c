/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sphere.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-segu <sde-segu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/25 07:09:25 by sde-segu          #+#    #+#             */
/*   Updated: 2014/02/25 07:09:25 by sde-segu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		rt_sphere(t_env *e, t_data *scene)
{
	e->a = pow((e->vect_x), 2) + pow((e->vect_y), 2) + pow((e->vect_z), 2);
	e->b = 2 * ((e->vect_x) * (e->cam_x - scene->x)
		+ e->vect_y * (e->cam_y - scene->y)
			+ (e->vect_z) * (e->cam_z - scene->z));
	e->c = (pow((e->cam_x - scene->x), 2)
		+ pow((e->cam_y - scene->y), 2) + pow((e->cam_z - scene->z), 2)
			- pow(scene->radius, 2));
	e->delta = pow(e->b, 2) - 4 * e->a * e->c;
	if (e->delta >= 0)
		get_inter_to_print(e, scene);
	return (0);
}

int		get_inter_to_print(t_env *e, t_data *scene)
{
	float	inter1;
	float	inter2;

	inter1 = (-e->b + sqrt(e->delta)) / (2 * e->a);
	inter2 = (-e->b - sqrt(e->delta)) / (2 * e->a);
	inter2 = (fmin(inter1, inter2) > 0.01) ? fmin(inter1, inter2)
		: fmax(inter1, inter2);
	if (((e->inter == -1) || e->inter > inter2) && inter2 > 0.01)
	{
		e->inter = inter1;
		e->object = 1;
		e->heart_sphere[0] = scene->x;
		e->heart_sphere[1] = scene->y;
		e->heart_sphere[2] = scene->z;
		e->red = scene->rgb[0];
		e->green = scene->rgb[1];
		e->blue = scene->rgb[2];
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

	x = e->interx - e->heart_sphere[0];
	y = e->intery - e->heart_sphere[1];
	z = e->interz - e->heart_sphere[2];
	len = sqrt(x * x + y * y + z * z);
	e->normale_x = x / len;
	e->normale_y = y / len;
	e->normale_z = z / len;
	scal = (e->normale_x * e->shadowray_x + e->normale_y * e->shadowray_y
				+ e->normale_z * e->shadowray_z);
	scal = (scal < 0.2) ? 0.2 : scal;
	e->red *= scal;
	e->green *= scal;
	e->blue *= scal;
}

void	size_light_on_sphere(t_env *e, t_data *scene)
{
	e->a = pow((e->shadowray_x), 2) + pow((e->shadowray_y), 2)
		+ pow((e->shadowray_z), 2);
	e->b = 2 * ((e->shadowray_x) * (e->interx - scene->x)
		+ e->shadowray_y * (e->intery - scene->y)
		+ (e->shadowray_z) * (e->interz - scene->z));
	e->c = (pow((e->interx - scene->x), 2)
		+ pow((e->intery - scene->y), 2)
		+ pow((e->interz - scene->z), 2) - pow(scene->radius, 2));
	e->delta_light = pow(e->b, 2) - 4 * e->a * e->c;
	get_light_to_print(e);
}

void	get_light_to_print(t_env *e)
{
	float	inter;
	float	inter2;

	inter = 0;
	inter2 = 0;
	if (e->delta_light >= 0)
	{
		inter2 = (-e->b + sqrt(e->delta_light)) / (2 * e->a);
		inter = (-e->b - sqrt(e->delta_light)) / (2 * e->a);
		inter = fmin(inter2, inter);
		if (inter > 0.1 && (inter2 < e->lenght))
		{
			e->inter_light = inter;
			if (e->red > 20)
				e->red /= 2;
			if (e->green > 20)
				e->green /= 2;
			if (e->blue > 20)
				e->blue /= 2;
		}
	}
}