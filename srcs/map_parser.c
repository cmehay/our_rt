/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmehay <cmehay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/15 14:37:00 by cmehay            #+#    #+#             */
/*   Updated: 2014/03/23 20:16:35 by cmehay           ###   ########.fr       */
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
		OBJ_ALIASING,
		OBJ_HEIGHT,
		OBJ_WIDTH,
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

void	set_options(char **split, t_env *e, t_obj obj, int line)
{
	int	set;

	if (count_array(split) != 2 || !ft_strtest(split[1], ft_isdigit))
	{
		display_parse_error(obj, line);
		return ;
	}
	if (obj == ANTIALIASING && (set = ft_atoi(split[1])) < 4)
		e->screen.upscale = set;
	if (obj == WIDTH)
		e->screen.display.w = ft_atoi(split[1]);
	if (obj == HEIGHT)
		e->screen.display.h = ft_atoi(split[1]);
}
