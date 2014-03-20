/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_cylinder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmehay <cmehay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/02 03:09:23 by sde-segu          #+#    #+#             */
/*   Updated: 2014/03/20 18:05:27 by dcouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	rt_cylinder(t_env *e, t_data *scene)
{
	t_pos	v;
	t_pos	o;

	o.x = e->cam.x - scene->pos.x;
	o.z = e->cam.z - scene->pos.z;
	o.y = e->cam.y - scene->pos.y;
	v.x = e->vect.x;
	v.z = e->vect.z;
	v.y = e->vect.y;
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
	get_cyl_to_print(e, scene);
}

int		get_cyl_to_print(t_env *e, t_data *scene)
{
	float	inter1;
	float	inter2;

	inter1 = (-e->b + sqrt(e->ray.delta)) / (2 * e->a);
	inter2 = (-e->b - sqrt(e->ray.delta)) / (2 * e->a);
	inter2 = (fmin(inter1, inter2) > 0.01) ? fmin(inter1, inter2)
		: fmax(inter1, inter2);
	if (((e->ray.inter == -1) || e->ray.inter > inter2) && inter2 > 0.01)
	{
		e->ray.inter = inter2;
		e->object = 3;
		e->heart_sphere[0] = scene->pos.x;
		e->heart_sphere[1] = scene->pos.y;
		e->heart_sphere[2] = scene->pos.z;
		e->color.red = scene->rgb[0];
		e->color.green = scene->rgb[1];
		e->color.blue = scene->rgb[2];
	}
	return (0);
}

void	lightcylinder(t_env *e, t_data *scene)
{
	float	len;
	t_pos	i;
	t_pos	h;
	t_pos	s;
	float	scal;

	i.x = e->inter.x - e->heart_sphere[0];
	i.y = e->inter.y - e->heart_sphere[1];
	i.z = e->inter.z - e->heart_sphere[2];
	h.x = e->heart_sphere[0];
	h.y = e->heart_sphere[1];
	h.z = e->heart_sphere[2];
	rt_rotate(scene, &i, &h, e);
	i.z = 0;
	len = sqrt(i.x * i.x + i.y * i.y + i.z * i.z);
	e->normal.x = i.x / len;
	e->normal.y = i.y / len;
	e->normal.z = i.z / len;
	s.x = e->shadowray.x;
	s.y = e->shadowray.y;
	s.z = e->shadowray.z;
	rt_rotate(scene, &i, &s, e);
	scal = (e->normal.x * s.x + e->normal.y * s.y
		 + e->normal.z * s.z) / (e->ray.len / 40);
	scal = (scal > 1) ? 1 : scal;
	scal = (scal < 0.001) ? 0.001 : scal;
	e->light *= scal;
}

void	size_light_on_cyl(t_env *e, t_data *scene)
{
	t_pos	s;
	t_pos	i;
	t_pos	p;
	t_pos	z;

	i.x = e->inter.x;
	i.y = e->inter.y;
	i.z = e->inter.z;
	s.x = e->shadowray.x;
	s.y = e->shadowray.y;
	s.z = e->shadowray.z;
	p.x = scene->pos.x;
	p.y = scene->pos.y;
	p.z = scene->pos.z;
	rt_rotate(scene, &s, &i, e);
	rt_rotate(scene, &z, &p, e);
	e->a = pow((s.x), 2) + pow((s.y), 2);
	e->b = 2 * ((s.x) * (i.x - p.x)
		+ s.y * (i.y - p.y));
	e->c = (pow((i.x - p.x), 2)
		+ pow((i.y - p.y), 2) - pow(scene->radius, 2));
	e->ray.delta_light = pow(e->b, 2) - 4 * e->a * e->c;
	get_light_to_print(e);
}
