/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_cone.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmehay <cmehay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/02 03:09:31 by sde-segu          #+#    #+#             */
/*   Updated: 2014/03/15 17:17:14 by dcouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	rt_cone(t_env *e, t_data *scene)
{
	float	mem;
	float	vx;
	float	vz;
	float	vy;
	float	ox;
	float	oz;
	float	oy;

	ox = e->cam.x - scene->pos.x;
	oz = e->cam.z - scene->pos.z;
	oy = e->cam.y - scene->pos.y;
	vx = e->vect.x;
	vz = e->vect.z;
	vy = e->vect.y;

	if (scene->angle.y)
	{
		mem = e->vect.x;
		vx = cos(scene->angle.y * M_PI / 180) * mem - sin(scene->angle.y * M_PI     / 180) * e->vect.z;
		vz = sin(scene->angle.y * M_PI / 180) * mem + cos(scene->angle.y * M_PI     / 180) * e->vect.z;
		mem = ox;
		ox = cos(scene->angle.y * M_PI / 180) * mem - sin(scene->angle.y * M_PI     / 180) * oz;
		oz = sin(scene->angle.y * M_PI / 180) * mem + cos(scene->angle.y * M_PI     / 180) * oz;
	}
	if (scene->angle.x)
	{
		mem = vy;
		vy = cos(scene->angle.x * M_PI / 180) * mem + sin(scene->angle.x * M_PI     / 180) * vz;
		vz = sin(scene->angle.x * M_PI / 180) * mem * -1 + cos(scene->angle.x *     M_PI / 180) * vz;
		mem = oy;
		oy = cos(scene->angle.x * M_PI / 180) * mem + sin(scene->angle.x * M_PI     / 180) * oz;
		oz = sin(scene->angle.x * M_PI / 180) * mem * -1 + cos(scene->angle.x *     M_PI / 180) * oz;
	}
	ox = scene->pos.x + ox;
	oy = scene->pos.y + oy;
	oz = scene->pos.z + oz;
	e->a = pow((vx), 2) + pow((vy), 2)
		- pow((vz), 2) * pow(scene->radius, 2) / 100;
	e->b = 2 * ((vx) * (ox - scene->pos.x)
			+ vy * (oy - scene->pos.y)
			- (vz) * (oz - scene->pos.z) * pow(scene->radius, 2) / 100);
	e->c = pow((ox - scene->pos.x), 2)
		+ pow((oy - scene->pos.y), 2)
		- pow((oz - scene->pos.z), 2) * pow(scene->radius, 2) / 100;
	e->ray.delta = pow(e->b, 2) - (4 * e->a * e->c);
	get_cone_to_print(e, scene);
}

int		get_cone_to_print(t_env *e, t_data *scene)
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
		e->object = 3;
		e->color.red = scene->rgb[0];
		e->color.green = scene->rgb[1];
		e->color.blue = scene->rgb[2];
	}
	return (0);
}

void	size_light_on_cone(t_env *e, t_data *scene)
{
	e->a = pow((e->shadowray.x), 2) + pow((e->shadowray.y), 2)
		- pow((e->shadowray.z), 2);
	e->b = 2 * ((e->shadowray.x) * (e->inter.x - scene->pos.x)
		+ e->shadowray.y * (e->inter.y - scene->pos.y)
		+ (e->shadowray.z) * (e->inter.z - scene->pos.z));
	e->c = pow((e->inter.x - scene->pos.x), 2)
		+ pow((e->inter.y - scene->pos.y), 2)
		- pow((e->inter.z - scene->pos.z), 2);
	e->ray.delta = pow(e->b, 2) - 4 * e->a * e->c;
	get_light_to_print(e);
}
