/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmehay <cmehay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/15 16:56:51 by cmehay            #+#    #+#             */
/*   Updated: 2014/03/15 19:04:17 by cmehay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_data	*set_cam(char **input, int line)
{
	static t_data	*cam = NULL;

	if ((cam && input) || (input && count_array(input) != 10))
		return ((t_data*)display_parse_error(CAM, line));
	if (!cam && input)
	{
		cam = (t_data *)safe_malloc(sizeof(t_data));
		cam->obj = CAM;
		cam->pos.x = ft_atoi(input[1]);
		cam->pos.y = ft_atoi(input[2]);
		cam->pos.z = ft_atoi(input[3]);
		cam->vect.x = ft_atoi(input[4]);
		cam->vect.y = ft_atoi(input[5]);
		cam->vect.z = ft_atoi(input[6]);
		cam->angle.x = ft_atoi(input[7]);
		cam->angle.y = ft_atoi(input[8]);
		cam->angle.z = ft_atoi(input[9]);
	}
	return (cam);
}

t_data	*get_cam(void)
{
	return (set_cam(NULL, 0));
}
