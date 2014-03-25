/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_plan.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmehay <cmehay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/01 02:13:06 by sde-segu          #+#    #+#             */
/*   Updated: 2014/03/25 15:13:03 by cmehay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <stdio.h>

static void	rt_plan_compute(t_env *e, t_data *scene, float inter)
{
	e->ray.inter = inter;
	e->color.red = scene->rgb[0];
	e->color.green = scene->rgb[1];
	e->color.blue = scene->rgb[2];
	e->angle_ob.x = scene->angle.x;
	e->angle_ob.y = scene->angle.y;
	e->angle_ob.z = scene->angle.z;
	e->object = 2;
	e->heart_plan[0] = scene->pos.x;
	if (scene->radius < 0)
		e->heart_plan[0] *= -1;
	e->heart_plan[1] = scene->pos.y;
	if (scene->radius < 0)
		e->heart_plan[1] *= -1;
	e->heart_plan[2] = scene->pos.z;
	if (scene->radius < 0)
		e->heart_plan[2] *= -1;
	e->heart_plan[3] = scene->radius;
}

int		rt_plan(t_env *e, t_data *scene)
{
	float	inter;
	t_pos	o;
	t_pos	v;

	o.x = e->cam.x + scene->pos.x * scene->radius;
	o.y = e->cam.y + scene->pos.y * scene->radius;
	o.z = e->cam.z + scene->pos.z * scene->radius;
	v.x = e->vect.x;
	v.y = e->vect.y;
	v.z = e->vect.z;
	rt_rotate(scene, &v, &o, e);
	o.x = o.x - scene->pos.x * scene->radius;
	o.y = o.y - scene->pos.y * scene->radius;
	o.z = o.z - scene->pos.z * scene->radius;
	inter = -((scene->pos.x * o.x + scene->pos.y * o.y + scene->pos.z * o.z
		+ scene->radius) / (scene->pos.x * v.x + scene->pos.y * v.y
		+ scene->pos.z * v.z));
	if (((e->ray.inter == -1) || (inter < e->ray.inter)) && inter > 0.01)
		rt_plan_compute(e, scene, inter);
	return (0);
}



