/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dsphere.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcouly <dcouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 19:02:46 by dcouly            #+#    #+#             */
/*   Updated: 2014/03/26 19:15:16 by dcouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static float	rt_cal_rot(t_data *scene, t_env *e, float min_i)
{
	t_pos	inter;
	t_pos	angle;
	t_pos	inu;
	float	mem;

	angle.x = e->angle[0];
	angle.y = -e->angle[1];
	angle.z = e->angle[2];
	inter.z = min_i * e->vect.z - scene->pos.z + e->cam.z;
	inter.y = min_i * e->vect.y - scene->pos.y + e->cam.y;
	inter.x = min_i * e->vect.x - scene->pos.x + e->cam.x;
	rt_rotate_x(&angle, &inter, &inu, e);
	rt_rotate_y(&angle, &inter, &inu, e);
	rt_rotate_z(&angle, &inter, &inu, e);
	mem = -sinf(scene->angle.x * M_PI / 180) * inter.y
		+ cosf(scene->angle.x * M_PI / 180) * inter.z;
	mem = sinf(scene->angle.y * M_PI / 180) * inter.x
		+ cosf(scene->angle.y * M_PI / 180) * mem;
	mem = mem + scene->pos.z;
	return (mem);
}

static void		rt_assign(t_env *e, t_data *scene, float min_i, float change)
{
	e->ray.inter = min_i;
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

int   get_demi_to_print(t_env *e, t_data *scene)
{
	float  min_i;
	float  inter1;
	float  inter2;
	float  change;
	float  mem;

	inter1 = (-e->b + sqrt(e->ray.delta)) / (2 * e->a);
	inter2 = (-e->b - sqrt(e->ray.delta)) / (2 * e->a);
	min_i = fmin(inter1, inter2);
	change = 0;
	mem = rt_cal_rot(scene, e, min_i);
	if (mem > scene->pos.z)
	{
		min_i = fmax(inter1, inter2);
		change = 1;
		mem = rt_cal_rot(scene, e, min_i);
		if (mem > scene->pos.z)
			return (0);
	}
	if (((e->ray.inter == -1) || e->ray.inter > min_i) && min_i > 0.01)
		rt_assign(e, scene, min_i, change);
	return (0);
}
