/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dcylindre.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcouly <dcouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 16:44:12 by dcouly            #+#    #+#             */
/*   Updated: 2014/03/26 18:07:03 by dcouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static float	rt_cal_rot(t_data *scene, t_env *e, float min_i)
{
	t_pos	inter;
	t_pos	angle;
	t_pos	inu;

	angle.x = e->angle[0];
	angle.y = -e->angle[1];
	angle.z = e->angle[2];
	inter.z = min_i * e->vect.z - scene->pos.z + e->cam.z;
	inter.y = min_i * e->vect.y - scene->pos.y + e->cam.y;
	inter.x = min_i * e->vect.x - scene->pos.x + e->cam.x;
	rt_rotate_x(&angle, &inter, &inu, e);
	rt_rotate_y(&angle, &inter, &inu, e);
	rt_rotate_z(&angle, &inter, &inu, e);
	inter.z = -sinf(-scene->angle.x * M_PI / 180) * inter.y
		+ cosf(-scene->angle.x * M_PI / 180) * inter.z;
	inter.z = sinf(-scene->angle.y * M_PI / 180) * inter.x
		+ cosf(-scene->angle.y * M_PI / 180) * inter.z;
	return (inter.z);
}

static void		rt_assign(t_env *e, t_data *scene, float min_i)
{
	e->angle_ob.x = scene->angle.x;
	e->angle_ob.y = scene->angle.y;
	e->angle_ob.z = scene->angle.z;
	e->ray.inter = min_i;
	e->object = 6;
	e->heart_sphere[0] = scene->pos.x;
	e->heart_sphere[1] = scene->pos.y;
	e->heart_sphere[2] = scene->pos.z;
	e->color.red = scene->rgb[0];
	e->color.green = scene->rgb[1];
	e->color.blue = scene->rgb[2];
}

static float	rt_cal_inter(float *inter1, float *inter2, t_env *e)
{
	float	min_i;

	*inter1 = (-e->b + sqrt(e->ray.delta)) / (2 * e->a);
	*inter2 = (-e->b - sqrt(e->ray.delta)) / (2 * e->a);
	min_i = fmin(*inter1, *inter2);
	return (min_i);
}

int				get_dcyl_to_print(t_env *e, t_data *scene)
{
	float	min_i;
	float	inter1;
	float	inter2;
	float	inter_z;
	float	change;

	min_i = rt_cal_inter(&inter1, &inter2, e);
	change = 0;
	inter_z = rt_cal_rot(scene, e, min_i) + scene->pos.z;
	if (inter_z < scene->pos.z + scene->min
			|| inter_z > scene->pos.z + scene->max)
	{
		min_i = fmax(inter1, inter2);
		change = 1;
		inter_z = rt_cal_rot(scene, e, min_i) + scene->pos.z;
		if (inter_z < scene->pos.z + scene->min
				|| inter_z > scene->pos.z + scene->max)
			return (0);
	}
	if (((e->ray.inter == -1) || e->ray.inter > min_i) && min_i > 0.01)
	{
		e->heart_plan[3] = (inter_z < scene->pos.z) ? -change : change;
		rt_assign(e, scene, min_i);
	}
	return (0);
}
