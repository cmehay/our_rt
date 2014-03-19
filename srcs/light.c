/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmehay <cmehay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/27 21:15:52 by sde-segu          #+#    #+#             */
/*   Updated: 2014/03/19 19:47:17 by dcouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <stdio.h>

int		check_light(t_env *e, t_data **scene)
{
	t_data	*tmp;
	int		two_light;

	e->light = 1;
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
			id_object_for_light(e, scene);
			two_light++;
		}
		tmp = tmp->next;
	}
	while (--two_light)
		e->light = sqrt(e->light);
	e->color.red *= e->light;
	e->color.green *= e->light;
	e->color.blue *= e->light;
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

#include <stdio.h>

void	id_object_for_light(t_env *e, t_data **scene)
{
	t_data	*tmp;

	tmp = *scene;
	printf("1 %f %f %f\n", e->inter.x, e->inter.y, e->inter.z);
	e->ray.inter_light = -1;
	if (e->object == 1)
		lightsphere(e);
	if (e->object == 2)
		lightplan(e);
	if (e->object == 3)
		lightcylinder(e, *scene);
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
	printf("2 %f %f %f\n", e->inter.x, e->inter.y, e->inter.z);
}
