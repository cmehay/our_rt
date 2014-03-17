/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmehay <cmehay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/27 21:15:52 by sde-segu          #+#    #+#             */
/*   Updated: 2014/03/17 21:20:50 by dcouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		check_light(t_env *e, t_data **scene)
{
	t_data	*tmp;

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
			id_object_for_light(e, scene);
		}
		tmp = tmp->next;
	}
	return (0);
}
#include <stdio.h>

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

void	id_object_for_light(t_env *e, t_data **scene)
{
	t_data	*tmp;

	tmp = *scene;
	e->ray.inter_light = -1;
	if (e->object == 1)
		lightsphere(e);
	if (e->object == 2)
		lightplan(e);
	if (e->object == 3)
		lightcylinder(e);
	if (e->object == 4)
		lightcone(e);
	while (tmp)
	{
		if (tmp && tmp->obj == SPHERE)
			size_light_on_sphere(e, tmp);
		if (tmp && tmp->obj == PLAN)
			size_light_on_plan(e, tmp);
		if (tmp && tmp->obj == CYLINDER)
			size_light_on_cyl(e, tmp);
		if (tmp && tmp->obj == CONE)
			size_light_on_cone(e, tmp);
		tmp = tmp->next;
	}
}
