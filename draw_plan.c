/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_plan.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-segu <sde-segu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/01 02:13:06 by sde-segu          #+#    #+#             */
/*   Updated: 2014/03/01 02:13:07 by sde-segu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		rt_plan(t_env *e, t_data *scene)
{
	float	inter;
	float	x;
	float	y;
	float	z;

	x = e->cam_x;
	y = e->cam_y;
	z = e->cam_z;
	inter = -((scene->x * x + scene->y * y + scene->z * z + scene->radius)
	/ (scene->x * e->vect_x + scene->y * e->vect_y + scene->z * e->vect_z));
	if (((e->inter == -1) || (inter < e->inter)) && inter > 0.01)
	{
		e->inter = inter;
		e->red = scene->rgb[0];
		e->green = scene->rgb[1];
		e->blue = scene->rgb[2];
		e->object = 2;
		e->heart_plan[0] = scene->x;
		e->heart_plan[1] = scene->y;
		e->heart_plan[2] = scene->z;
		e->heart_plan[3] = scene->radius;
	}
	return (0);
}

int		lightplan(t_env *e)
{
	float	scal;

	scal = (e->heart_plan[0] * e->shadowray_x
	+ e->heart_plan[1] * e->shadowray_y
	+ e->heart_plan[2] * e->shadowray_z);
	scal = (scal < 0.2) ? 0.2 : scal;
	e->red *= scal;
	e->green *= scal;
	e->blue *= scal;
	return (0);
}

void	size_light_on_plan(t_env *e, t_data *scene)
{
	float	inter;
	float	x;
	float	y;
	float	z;

	x = e->interx;
	y = e->intery;
	z = e->interz;
	inter = -((scene->x * x + scene->y * y + scene->z * z + scene->radius)
		/ (scene->x * e->shadowray_x + scene->y * e->shadowray_y
			+ scene->z * e->shadowray_z));
	if (inter > 4 && (inter < e->lenght))
	{
		if (e->red > 20)
			e->red /= 2;
		if (e->red > 20)
			e->red /= 2;
		if (e->red > 20)
			e->red /= 2;
	}
}