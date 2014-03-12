/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-segu <sde-segu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/27 21:15:52 by sde-segu          #+#    #+#             */
/*   Updated: 2014/02/27 21:15:52 by sde-segu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		check_light(t_env *e, t_data **scene)
{
	t_data	*tmp;

	tmp = *scene;
	e->interx = e->cam_x + (e->vect_x * e->inter);
	e->intery = e->cam_y + (e->vect_y * e->inter);
	e->interz = e->cam_z + (e->vect_z * e->inter);
	while (tmp)
	{
		tmp = tmp->next;
		if (tmp && !ft_strcmp("light", tmp->what))
		{
			size_raylight(e, tmp);
			id_object_for_light(e, scene);
		}
	}
	return (0);
}

void	size_raylight(t_env *e, t_data *scene)
{
	float	len;
	float	x;
	float	y;
	float	z;

	x = scene->x - e->interx;
	y = scene->y - e->intery;
	z = scene->z - e->interz;
	len = sqrt(x * x + y * y + z * z);
	e->len = len;
	e->shadowray_x = x / len;
	e->shadowray_y = y / len;
	e->shadowray_z = z / len;
}

void	id_object_for_light(t_env *e, t_data **scene)
{
	t_data	*tmp;

	tmp = *scene;
	e->inter_light = -1;
	if (e->object == 1)
		lightsphere(e);
	if (e->object == 2)
		lightplan(e);
	if (e->object == 3)
		lightcylinder(e);
	while (tmp)
	{
		tmp = tmp->next;
		if (tmp && !ft_strcmp("sphere", tmp->what))
			size_light_on_sphere(e, tmp);
		if (tmp && !ft_strcmp("plan", tmp->what))
			size_light_on_plan(e, tmp);
		if (tmp && !ft_strcmp("cylinder", tmp->what))
			size_light_on_cyl(e, tmp);
		if (tmp && !ft_strcmp("cone", tmp->what))
			size_light_on_cone(e, tmp);
	}
}
