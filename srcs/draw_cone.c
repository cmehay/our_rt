/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_cone.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmehay <cmehay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/02 03:09:31 by sde-segu          #+#    #+#             */
/*   Updated: 2014/03/23 15:33:03 by cmehay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	rt_cone(t_env *e, t_data *scene)
{
	t_pos	v;
	t_pos	o;
	t_pos	a;

	o.x = e->cam.x - scene->pos.x;
	o.z = e->cam.z - scene->pos.z;
	o.y = e->cam.y - scene->pos.y;
	v.x = e->vect.x;
	v.z = e->vect.z;
	v.y = e->vect.y;
	a.x = e->angle[0];
	a.y = -e->angle[1];
	a.z = e->angle[2];
	rt_rotate_x(&a, &v, &o, e);
	rt_rotate_y(&a, &v, &o, e);
	rt_rotate_z(&a, &v, &o, e);
	rt_rotate(scene, &v, &o, e);
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
		e->angle_ob.x = scene->angle.x;
		e->angle_ob.y = scene->angle.y;
		e->angle_ob.z = scene->angle.z;
		e->heart_sphere[0] = scene->pos.x;
		e->heart_sphere[1] = scene->pos.y;
		e->heart_sphere[2] = scene->pos.z;
		e->ray.inter = inter2;
		e->object = 4;
		e->color.red = scene->rgb[0];
		e->color.green = scene->rgb[1];
		e->color.blue = scene->rgb[2];
	}
	return (0);
}

void	lightcone(t_env *e, t_data *scene)
{
	float	len;
	t_pos	nor;
	t_pos	p;
	float	scal;

	nor.x = e->inter.x - e->heart_sphere[0];
	nor.y = e->inter.y - e->heart_sphere[1];
	nor.z = 0;
	len = sqrt(nor.x * nor.x + nor.y * nor.y + nor.z * nor.z);
	e->normal.x = nor.x / len;
	e->normal.y = nor.y / len;
	e->normal.z = nor.z / len;
	p.x = e->shadowray.x;
	p.y = e->shadowray.y;
	p.z = e->shadowray.z;
	rt_rotate(scene, &nor, &p, e);
	scal = (e->normal.x * p.x + e->normal.y * p.y
			+ e->normal.z * p.z) / (e->ray.len / 50);
	scal = (scal > 1) ? 1 : scal;
	scal = (scal < 0.05) ? 0.05 : scal;
	e->light *= scal;
}

int		size_light_on_cone(t_env *e, t_data *scene)
{
	t_pos	v;
	t_pos	i;
	t_pos	p;
	t_pos	a;
	t_pos	z;

	a.x = e->angle[0];
	a.y = -e->angle[1];
	a.z = e->angle[2];
	v.x = e->shadowray.x;
	v.y = e->shadowray.y;
	v.z = e->shadowray.z;
	i.x = e->inter.x;
	i.y = e->inter.y;
	i.z = e->inter.z;
	p.x = scene->pos.x;
	p.y = scene->pos.y;
	p.z = scene->pos.z;
	rt_rotate_x(&a, &v, &i, e);
	rt_rotate_x(&a, &z, &p, e);
	rt_rotate_y(&a, &v, &i, e);
	rt_rotate_y(&a, &z, &p, e);
	rt_rotate_z(&a, &v, &i, e);
	rt_rotate_z(&a, &z, &p, e);
	rt_rotate(scene, &v, &i, e);
	rt_rotate(scene, &z, &p, e);
	e->a = pow((v.x), 2) + pow((v.y), 2)
		- pow((v.z), 2) * pow(scene->radius, 2) / 100;
	e->b = 2 * ((v.x) * (i.x - p.x)
			+ v.y * (i.y - p.y)
			- (v.z) * (i.z - p.z) * pow(scene->radius, 2) / 100);
	e->c = pow((i.x - p.x), 2)
		+ pow((i.y - p.y), 2)
		- pow((i.z - p.z), 2) * pow(scene->radius, 2) / 100;
	e->ray.delta_light = pow(e->b, 2) - (4 * e->a * e->c);
	return (get_light_to_print(e));
}
