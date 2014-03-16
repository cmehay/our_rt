/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcouly <dcouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/16 15:57:57 by dcouly            #+#    #+#             */
/*   Updated: 2014/03/16 18:33:47 by dcouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	rt_rotate_x(t_pos a, t_pos *v, t_pos *o, t_env *e)
{
	float	mem;
	float	an;

	if ((an = e->angle[0]))
	{
		mem = v->y;
		v->y = cos(an * M_PI / 180) * mem - sin(an * M_PI / 180) * v->z;
		v->z = sin(an * M_PI / 180) * mem + cos(an * M_PI / 180) * v->z;
	}
	if (a.x)
	{
		mem = v->y;
		v->y = cos(a.x * M_PI / 180) * mem - sin(a.x * M_PI / 180) * v->z;
		v->z = sin(a.x * M_PI / 180) * mem + cos(a.x * M_PI / 180) * v->z;
		mem = o->y;
		o->y = cos(a.x * M_PI / 180) * mem - sin(a.x * M_PI / 180) * o->z;
		o->z = sin(a.x * M_PI / 180) * mem + cos(a.x * M_PI / 180) * o->z;
	}
}

static void	rt_rotate_z(t_pos a, t_pos *v, t_pos *o, t_env *e)
{
	float	mem;
	float	an;

	if ((an = e->angle[2]))
	{
		mem = v->x;
		v->x = cos(an * M_PI / 180) * mem - sin(an * M_PI / 180) * v->y;
		v->y = sin(an * M_PI / 180) * mem + cos(an * M_PI / 180) * v->y;
	}
	if (a.z)
	{
		mem = v->x;
		v->x = cos(a.z * M_PI / 180) * mem - sin(a.z * M_PI / 180) * v->y;
		v->y = sin(a.z * M_PI / 180) * mem + cos(a.z * M_PI / 180) * v->y;
		mem = o->x;
		o->x = cos(a.z * M_PI / 180) * mem - sin(a.z * M_PI / 180) * o->y;
		o->y = sin(a.z * M_PI / 180) * mem + cos(a.z * M_PI / 180) * o->y;
	}
}

static void	rt_rotate_y(t_pos a, t_pos *v, t_pos *o, t_env *e)
{
	float	mem;
	float	an;

	if ((an = e->angle[1]))
	{
		mem = v->x;
		v->x = cos(an * M_PI / 180) * mem + sin(an * M_PI / 180) * v->z;
		v->z = sin(an * M_PI / 180) * mem * -1 + cos(an * M_PI / 180) * v->z;
	}
	if (a.y)
	{
		mem = v->x;
		v->x = cos(a.y * M_PI / 180) * mem + sin(a.y * M_PI / 180) * v->z;
		v->z = sin(a.y * M_PI / 180) * mem * -1 + cos(a.y * M_PI / 180) * v->z;
		mem = o->x;
		o->x = cos(a.y * M_PI / 180) * mem + sin(a.y * M_PI / 180) * o->z;
		o->z = sin(a.y * M_PI / 180) * mem * -1 + cos(a.y * M_PI / 180) * o->z;
	}
}

void		rt_rotate(t_data *scene, t_pos *v, t_pos *o, t_env *e)
{
	t_pos	 a;

	a = scene->angle;
	rt_rotate_y(a, v, o, e);
	rt_rotate_x(a, v, o, e);
	rt_rotate_z(a, v, o, e);
}