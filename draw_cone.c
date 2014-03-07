/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_cone.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-segu <sde-segu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/02 03:09:31 by sde-segu          #+#    #+#             */
/*   Updated: 2014/03/02 03:09:32 by sde-segu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	rt_cone(t_env *e, t_data *scene)
{
	e->a = pow((e->vect_x), 2) + pow((e->vect_y), 2)
		- pow((e->vect_z), 2);
	e->b = 2 * ((e->vect_x) * (e->cam_x - scene->x)
		+ e->vect_y * (e->cam_y - scene->y)
		+ (e->vect_z) * (e->cam_z - scene->z));
	e->c = pow((e->cam_x - scene->x), 2)
		+ pow((e->cam_y - scene->y), 2)
		- pow((e->cam_z - scene->z), 2);
	e->delta = pow(e->b, 2) - (4 * e->a * e->c);
	get_cone_to_print(e, scene);
}

int		get_cone_to_print(t_env *e, t_data *scene)
{
	float	inter1;
	float	inter2;

	inter1 = (-e->b + sqrt(e->delta)) / (2 * e->a);
	inter2 = (-e->b - sqrt(e->delta)) / (2 * e->a);
	inter2 = (fmin(inter1, inter2) > 0.01) ? fmin(inter1, inter2)
		: fmax(inter1, inter2);
	if (((e->inter == -1) || e->inter > inter2) && inter2 > 0.01)
	{
		e->inter = inter1;
		e->object = 3;
		e->red = scene->rgb[0];
		e->green = scene->rgb[1];
		e->blue = scene->rgb[2];
	}
	return (0);
}

void	size_light_on_cone(t_env *e, t_data *scene)
{
	e->a = pow((e->shadowray_x), 2) + pow((e->shadowray_y), 2)
		- pow((e->shadowray_z), 2);
	e->b = 2 * ((e->shadowray_x) * (e->interx - scene->x)
		+ e->shadowray_y * (e->intery - scene->y)
		+ (e->shadowray_z) * (e->interz - scene->z));
	e->c = pow((e->interx - scene->x), 2)
		+ pow((e->intery - scene->y), 2)
		- pow((e->interz - scene->z), 2);
	e->delta = pow(e->b, 2) - 4 * e->a * e->c;
	get_light_to_print(e);
}