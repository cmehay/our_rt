/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_demi_cylinder.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmehay <cmehay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 17:21:10 by dcouly            #+#    #+#             */
/*   Updated: 2014/03/26 21:29:00 by cmehay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static float	rt_init(float min, t_env *e, t_data *scene)
{
	t_pos	inu;
	t_pos	angle;
	t_pos	inter;
	float	res;

	angle.x = e->angle[0];
	angle.y = -e->angle[1];
	angle.z = e->angle[2];
	inter.z = min * e->shadowray.z + e->inter.z - scene->pos.z;
	inter.y = min * e->shadowray.y + e->inter.y - scene->pos.y;
	inter.x = min * e->shadowray.x + e->inter.x - scene->pos.x;
	rt_rotate_x(&angle, &inter, &inu, e);
	rt_rotate_y(&angle, &inter, &inu, e);
	rt_rotate_z(&angle, &inter, &inu, e);
	res = -sinf(-scene->angle.x * M_PI / 180) * inter.y
		+ cosf(-scene->angle.x * M_PI / 180) * inter.z;
	res = sinf(-scene->angle.y * M_PI / 180) * inter.x
		+ cosf(-scene->angle.y * M_PI / 180) * res;
	res = res + scene->pos.z;
	return (res);
}

static int		rt_change_col(t_env *e, float min, t_data light)
{
	float	max;

	e->light_bis = 0;
	e->ray.inter_light = min;
	max = cbrt(cbrt(light.radius));
	if (e->color.red > 20)
		e->color.red /= max;
	if (e->color.green > 20)
		e->color.green /= max;
	if (e->color.blue > 20)
		e->color.blue /= max;
	return (1);
}

int				get_light_to_demi_c(t_env *e, t_data *scene, t_data light)
{
	float	inter1;
	float	inter2;
	float	min;
	float	mem;

	if (e->ray.delta_light >= 0)
	{
		inter2 = (-e->b + sqrt(e->ray.delta_light)) / (2 * e->a);
		inter1 = (-e->b - sqrt(e->ray.delta_light)) / (2 * e->a);
		min = fmin(inter2, inter1);
		mem = rt_init(min, e, scene);
		if (mem > scene->pos.z + scene->max || mem < scene->pos.z + scene->min)
		{
			min = fmax(inter2, inter1);
			mem = rt_init(min, e, scene);
			if (mem > scene->pos.z + scene->max
					|| mem < scene->pos.z + scene->min)
				return (0);
		}
		if (min > 0.1 && (min < e->lenght))
			return (rt_change_col(e, min, light));
	}
	return (0);
}
