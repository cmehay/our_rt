/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmehay <cmehay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/24 19:09:21 by cmehay            #+#    #+#             */
/*   Updated: 2014/03/26 21:22:35 by cmehay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		lightsphere(t_env *e, t_data light)
{
	float	len;
	t_pos	nor;
	float	scal;

	nor.x = e->inter.x - e->heart_sphere[0];
	nor.y = e->inter.y - e->heart_sphere[1];
	nor.z = e->inter.z - e->heart_sphere[2];
	len = sqrt(nor.x * nor.x + nor.y * nor.y + nor.z * nor.z);
	e->normal.x = nor.x / len;
	e->normal.y = nor.y / len;
	e->normal.z = nor.z / len;
	scal = (e->normal.x * e->shadowray.x + e->normal.y * e->shadowray.y
		+ e->normal.z * e->shadowray.z);
	if (scal > 0.2 && light.radius)
		e->light_bis = fmax(pow(scal, 60), e->light_bis);
	scal = scal / (e->ray.len) * light.radius;
	scal = (scal < 0.05) ? 0.05 : scal;
	scal = (scal > 1) ? 1 : scal;
	e->light *= scal;
}

int			size_light_on_sphere(t_env *e, t_data *scene, t_data light)
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
	return (get_light_to_print(e, light));
}

static int	set_light_color(t_env *e, float min, t_data light)
{
	float	div;

	div = cbrt(cbrt(light.radius));
	e->light_bis = 0;
	e->ray.inter_light = min;
	if (e->color.red > 20)
		e->color.red /= div;
	if (e->color.green > 20)
		e->color.green /= div;
	if (e->color.blue > 20)
		e->color.blue /= div;
	return (1);
}

int			get_light_to_print(t_env *e, t_data light)
{
	float	inter;
	float	inter2;
	float	min;
	float	max;

	inter = 0;
	inter2 = 0;
	if (e->ray.delta_light >= 0)
	{
		inter2 = (-e->b + sqrt(e->ray.delta_light)) / (2 * e->a);
		inter = (-e->b - sqrt(e->ray.delta_light)) / (2 * e->a);
		min = fmin(inter2, inter);
		max = fmax(inter2, inter);
		if (min > 0.1 && (max < e->lenght))
			return (set_light_color(e, min, light));
	}
	return (0);
}
