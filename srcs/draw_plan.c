/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_plan.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmehay <cmehay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/01 02:13:06 by sde-segu          #+#    #+#             */
/*   Updated: 2014/03/20 22:40:41 by cmehay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <stdio.h>

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
	{
		e->ray.inter = inter;
		e->color.red = scene->rgb[0];
		e->color.green = scene->rgb[1];
		e->color.blue = scene->rgb[2];
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
	return (0);
}


int		lightplan(t_env *e)
{
	float	scal;
	float	len;
	float	x;
	float	y;
	float	z;

	len = sqrt(e->heart_plan[0] * e->heart_plan[0] + e->heart_plan[1]
	* e->heart_plan[1] + e->heart_plan[2] * e->heart_plan[2]);
	x = e->heart_plan[0] / len;
	y = e->heart_plan[1] / len;
	z = e->heart_plan[2] / len;
	scal = 40 / (e->ray.len);
	scal = (scal > 1) ? 1 : scal;
	scal = (scal < 0.001) ? 0.001 : scal;
	e->light *= scal;
	return (0);
}

void	size_light_on_plan(t_env *e, t_data *scene)
{
	float	inter;
	float	x;
	float	y;
	float	z;

	x = e->inter.x;
	y = e->inter.y;
	z = e->inter.z;
	inter = -((scene->pos.x * x + scene->pos.y * y + scene->pos.z * z
		+ scene->radius) / (scene->pos.x * e->shadowray.x
		+ scene->pos.y * e->shadowray.y + scene->pos.z * e->shadowray.z));
	if (inter > 20 && (inter < e->screen.length))
	{
		if (e->color.blue > 20)
			e->color.blue /= 2;
		if (e->color.green > 20)
			e->color.green /= 2;
		if (e->color.red > 20)
			e->color.red /= 2;
	}
}
