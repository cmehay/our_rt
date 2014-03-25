/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_cone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmehay <cmehay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/24 16:29:11 by cmehay            #+#    #+#             */
/*   Updated: 2014/03/25 19:27:04 by dcouly           ###   ########.fr       */
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
	i->z = e->inter.z - e->heart_sphere[2];
	s->x = e->shadowray.x;
	s->y = e->shadowray.y;
	s->z = e->shadowray.z;
}

void		lightdcone(t_env *e)
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
	i.z = i.z * -1 * e->heart_plan[3];
	len = sqrt(i.x * i.x + i.y * i.y + i.z * i.z);
	e->normal.x = i.x / len;
	e->normal.y = i.y / len;
	e->normal.z = i.z / len;
	scal = (e->normal.x * s.x + e->normal.y * s.y
			+ e->normal.z * s.z) / (e->ray.len / 60);
	if (scal > 0.2)
		e->light_bis = fmax(pow(scal * (e->ray.len / 60), 60), e->light_bis);
	scal = (scal > 1) ? 1 : scal;
	scal = (scal < 0.05) ? 0.05 : scal;
	e->light *= scal;
}

static void	set_pos_a_v_i(t_env *e, t_pos *a, t_pos *v, t_pos *i)
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

int			size_light_on_dcone(t_env *e, t_data *scene)
{
	t_pos	v;
	t_pos	i;
	t_pos	p;
	t_pos	a;
	t_pos	z;

	set_pos_a_v_i(e, &a, &v, &i);
	set_pos_p(scene, &p);
	rt_rotate_x(&a, &v, &i, e);
	rt_rotate_x(&a, &z, &p, e);
	rt_rotate_y(&a, &v, &i, e);
	rt_rotate_y(&a, &z, &p, e);
	rt_rotate_z(&a, &v, &i, e);
	rt_rotate_z(&a, &z, &p, e);
	rt_rotate(scene, &v, &i, e);
	rt_rotate(scene, &z, &p, e);
	e->a = pow((v.x), 2) + pow((v.y), 2)
		- pow((v.z), 2) * pow(tanf(scene->radius * M_PI / 180), 2);
	e->b = 2 * ((v.x) * (i.x - p.x) + v.y * (i.y - p.y)
			- (v.z) * (i.z - p.z) * pow(tanf(scene->radius * M_PI / 180), 2));
	e->c = pow((i.x - p.x), 2)
		+ pow((i.y - p.y), 2)
		- pow((i.z - p.z), 2) * pow(tanf(scene->radius * M_PI / 180), 2);
	e->ray.delta_light = pow(e->b, 2) - (4 * e->a * e->c);
	return (get_light_to_demi_c(e, scene));
}
