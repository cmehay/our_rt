/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmehay <cmehay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/24 17:00:41 by cmehay            #+#    #+#             */
/*   Updated: 2014/03/26 21:28:33 by cmehay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	set_pos_a_i_s(t_env *e, t_pos *a, t_pos *i, t_pos *s)
{
	a->x = e->angle[0];
	a->y = -e->angle[1];
	a->z = e->angle[2];
	i->x = e->inter.x - e->heart_sphere[0];
	i->y = e->inter.y - e->heart_sphere[1];
	i->z = (e->inter.z - e->heart_sphere[2]);
	s->x = e->shadowray.x;
	s->y = e->shadowray.y;
	s->z = e->shadowray.z;
}

void		lightcylinder(t_env *e, t_data light)
{
	float	len;
	t_pos	i;
	t_pos	s;
	float	scal;
	t_pos	a;

	set_pos_a_i_s(e, &a, &i, &s);
	rt_rotate_x(&a, &i, &s, e);
	rt_rotate_y(&a, &i, &s, e);
	rt_rotate_z(&a, &i, &s, e);
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

static void	set_pos_a_s_i(t_env *e, t_pos *a, t_pos *v, t_pos *i)
{
	a->x = e->angle[0];
	a->y = -e->angle[1];
	a->z = e->angle[2];
	v->x = e->shadowray.x;
	v->y = e->shadowray.y;
	v->z = e->shadowray.z;
	i->x = e->inter.x;
	i->y = e->inter.y;
	i->z = e->inter.z;
}

static void	set_pos_p(t_data *scene, t_pos *p)
{
	p->x = scene->pos.x;
	p->y = scene->pos.y;
	p->z = scene->pos.z;
}

int			size_light_on_cyl(t_env *e, t_data *scene, t_data light)
{
	t_pos	s;
	t_pos	i;
	t_pos	p;
	t_pos	a;
	t_pos	z;

	set_pos_a_s_i(e, &a, &s, &i);
	set_pos_p(scene, &p);
	rt_rotate_x(&a, &s, &i, e);
	rt_rotate_x(&a, &z, &p, e);
	rt_rotate_y(&a, &s, &i, e);
	rt_rotate_y(&a, &z, &p, e);
	rt_rotate_z(&a, &s, &i, e);
	rt_rotate_z(&a, &z, &p, e);
	rt_rotate(scene, &s, &i, e);
	rt_rotate(scene, &z, &p, e);
	e->a = pow((s.x), 2) + pow((s.y), 2);
	e->b = 2 * ((s.x) * (i.x - p.x)
		+ s.y * (i.y - p.y));
	e->c = (pow((i.x - p.x), 2)
		+ pow((i.y - p.y), 2) - pow(scene->radius, 2));
	e->ray.delta_light = pow(e->b, 2) - 4 * e->a * e->c;
	return (get_light_to_print(e, light));
}
