/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_demi_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmehay <cmehay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/25 07:09:25 by sde-segu          #+#    #+#             */
/*   Updated: 2014/03/25 15:36:29 by cmehay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		rt_demi_sphere(t_env *e, t_data *scene)
{
	t_pos	v;
	t_pos	o;
	t_pos	a;
	t_pos	x;

	a.x = e->angle[0];
	a.y = -e->angle[1];
	a.z = e->angle[2];
	o.x = e->cam.x - scene->pos.x;
	o.z = e->cam.z - scene->pos.z;
	o.y = e->cam.y - scene->pos.y;
	v.x = e->vect.x;
	v.z = e->vect.z;
	v.y = e->vect.y;
	x.x = scene->angle.x;
	x.y = scene->angle.y;
	x.z = scene->angle.z;
	rt_rotate_x(&a, &v, &o, e);
	rt_rotate_y(&a, &v, &o, e);
	rt_rotate_z(&a, &v, &o, e);
	rt_rotate(scene, &v, &o, e);
	o.x = scene->pos.x + o.x;
	o.y = scene->pos.y + o.y;
	o.z = scene->pos.z + o.z;
	e->a = pow((v.x), 2) + pow((v.y), 2) + pow((v.z), 2);
	e->b = 2 * ((v.x) * (o.x - scene->pos.x)
		+ v.y * (o.y - scene->pos.y)
		+ (v.z) * (o.z - scene->pos.z));
	e->c = (pow(o.x - scene->pos.x, 2)
		+ pow((o.y - scene->pos.y), 2) + pow((o.z - scene->pos.z), 2)
			- pow(scene->radius, 2));
	e->ray.delta = pow(e->b, 2) - 4 * e->a * e->c;
	if (e->ray.delta >= 0)
		get_demi_to_print(e, scene, v);
	return (0);
}

#include <stdio.h>

int		get_demi_to_print(t_env *e, t_data *scene, t_pos v)
{
	float	inter1;
	float	inter2;
	float	change;
	float	mem;
	t_pos	inter;
	t_pos	angle;
	t_pos	inu;

	angle.x = e->angle[0];
	angle.y = -e->angle[1];
	angle.z = e->angle[2];
	inter.x = v.x;
	inter1 = (-e->b + sqrt(e->ray.delta)) / (2 * e->a);
	inter2 = (-e->b - sqrt(e->ray.delta)) / (2 * e->a);
	inter2 = (fmin(inter1, inter2) > 0.01) ? fmin(inter1, inter2)
		: fmax(inter1, inter2);
	inter.z = inter2 * e->vect.z - scene->pos.z + e->cam.z;
	inter.y = inter2 * e->vect.y - scene->pos.y + e->cam.y;
	inter.x = inter2 * e->vect.x - scene->pos.x + e->cam.x;
	rt_rotate_x(&angle, &inter, &inu, e);
	rt_rotate_y(&angle, &inter, &inu, e);
	rt_rotate_z(&angle, &inter, &inu, e);
	mem = -sinf(scene->angle.x * M_PI / 180) * inter.y + cosf(scene->angle.x * M_PI / 180) * inter.z;
	mem = sinf(scene->angle.y * M_PI / 180) * inter.x + cosf(scene->angle.y * M_PI / 180) * mem;
	mem = mem + scene->pos.z;
	change = 0;
	if (((e->ray.inter == -1) || e->ray.inter > inter2) && inter2 > 0.01)
	{
		if (mem > scene->pos.z)
		{
			mem = inter1;
			inter1 = inter2;
			inter2 = mem;
			change = 1;
			inter.z = inter2 * e->vect.z - scene->pos.z + e->cam.z;
			inter.y = inter2 * e->vect.y - scene->pos.y + e->cam.y;
			inter.x = inter2 * e->vect.x - scene->pos.x + e->cam.x;
			rt_rotate_x(&angle, &inter, &inu, e);
			rt_rotate_y(&angle, &inter, &inu, e);
			rt_rotate_z(&angle, &inter, &inu, e);
			mem = -sinf(scene->angle.x * M_PI / 180) * inter.y + cosf(scene->angle.x * M_PI / 180) * inter.z;
			mem = sinf(scene->angle.y * M_PI / 180) * inter.x + cosf(scene->angle.y * M_PI / 180) * mem;
			mem = mem + scene->pos.z;
			if (mem > scene->pos.z)
				return (0);
		}
	}
	if (((e->ray.inter == -1) || e->ray.inter > inter2) && inter2 > 0.01)
	{
		e->ray.inter = inter2;
		e->object = 5;
		e->heart_sphere[0] = scene->pos.x;
		e->heart_sphere[1] = scene->pos.y;
		e->heart_sphere[2] = scene->pos.z;
		e->heart_plan[3] = change;
		e->angle_ob.x = scene->angle.x;
		e->angle_ob.y = scene->angle.y;
		e->angle_ob.z = scene->angle.z;
		e->color.red = scene->rgb[0];
		e->color.green = scene->rgb[1];
		e->color.blue = scene->rgb[2];
	}
	return (0);
}

int		get_light_to_print_demi(t_env *e, t_data *scene)
{
	float	inter1;
	t_pos	inter;
	float	inter2;
	float	min;
	float	max;
	float	mem = 0;
	t_pos	angle;
	t_pos	inu;

	angle.x = e->angle[0];
	angle.y = -e->angle[1];
	angle.z = e->angle[2];
	if (e->ray.delta_light >= 0)
	{
		inter2 = (-e->b + sqrt(e->ray.delta_light)) / (2 * e->a);
		inter1 = (-e->b - sqrt(e->ray.delta_light)) / (2 * e->a);
		min = fmin(inter2, inter1);
		max = fmax(inter2, inter1);
		inter.z = min * e->shadowray.z + e->inter.z - scene->pos.z;
		inter.y = min * e->shadowray.y + e->inter.y - scene->pos.y;
		inter.x = min * e->shadowray.x + e->inter.x - scene->pos.x;
		rt_rotate_x(&angle, &inter, &inu, e);
		rt_rotate_y(&angle, &inter, &inu, e);
		rt_rotate_z(&angle, &inter, &inu, e);
		mem = -sinf(scene->angle.x * M_PI / 180) * inter.y + cosf(scene->angle.x * M_PI / 180) * inter.z;
		mem = sinf(scene->angle.y * M_PI / 180) * inter.x + cosf(scene->angle.y * M_PI / 180) * mem;
		mem = mem + scene->pos.z;
		if (mem > scene->pos.z)
		{
			mem = max;
			max = min;
			min = mem;
			inter.z = min * e->shadowray.z + e->inter.z - scene->pos.z;
			inter.y = min * e->shadowray.y + e->inter.y - scene->pos.y;
			inter.x = min * e->shadowray.x + e->inter.x - scene->pos.x;
			rt_rotate_x(&angle, &inter, &inu, e);
			rt_rotate_y(&angle, &inter, &inu, e);
			rt_rotate_z(&angle, &inter, &inu, e);
			mem = -sinf(scene->angle.x * M_PI / 180) * inter.y + cosf(scene->angle.x * M_PI / 180) * inter.z;
			mem = sinf(scene->angle.y * M_PI / 180) * inter.x + cosf(scene->angle.y * M_PI / 180) * mem;
			mem = mem + scene->pos.z;
			if (mem > scene->pos.z)
				return (0);
		}
		if (min > 0.1 && (max < e->lenght))
		{
			e->light_bis = 0;
			e->ray.inter_light = min;
			if (e->color.red > 20)
				e->color.red /= 2;
			if (e->color.green > 20)
				e->color.green /= 2;
			if (e->color.blue > 20)
				e->color.blue /= 2;
			return (1);
		}
	}
	return (0);
}

void	lightdemisphere(t_env *e)
{
	float	len;
	t_pos	nor;
	float	scal;
	t_pos	a;
	t_pos	s;
	t_pos	u;

	s.x = e->shadowray.x;
	s.y = e->shadowray.y;
	s.z = e->shadowray.z;
	if (e->heart_plan[3] == 0)
	{
		nor.x = e->inter.x - e->heart_sphere[0];
		nor.y = e->inter.y - e->heart_sphere[1];
		nor.z = e->inter.z - e->heart_sphere[2];
	}
	else
	{
		nor.x = 0;
		nor.y = 0;
		nor.z = 1;
		a.x = e->angle[0];
		a.y = e->angle[1];
		a.z = e->angle[2];
		rt_rotate_x(&a, &nor, &u, e);
		rt_rotate_y(&a, &nor, &u, e);
		rt_rotate_z(&a, &nor, &u, e);
		a.x = e->angle_ob.x;
		a.y = e->angle_ob.y;
		a.z = e->angle_ob.z;
		rt_rotate_y(&a, &nor, &u, e);
		rt_rotate_x(&a, &nor, &u, e);
	}
	len = sqrt(nor.x * nor.x + nor.y * nor.y + nor.z * nor.z);
	e->normal.x = nor.x / len;
	e->normal.y = nor.y / len;
	e->normal.z = nor.z / len;
	scal = (e->normal.x * s.x + e->normal.y * s.y + e->normal.z * s.z);
	if (scal > 0.2)
		e->light_bis = fmax(pow(scal, 60), e->light_bis);
	scal = scal / (e->ray.len / 60);
	scal = (scal < 0.05) ? 0.05 : scal;
	scal = (scal > 1) ? 1 : scal;
	e->light *= scal;
}

int		size_light_on_demi_sphere(t_env *e, t_data *scene)
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
	return (get_light_to_print_demi(e, scene));
}
