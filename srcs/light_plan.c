/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_plan.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmehay <cmehay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/24 18:39:04 by cmehay            #+#    #+#             */
/*   Updated: 2014/03/24 19:08:50 by cmehay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		lightplan(t_env *e)
{
	float	scal;
	float	len;
	float	x;
	float	y;
	float	z;

	len = sqrt(e->heart_plan[0] * e->heart_plan[0] + e->heart_plan[1]
	* e->heart_plan[1] + e->heart_plan[2] * e->heart_plan[2]);
	x = e->heart_plan[0] / len;
	y = e->heart_plan[1] / len;
	z = e->heart_plan[2] / len;
	scal = 60 / (e->ray.len);
	scal = (scal > 1) ? 1 : scal;
	e->light *= scal;
	x = x * e->shadowray.x + y * e->shadowray.y + z * e->shadowray.z;
	e->light_bis = fmax(pow(x, 1600), e->light_bis);
	return (0);
}

int		size_light_on_plan(t_env *e, t_data *scene)
{
	float	inter;
	float	x;
	float	y;
	float	z;

	x = e->inter.x;
	y = e->inter.y;
	z = e->inter.z;
	inter = -((scene->pos.x * x + scene->pos.y * y + scene->pos.z * z
		+ scene->radius) / (scene->pos.x * e->shadowray.x
		+ scene->pos.y * e->shadowray.y + scene->pos.z * e->shadowray.z));
	if (inter > 20 && (inter < e->screen.length))
	{
		if (e->color.blue > 20)
			e->color.blue /= 2;
		if (e->color.green > 20)
			e->color.green /= 2;
		if (e->color.red > 20)
			e->color.red /= 2;
		return (1);
	}
	return (0);
}
