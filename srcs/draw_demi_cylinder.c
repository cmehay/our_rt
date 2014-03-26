/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_demi_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmehay <cmehay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/25 15:11:27 by dcouly            #+#    #+#             */
/*   Updated: 2014/03/26 22:10:31 by cmehay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_pos	rt_init(t_pos *a, t_data *scene, t_pos *v, t_env *e)
{
	t_pos	o;

	a->x = e->angle[0];
	a->y = -e->angle[1];
	a->z = e->angle[2];
	o.x = e->cam.x - scene->pos.x;
	o.z = e->cam.z - scene->pos.z;
	o.y = e->cam.y - scene->pos.y;
	v->x = e->vect.x;
	v->z = e->vect.z;
	v->y = e->vect.y;
	return (o);
}

void			rt_dcylinder(t_env *e, t_data *scene)
{
	t_pos	v;
	t_pos	o;
	t_pos	a;

	o = rt_init(&a, scene, &v, e);
	rt_rotate_x(&a, &v, &o, e);
	rt_rotate_y(&a, &v, &o, e);
	rt_rotate_z(&a, &v, &o, e);
	rt_rotate(scene, &v, &o, e);
	o.x = scene->pos.x + o.x;
	o.y = scene->pos.y + o.y;
	o.z = scene->pos.z + o.z;
	e->a = pow((v.x), 2) + pow((v.y), 2);
	e->b = 2 * ((v.x) * (o.x - scene->pos.x)
		+ v.y * (o.y - scene->pos.y));
	e->c = pow((o.x - scene->pos.x), 2)
		+ pow((o.y - scene->pos.y), 2) - pow(scene->radius, 2);
	e->ray.delta = pow(e->b, 2) - (4 * e->a * e->c);
	if (e->ray.delta >= 0)
		get_dcyl_to_print(e, scene);
}

static void		rt_init_bis(t_pos *a, t_pos *s, t_pos *i, t_env *e)
{
	a->x = e->angle[0];
	a->y = -e->angle[1];
	a->z = e->angle[2];
	s->x = e->shadowray.x;
	s->y = e->shadowray.y;
	s->z = e->shadowray.z;
	rt_rotate_x(a, i, s, e);
	rt_rotate_y(a, i, s, e);
	rt_rotate_z(a, i, s, e);
}

void			lightdcylinder(t_env *e, t_data light)
{
	float	len;
	t_pos	i;
	t_pos	s;
	float	scal;
	t_pos	a;

	i.x = e->inter.x - e->heart_sphere[0];
	i.y = e->inter.y - e->heart_sphere[1];
	i.z = e->inter.z - e->heart_sphere[2];
	rt_init_bis(&a, &s, &i, e);
	rt_rotate2(&i, &s, e);
	i.z = 0;
	len = sqrt(i.x * i.x + i.y * i.y + i.z * i.z);
	e->normal.x = i.x / len;
	e->normal.y = i.y / len;
	e->normal.z = i.z / len;
	scal = (e->normal.x * s.x + e->normal.y * s.y
		+ e->normal.z * s.z) / (e->ray.len / light.radius);
	if (scal > 0.2 && light.radius)
		e->light_bis = fmax(pow(scal * (e->ray.len / light.radius), 60),
				e->light_bis);
	scal = (scal > 1) ? 1 : scal;
	scal = (scal < 0.05) ? 0.05 : scal;
	e->light *= scal;
}

int				size_light_on_dcyl(t_env *e, t_data *scene, t_data light)
{
	t_pos	s;
	t_pos	i;
	t_pos	p;
	t_pos	a;
	t_pos	z;

	i.x = e->inter.x;
	i.y = e->inter.y;
	i.z = e->inter.z;
	p.x = scene->pos.x;
	p.y = scene->pos.y;
	p.z = scene->pos.z;
	rt_init_bis(&a, &s, &i, e);
	rt_rotate_x(&a, &z, &p, e);
	rt_rotate_y(&a, &z, &p, e);
	rt_rotate_z(&a, &z, &p, e);
	rt_rotate(scene, &s, &i, e);
	rt_rotate(scene, &z, &p, e);
	e->a = pow((s.x), 2) + pow((s.y), 2);
	e->b = 2 * ((s.x) * (i.x - p.x)
		+ s.y * (i.y - p.y));
	e->c = (pow((i.x - p.x), 2)
		+ pow((i.y - p.y), 2) - pow(scene->radius, 2));
	e->ray.delta_light = pow(e->b, 2) - 4 * e->a * e->c;
	return (get_light_to_demi_c(e, scene, light));
}
