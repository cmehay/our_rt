/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_cone.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmehay <cmehay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/02 03:09:31 by sde-segu          #+#    #+#             */
/*   Updated: 2014/03/16 13:17:58 by cmehay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	rt_cone_set_1(t_env *e, t_data *scene, t_pos *v, t_pos *o)
{
	float	mem;
	t_pos	a;
	t_pos	vect;
	
	vect = e->vect;
	a = scene->angle;
	if (a.y)
	{
		mem = vect.x;
		v->x = cos(a.y * M_PI / 180) * mem - sin(a.y * M_PI / 180) * vect.z;
		v->z = sin(a.y * M_PI / 180) * mem + cos(a.y * M_PI / 180) * vect.z;
		mem = o->x;
		o->x = cos(a.y * M_PI / 180) * mem - sin(a.y * M_PI / 180) * o->z;
		o->z = sin(a.y * M_PI / 180) * mem + cos(a.y * M_PI / 180) * o->z;
	}
	if (a.x)
	{
		mem = v->y;
		v->y = cos(a.x * M_PI / 180) * mem + sin(a.x * M_PI / 180) * v->z;
		v->z = sin(a.x * M_PI / 180) * mem * -1 + cos(a.x * M_PI / 180) * v->z;
		mem = o->y;
		o->y = cos(a.x * M_PI / 180) * mem + sin(a.x * M_PI / 180) * o->z;
		o->z = sin(a.x * M_PI / 180) * mem * -1 + cos(a.x * M_PI / 180) * o->z;
	}
}

void	rt_cone(t_env *e, t_data *scene)
{
	t_pos	v;
	t_pos	o;

	o.x = e->cam.x - scene->pos.x;
	o.z = e->cam.z - scene->pos.z;
	o.y = e->cam.y - scene->pos.y;
	v.x = e->vect.x;
	v.z = e->vect.z;
	v.y = e->vect.y;
	rt_cone_set_1(e, scene, &v, &o);
	o.x = scene->pos.x + o.x;
	o.y = scene->pos.y + o.y;
	o.z = scene->pos.z + o.z;
	e->a = pow((v.x), 2) + pow((v.y), 2)
		- pow((v.z), 2) * pow(scene->radius, 2) / 100;
	e->b = 2 * ((v.x) * (o.x - scene->pos.x)
			+ v.y * (o.y - scene->pos.y)
			- (v.z) * (o.z - scene->pos.z) * pow(scene->radius, 2) / 100);
	e->c = pow((o.x - scene->pos.x), 2)
		+ pow((o.y - scene->pos.y), 2)
		- pow((o.z - scene->pos.z), 2) * pow(scene->radius, 2) / 100;
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
