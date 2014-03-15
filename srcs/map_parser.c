/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmehay <cmehay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/15 14:37:00 by cmehay            #+#    #+#             */
/*   Updated: 2014/03/15 18:34:51 by cmehay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

char	**gimme_obj_list(void)
{
	static char	*objs[] =
	{
		OBJ_CAM,
		OBJ_SPHERE,
		OBJ_CYLINDER,
		OBJ_CONE,
		OBJ_PLAN,
		OBJ_LIGHT,
		NULL
	};

	return (objs);
}

t_obj	parse_object(char *input)
{
	t_obj	count;
	char	**objs;

	objs = gimme_obj_list();
	count = count_array(objs) + 1;
	while (--count)
	{
		if (ft_strequ(objs[count - 1], input))
			return (count);
	}
	return (count);
}

