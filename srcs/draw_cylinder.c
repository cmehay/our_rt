/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_cylinder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmehay <cmehay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/02 03:09:23 by sde-segu          #+#    #+#             */
/*   Updated: 2014/03/12 18:09:41 by cmehay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	rt_cylinder(t_env *e, t_data *scene)
{
	e->a = pow((e->vect.x), 2) + pow((e->vect.y), 2);
	e->b = 2 * ((e->vect.x) * (e->cam.x - scene->pos.x)
		+ e->vect.y * (e->cam.y - scene->pos.y));
	e->c = pow((e->cam.x - scene->pos.x), 2)
		+ pow((e->cam.y - scene->pos.y), 2) - pow(scene->radius, 2);
	e->ray.delta = pow(e->b, 2) - (4 * e->a * e->c);
	get_cyl_to_print(e, scene);
}

int		get_cyl_to_print(t_env *e, t_data *scene)
{
	float	inter1;
	float	inter2;

	inter1 = (-e->b + sqrt(e->ray.delta)) / (2 * e->a);
	inter2 = (-e->b - sqrt(e->ray.delta)) / (2 * e->a);
	inter2 = (fmin(inter1, inter2) > 0.01) ? fmin(inter1, inter2)
		: fmax(inter1, inter2);
	if (((e->ray.inter == -1) || e->ray.inter > inter2) && inter2 > 0.01)
	{
		e->ray.inter = inter1;
		e->object = 3;
		e->color.red = scene->rgb[0];
		e->color.green = scene->rgb[1];
		e->color.blue = scene->rgb[2];
	}
	return (0);
}

void	lightcylinder(t_env *e)
{
	float	len;
	float	x;
	float	y;
	float	z;
	float	scal;

	x = e->inter.x - e->heart_sphere[0];
	y = e->inter.y - e->heart_sphere[1];
	z = 0;
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

void	size_light_on_cyl(t_env *e, t_data *scene)
{
	e->a = pow((e->shadowray.x), 2) + pow((e->shadowray.y), 2);
	e->b = 2 * ((e->shadowray.x) * (e->inter.x - scene->pos.x)
		+ e->shadowray.y * (e->inter.y - scene->pos.y));
	e->c = (pow((e->inter.x - scene->pos.x), 2)
		+ pow((e->inter.y - scene->pos.y), 2) - pow(scene->radius, 2));
	e->ray.delta = pow(e->b, 2) - 4 * e->a * e->c;
	get_light_to_print(e);
}