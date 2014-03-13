/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_plan.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmehay <cmehay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/01 02:13:06 by sde-segu          #+#    #+#             */
/*   Updated: 2014/03/13 16:08:54 by cmehay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		rt_plan(t_env *e, t_data *scene)
{
	float	inter;
	float	x;
	float	y;
	float	z;

	x = e->cam.x;
	y = e->cam.y;
	z = e->cam.z;
	inter = -((scene->pos.x * x + scene->pos.y * y + scene->pos.z * z
		+ scene->radius) / (scene->pos.x * e->vect.x + scene->pos.y * e->vect.y
		+ scene->pos.z * e->vect.z));
	if (((e->ray.inter == -1) || (inter < e->ray.inter)) && inter > 0.01)
	{
		e->ray.inter = inter;
		e->color.red = scene->rgb[0];
		e->color.green = scene->rgb[1];
		e->color.blue = scene->rgb[2];
		e->object = 2;
		e->heart_plan[0] = scene->pos.x;
		e->heart_plan[1] = scene->pos.y;
		e->heart_plan[2] = scene->pos.z;
		e->heart_plan[3] = scene->radius;
	}
	return (0);
}

int		lightplan(t_env *e)
{
	float	scal;

	scal = (e->heart_plan[0] * e->shadowray.x
	+ e->heart_plan[1] * e->shadowray.y
	+ e->heart_plan[2] * e->shadowray.z);
	scal = (scal < 0.2) ? 0.2 : scal;
	e->color.red *= scal;
	e->color.green *= scal;
	e->color.blue *= scal;
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
	if (inter > 4 && (inter < e->screen.length))
	{
		if (e->color.red > 20)
			e->color.red /= 2;
		if (e->color.red > 20)
			e->color.red /= 2;
		if (e->color.red > 20)
			e->color.red /= 2;
	}
}
