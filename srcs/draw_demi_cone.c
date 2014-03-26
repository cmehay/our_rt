/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_demi_cone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmehay <cmehay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/02 03:09:31 by sde-segu          #+#    #+#             */
/*   Updated: 2014/03/26 19:48:01 by dcouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	set_pos_o(t_env *e, t_data *scene, t_pos *o)
{
	o->x = e->cam.x - scene->pos.x;
	o->z = e->cam.z - scene->pos.z;
	o->y = e->cam.y - scene->pos.y;
}

static void	set_pos_v(t_env *e, t_pos *v)
{
	v->x = e->vect.x;
	v->z = e->vect.z;
	v->y = e->vect.y;
}

static void set_pos_a(t_env *e, t_pos *a)
{
	a->x = e->angle[0];
	a->y = -e->angle[1];
	a->z = e->angle[2];
}

void		rt_dcone(t_env *e, t_data *scene)
{
	t_pos	v;
	t_pos	o;
	t_pos	a;

	set_pos_o(e, scene, &o);
	set_pos_v(e, &v);
	set_pos_a(e, &a);
	rt_rotate_x(&a, &v, &o, e);
	rt_rotate_y(&a, &v, &o, e);
	rt_rotate_z(&a, &v, &o, e);
	rt_rotate(scene, &v, &o, e);
	o.x = scene->pos.x + o.x;
	o.y = scene->pos.y + o.y;
	o.z = scene->pos.z + o.z;
	e->a = pow((v.x), 2) + pow((v.y), 2)
		- pow((v.z), 2) * pow(tanf(scene->radius * M_PI / 180), 2);
	e->b = 2 * ((v.x) * (o.x - scene->pos.x)
		+ v.y * (o.y - scene->pos.y) - (v.z) * (o.z - scene->pos.z)
		* pow(tanf(scene->radius * M_PI / 180), 2));
	e->c = pow((o.x - scene->pos.x), 2)
		+ pow((o.y - scene->pos.y), 2) - pow((o.z - scene->pos.z), 2)
		* pow(tanf(scene->radius * M_PI / 180), 2);
	e->ray.delta = pow(e->b, 2) - (4 * e->a * e->c);
	if (e->ray.delta > 0)
		get_dcone_to_print(e, scene);
}
