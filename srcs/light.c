/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmehay <cmehay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/27 21:15:52 by sde-segu          #+#    #+#             */
/*   Updated: 2014/03/23 20:55:26 by cmehay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <stdio.h>

int		check_light(t_env *e, t_data **scene)
{
	t_data	*tmp;
	int		two_light;
	float	mem;

	mem = 0;
	e->light = 1;
	mem = 0;
	two_light = 0;
	tmp = *scene;
	e->inter.x = e->cam.x + (e->vect.x * e->ray.inter);
	e->inter.y = e->cam.y + (e->vect.y * e->ray.inter);
	e->inter.z = e->cam.z + (e->vect.z * e->ray.inter);
	e->lenght = 1000;
	while (tmp)
	{
		if (tmp && tmp->obj == LIGHT)
		{
			size_raylight(e, tmp);
			if (id_object_for_light(e, scene) == 0)
				mem = e->light_bis;
			two_light++;
		}
		tmp = tmp->next;
	}
	while (--two_light)
		e->light = sqrt(e->light);
	e->color.red *= e->light;
	e->color.green *= e->light;
	e->color.blue *= e->light;
	if (mem > 0)
	{
		e->color.red += 255 * mem;
		e->color.blue += 255 * mem;
		e->color.green += 255 * mem;
	}
	e->light_bis = 0;
	if (e->color.red > 255)
		e->color.red = 255;
	if (e->color.blue > 255)
		e->color.blue = 255;
	if (e->color.green > 255)
		e->color.green = 255;
	return (0);
}

void	size_raylight(t_env *e, t_data *scene)
{
	float	len;
	float	x;
	float	y;
	float	z;

	x = scene->pos.x - e->inter.x;
	y = scene->pos.y - e->inter.y;
	z = scene->pos.z - e->inter.z;
	len = sqrt(x * x + y * y + z * z);
	e->ray.len = len;
	e->shadowray.x = x / len;
	e->shadowray.y = y / len;
	e->shadowray.z = z / len;
}

int		id_object_for_light(t_env *e, t_data **scene)
{
	t_data	*tmp;
	int		ombre;

	ombre = 0;
	tmp = *scene;
	e->ray.inter_light = -1;
	if (e->object == 1)
		lightsphere(e);
	if (e->object == 2)
		lightplan(e);
	if (e->object == 3)
		lightcylinder(e);
	if (e->object == 4)
		lightcylinder(e);
	while (tmp)
	{
		if (tmp && tmp->obj == SPHERE)
			ombre += size_light_on_sphere(e, tmp);
		if (tmp && tmp->obj == PLAN)
			ombre += size_light_on_plan(e, tmp);
		if (tmp && tmp->obj == CYLINDER)
			ombre += size_light_on_cyl(e, tmp);
		if (tmp && tmp->obj == CONE)
			ombre += size_light_on_cone(e, tmp);
		tmp = tmp->next;
	}
	return (ombre);
}
