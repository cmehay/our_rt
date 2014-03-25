/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_cone.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmehay <cmehay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/02 03:09:31 by sde-segu          #+#    #+#             */
/*   Updated: 2014/03/25 20:22:15 by dcouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	set_pos_o(t_env *e, t_data *scene, t_pos *o)
{
	o->x = e->cam.x - scene->pos.x;
	o->z = e->cam.z - scene->pos.z;
	o->y = e->cam.y - scene->pos.y;
}

static void	set_pos_v(t_env *e, t_pos *v)
{
	v->x = e->vect.x;
	v->z = e->vect.z;
	v->y = e->vect.y;
}

static void set_pos_a(t_env *e, t_pos *a)
{
	a->x = e->angle[0];
	a->y = -e->angle[1];
	a->z = e->angle[2];
}

void		rt_dcone(t_env *e, t_data *scene)
{
	t_pos	v;
	t_pos	o;
	t_pos	a;

	set_pos_o(e, scene, &o);
	set_pos_v(e, &v);
	set_pos_a(e, &a);
	rt_rotate_x(&a, &v, &o, e);
	rt_rotate_y(&a, &v, &o, e);
	rt_rotate_z(&a, &v, &o, e);
	rt_rotate(scene, &v, &o, e);
	o.x = scene->pos.x + o.x;
	o.y = scene->pos.y + o.y;
	o.z = scene->pos.z + o.z;
	e->a = pow((v.x), 2) + pow((v.y), 2)
		- pow((v.z), 2) * pow(tanf(scene->radius * M_PI / 180), 2);
	e->b = 2 * ((v.x) * (o.x - scene->pos.x)
		+ v.y * (o.y - scene->pos.y) - (v.z) * (o.z - scene->pos.z)
		* pow(tanf(scene->radius * M_PI / 180), 2));
	e->c = pow((o.x - scene->pos.x), 2)
		+ pow((o.y - scene->pos.y), 2) - pow((o.z - scene->pos.z), 2)
		* pow(tanf(scene->radius * M_PI / 180), 2);
	e->ray.delta = pow(e->b, 2) - (4 * e->a * e->c);
	if (e->ray.delta > 0)
		get_dcone_to_print(e, scene);
}

#include <stdio.h>

int			get_dcone_to_print(t_env *e, t_data *scene)
{
	float	min_i;
	float	max_i;
	float	inter1;
	float	inter2;
	float	inter_z;
	float	change;
	t_pos	angle;
	t_pos	inter;
	t_pos	inu;

	angle.x = e->angle[0];
	angle.y = -e->angle[1];
	angle.z = e->angle[2];
	change = 0;
	inter1 = (-e->b + sqrt(e->ray.delta)) / (2 * e->a);
	inter2 = (-e->b - sqrt(e->ray.delta)) / (2 * e->a);
	min_i = fmin(inter1, inter2);
	max_i = fmax(inter1, inter2);
	inter.z = min_i * e->vect.z - scene->pos.z + e->cam.z;
	inter.y = min_i * e->vect.y - scene->pos.y + e->cam.y;
	inter.x = min_i * e->vect.x - scene->pos.x + e->cam.x;
	rt_rotate_x(&angle, &inter, &inu, e);
	rt_rotate_y(&angle, &inter, &inu, e);
	rt_rotate_z(&angle, &inter, &inu, e);
	inter_z = -sinf(-scene->angle.x * M_PI / 180) * inter.y + cosf(-scene->angle.x * M_PI / 180) * inter.z;
	inter_z = sinf(-scene->angle.y * M_PI / 180) * inter.x + cosf(-scene->angle.y * M_PI / 180) * inter_z;
	inter_z = inter_z + scene->pos.z;
//	printf("%f %f %f\n", inter_z, inter.z, scene->pos.z);
	if (inter_z < scene->pos.z + scene->min || inter_z > scene->pos.z + scene->max)
	{
		change = min_i;
		min_i = max_i;
		max_i = change;
		change = 1;
		inter.z = min_i * e->vect.z - scene->pos.z + e->cam.z;
		inter.y = min_i * e->vect.y - scene->pos.y + e->cam.y;
		inter.x = min_i * e->vect.x - scene->pos.x + e->cam.x;
		rt_rotate_x(&angle, &inter, &inu, e);
		rt_rotate_y(&angle, &inter, &inu, e);
		rt_rotate_z(&angle, &inter, &inu, e);
		inter_z = -sinf(-scene->angle.x * M_PI / 180) * inter.y + cosf(-scene->angle.x * M_PI / 180) * inter.z;
		inter_z = sinf(-scene->angle.y * M_PI / 180) * inter.x + cosf(-scene->angle.y * M_PI / 180) * inter_z;
		inter_z = inter_z + scene->pos.z;
		if (inter_z < scene->pos.z + scene->min || inter_z > scene->pos.z + scene->max)
			return (0);
	}
	if (((e->ray.inter == -1) || e->ray.inter > inter2) && inter2 > 0.01)
	{
		e->angle_ob.x = scene->angle.x;
		e->angle_ob.y = scene->angle.y;
		e->angle_ob.z = scene->angle.z;
		e->heart_sphere[0] = scene->pos.x;
		e->heart_sphere[1] = scene->pos.y;
		e->heart_sphere[2] = scene->pos.z;
		e->heart_plan[3] = pow(tanf(scene->radius * M_PI / 180), 2);
		e->ray.inter = min_i;
		e->object = 7;
		e->heart_plan[2] = (inter_z < scene->pos.z) ? -change : change;
		e->color.red = scene->rgb[0];
		e->color.green = scene->rgb[1];
		e->color.blue = scene->rgb[2];
	}
	return (0);
}

