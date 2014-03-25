/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_demi_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcouly <dcouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/25 15:11:27 by dcouly            #+#    #+#             */
/*   Updated: 2014/03/25 20:15:52 by dcouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	rt_dcylinder(t_env *e, t_data *scene)
{
	t_pos	v;
	t_pos	o;
	t_pos	a;
	t_pos	x;

	a.x = e->angle[0];
	a.y = -e->angle[1];
	a.z = e->angle[2];
	o.x = e->cam.x - scene->pos.x;
	o.z = e->cam.z - scene->pos.z;
	o.y = e->cam.y - scene->pos.y;
	v.x = e->vect.x;
	v.z = e->vect.z;
	v.y = e->vect.y;
	x.x = scene->angle.x;
	x.y = scene->angle.y;
	x.z = scene->angle.z;
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
	if (e->ray.delta > 0)
		get_dcyl_to_print(e, scene);
}

#include <stdio.h>

int		get_dcyl_to_print(t_env *e, t_data *scene)
{
	float	min_i;
	float	max_i;
	float	inter1;
	float	inter2;
	float	inter_z;
	float	change;
	t_pos	angle;
	t_pos	inter;
	t_pos	inu;

	angle.x = e->angle[0];
	angle.y = -e->angle[1];
	angle.z = e->angle[2];
	change = 0;
	inter1 = (-e->b + sqrt(e->ray.delta)) / (2 * e->a);
	inter2 = (-e->b - sqrt(e->ray.delta)) / (2 * e->a);
	min_i = fmin(inter1, inter2);
	max_i = fmax(inter1, inter2);
	inter.z = min_i * e->vect.z - scene->pos.z + e->cam.z;
	inter.y = min_i * e->vect.y - scene->pos.y + e->cam.y;
	inter.x = min_i * e->vect.x - scene->pos.x + e->cam.x;
	rt_rotate_x(&angle, &inter, &inu, e);
	rt_rotate_y(&angle, &inter, &inu, e);
	rt_rotate_z(&angle, &inter, &inu, e);
	inter_z = -sinf(-scene->angle.x * M_PI / 180) * inter.y + cosf(-scene->angle.x * M_PI / 180) * inter.z;
	inter_z = sinf(-scene->angle.y * M_PI / 180) * inter.x + cosf(-scene->angle.y * M_PI / 180) * inter_z;
	inter_z = inter_z + scene->pos.z;
	if (inter_z < scene->pos.z + scene->min || inter_z > scene->pos.z + scene->max)
	{
		change = min_i;
		min_i = max_i;
		max_i = change;
		change = 1;
		inter.z = min_i * e->vect.z - scene->pos.z + e->cam.z;
		inter.y = min_i * e->vect.y - scene->pos.y + e->cam.y;
		inter.x = min_i * e->vect.x - scene->pos.x + e->cam.x;
		rt_rotate_x(&angle, &inter, &inu, e);
		rt_rotate_y(&angle, &inter, &inu, e);
		rt_rotate_z(&angle, &inter, &inu, e);
		inter_z = -sinf(-scene->angle.x * M_PI / 180) * inter.y + cosf(-scene->angle.x * M_PI / 180) * inter.z;
		inter_z = sinf(-scene->angle.y * M_PI / 180) * inter.x + cosf(-scene->angle.y * M_PI / 180) * inter_z;
		inter_z = inter_z + scene->pos.z;
		if (inter_z < scene->pos.z + scene->min || inter_z > scene->pos.z + scene->max)
			return (0);
	}
	if (((e->ray.inter == -1) || e->ray.inter > min_i) && min_i > 0.01)
	{
		e->angle_ob.x = scene->angle.x;
		e->angle_ob.y = scene->angle.y;
		e->angle_ob.z = scene->angle.z;
		e->ray.inter = inter2;
		e->object = 6;
		e->heart_plan[3] = (inter_z < scene->pos.z) ? -change : change;
		e->heart_sphere[0] = scene->pos.x;
		e->heart_sphere[1] = scene->pos.y;
		e->heart_sphere[2] = scene->pos.z;
		e->color.red = scene->rgb[0];
		e->color.green = scene->rgb[1];
		e->color.blue = scene->rgb[2];
	}
	return (0);
}

int		get_light_to_demi_c(t_env *e, t_data *scene)
{
	float	inter1;
	t_pos	inter;
	float	inter2;
	float	min;
	float	max;
	float	mem = 0;
	t_pos	angle;
	t_pos	inu;

	angle.x = e->angle[0];
	angle.y = -e->angle[1];
	angle.z = e->angle[2];
	if (e->ray.delta_light >= 0)
	{
		inter2 = (-e->b + sqrt(e->ray.delta_light)) / (2 * e->a);
		inter1 = (-e->b - sqrt(e->ray.delta_light)) / (2 * e->a);
		min = fmin(inter2, inter1);
		max = fmax(inter2, inter1);
		inter.z = min * e->shadowray.z + e->inter.z - scene->pos.z;
		inter.y = min * e->shadowray.y + e->inter.y - scene->pos.y;
		inter.x = min * e->shadowray.x + e->inter.x - scene->pos.x;
		rt_rotate_x(&angle, &inter, &inu, e);
		rt_rotate_y(&angle, &inter, &inu, e);
		rt_rotate_z(&angle, &inter, &inu, e);
		mem = -sinf(-scene->angle.x * M_PI / 180) * inter.y + cosf(-scene->angle.x     * M_PI / 180) * inter.z;
		mem = sinf(-scene->angle.y * M_PI / 180) * inter.x + cosf(-scene->angle.y *     M_PI / 180) * mem;
		mem = mem + scene->pos.z;
		if (mem > scene->pos.z + scene->max || mem < scene->pos.z + scene->min)
		{
			mem = max;
			max = min;
			min = mem;
			inter.z = min * e->shadowray.z + e->inter.z - scene->pos.z;
			inter.y = min * e->shadowray.y + e->inter.y - scene->pos.y;
			inter.x = min * e->shadowray.x + e->inter.x - scene->pos.x;
			rt_rotate_x(&angle, &inter, &inu, e);
			rt_rotate_y(&angle, &inter, &inu, e);
			rt_rotate_z(&angle, &inter, &inu, e);
			mem = -sinf(-scene->angle.x * M_PI / 180) * inter.y + cosf(-scene->angle.x * M_PI / 180) * inter.z;
			mem = sinf(-scene->angle.y * M_PI / 180) * inter.x + cosf(-scene->angle.y * M_PI / 180) * mem;
			mem = mem + scene->pos.z;
			if (mem > scene->pos.z + scene->max || mem < scene->pos.z + scene->min)
				return (0);
		}
		if (min > 0.1 && (max < e->lenght))
		{
			e->light_bis = 0;
			e->ray.inter_light = min;
			if (e->color.red > 20)
				e->color.red /= 2;
			if (e->color.green > 20)
				e->color.green /= 2;
			if (e->color.blue > 20)
				e->color.blue /= 2;
			return (1);
		}
	}
	return (0);
}

void	lightdcylinder(t_env *e)
{
	float	len;
	t_pos	i;
	t_pos	s;
	float	scal;
	t_pos	a;

	a.x = e->angle[0];
	a.y = -e->angle[1];
	a.z = e->angle[2];
	i.x = e->inter.x - e->heart_sphere[0];
	i.y = e->inter.y - e->heart_sphere[1];
	i.z = e->inter.z - e->heart_sphere[2];
	s.x = e->shadowray.x;
	s.y = e->shadowray.y;
	s.z = e->shadowray.z;
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
		 + e->normal.z * s.z) / (e->ray.len / 60);
	if (scal > 0.2)
		e->light_bis = fmax(pow(scal * (e->ray.len / 60), 60), e->light_bis);
	scal = (scal > 1) ? 1 : scal;
	scal = (scal < 0.05) ? 0.05 : scal;
	e->light *= scal;
}

int		size_light_on_dcyl(t_env *e, t_data *scene)
{
	t_pos	s;
	t_pos	i;
	t_pos	p;
	t_pos	a;
	t_pos	z;

	a.x = e->angle[0];
	a.y = -e->angle[1];
	a.z = e->angle[2];
	i.x = e->inter.x;
	i.y = e->inter.y;
	i.z = e->inter.z;
	s.x = e->shadowray.x;
	s.y = e->shadowray.y;
	s.z = e->shadowray.z;
	p.x = scene->pos.x;
	p.y = scene->pos.y;
	p.z = scene->pos.z;
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
	return (get_light_to_demi_c(e, scene));
}
