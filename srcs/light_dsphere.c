/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_dsphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcouly <dcouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 19:18:19 by dcouly            #+#    #+#             */
/*   Updated: 2014/03/26 19:33:33 by dcouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static float	rt_init(float min, t_env *e, t_data *scene)
{
	t_pos	inu;
	t_pos	angle;
	t_pos	inter;
	float	mem;

	angle.x = e->angle[0];
	angle.y = -e->angle[1];
	angle.z = e->angle[2];
	inter.z = min * e->shadowray.z + e->inter.z - scene->pos.z;
	inter.y = min * e->shadowray.y + e->inter.y - scene->pos.y;
	inter.x = min * e->shadowray.x + e->inter.x - scene->pos.x;
	rt_rotate_x(&angle, &inter, &inu, e);
	rt_rotate_y(&angle, &inter, &inu, e);
	rt_rotate_z(&angle, &inter, &inu, e);
	mem = -sinf(scene->angle.x * M_PI / 180) * inter.y
		+ cosf(scene->angle.x * M_PI / 180) * inter.z;
	mem = sinf(scene->angle.y * M_PI / 180) * inter.x
		+ cosf(scene->angle.y * M_PI / 180) * mem;
	return (mem);
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

int	get_light_to_print_demi(t_env *e, t_data *scene, t_data light)
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
		mem = rt_init(min, e, scene) + scene->pos.z;
		if (mem > scene->pos.z)
		{
			min = fmax(inter2, inter1);
			mem = rt_init(min, e, scene) + scene->pos.z;
			if (mem > scene->pos.z)
				return (0);
		}
		if (min > 0.1 && (min < e->lenght))
			return (rt_change_col(e, min, light));
	}
	return (0);
}

static void	rt_init_light(t_env *e, t_pos *nor, t_pos *a)
{
	t_pos	u;

	if (e->heart_plan[3] == 0)
	{
		nor->x = e->inter.x - e->heart_sphere[0];
		nor->y = e->inter.y - e->heart_sphere[1];
		nor->z = e->inter.z - e->heart_sphere[2];
	}
	else
	{
		nor->x = 0;
		nor->y = 0;
		nor->z = 1;
		a->x = e->angle[0];
		a->y = e->angle[1];
		a->z = e->angle[2];
		rt_rotate_x(a, nor, &u, e);
		rt_rotate_y(a, nor, &u, e);
		rt_rotate_z(a, nor, &u, e);
		a->x = e->angle_ob.x;
		a->y = e->angle_ob.y;
		a->z = e->angle_ob.z;
		rt_rotate_y(a, nor, &u, e);
		rt_rotate_x(a, nor, &u, e);
	}
}

void	lightdemisphere(t_env *e, t_data light)
{
	float	len;
	t_pos	nor;
	float	scal;
	t_pos	a;
	t_pos	s;

	s.x = e->shadowray.x;
	s.y = e->shadowray.y;
	s.z = e->shadowray.z;
	rt_init_light(e, &nor, &a);
	len = sqrt(nor.x * nor.x + nor.y * nor.y + nor.z * nor.z);
	e->normal.x = nor.x / len;
	e->normal.y = nor.y / len;
	e->normal.z = nor.z / len;
	scal = (e->normal.x * s.x + e->normal.y * s.y + e->normal.z * s.z);
	if (scal > 0.2 && light.radius)
		e->light_bis = fmax(pow(scal, 60), e->light_bis);
	scal = scal / (e->ray.len) * light.radius;
	scal = (scal < 0.05) ? 0.05 : scal;
	scal = (scal > 1) ? 1 : scal;
	e->light *= scal;
}
