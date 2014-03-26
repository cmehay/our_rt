/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_demi_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmehay <cmehay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/25 07:09:25 by sde-segu          #+#    #+#             */
/*   Updated: 2014/03/26 19:30:49 by dcouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	rt_init(t_pos *a, t_pos *o, t_env *e, t_data *scene)
{
	a->x = e->angle[0];
	a->y = -e->angle[1];
	a->z = e->angle[2];
	o->x = e->cam.x - scene->pos.x;
	o->z = e->cam.z - scene->pos.z;
	o->y = e->cam.y - scene->pos.y;
}

static void	rt_init2(t_pos *v, t_pos *x, t_env *e, t_data *scene)
{
	v->x = e->vect.x;
	v->z = e->vect.z;
	v->y = e->vect.y;
	x->x = scene->angle.x;
	x->y = scene->angle.y;
	x->z = scene->angle.z;
}

int		rt_demi_sphere(t_env *e, t_data *scene)
{
	t_pos	v;
	t_pos	o;
	t_pos	a;
	t_pos	x;

	rt_init(&a, &o, e, scene);
	rt_init2(&v, &x, e, scene);
	rt_rotate_x(&a, &v, &o, e);
	rt_rotate_y(&a, &v, &o, e);
	rt_rotate_z(&a, &v, &o, e);
	rt_rotate(scene, &v, &o, e);
	o.x = scene->pos.x + o.x;
	o.y = scene->pos.y + o.y;
	o.z = scene->pos.z + o.z;
	e->a = pow((v.x), 2) + pow((v.y), 2) + pow((v.z), 2);
	e->b = 2 * ((v.x) * (o.x - scene->pos.x)
		+ v.y * (o.y - scene->pos.y)
		+ (v.z) * (o.z - scene->pos.z));
	e->c = (pow(o.x - scene->pos.x, 2)
		+ pow((o.y - scene->pos.y), 2) + pow((o.z - scene->pos.z), 2)
			- pow(scene->radius, 2));
	e->ray.delta = pow(e->b, 2) - 4 * e->a * e->c;
	if (e->ray.delta >= 0)
		get_demi_to_print(e, scene);
	return (0);
}

int		size_light_on_demi_sphere(t_env *e, t_data *scene, t_data light)
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
	return (get_light_to_print_demi(e, scene, light));
}
