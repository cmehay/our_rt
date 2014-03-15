/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_infos.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmehay <cmehay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/25 07:13:36 by sde-segu          #+#    #+#             */
/*   Updated: 2014/03/15 19:28:29 by cmehay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_data		*get_infos(int fd)
{
	char	*line;
	char	**split;
	t_data	*list;
	int		line_nb;
	t_obj	obj;

	line_nb = 0;
	list = NULL;
	while (cool_next_line(fd, &line) > 0 && line && ++line_nb)
	{
		split = cool_strsplit(sanityze_str(line), ' ');
		if (split && split[0] && parse_object(split[0]) == CAM)
			set_cam(split, line_nb);
		else if (split && split[0] && (obj = parse_object(split[0])) > CAM)
			fill_list_with_obj(&list, split, obj, line_nb);
		else
			display_ignored_line(line_nb);
		cool_free(line);
	}
	if (!get_cam())
		return (NULL);
	return (list);
}

void	fill_list_with_obj(t_data **list, char **tab, t_obj type, int line)
{
	t_data	*obj;
	t_data	*tmp;

	if (count_array(tab) != 11)
	{
		display_parse_error(type, line);
		return ;
	}
	obj = (t_data *)safe_malloc(sizeof(t_data));
	obj = collect_info_about_obj(obj, tab, type);
	tmp = *list;
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = obj;
	}
	else
		*list = obj;
}

t_data	*collect_info_about_obj(t_data *obj, char **tab, t_obj type)
{
	obj->obj = type;
	obj->pos.x = ft_atoi(tab[1]);
	obj->pos.y = ft_atoi(tab[2]);
	obj->pos.z = ft_atoi(tab[3]);
	obj->radius = ft_atoi(tab[4]);
	obj->rgb[0] = ft_atoi(tab[5]);
	obj->rgb[1] = ft_atoi(tab[6]);
	obj->rgb[2] = ft_atoi(tab[7]);
	obj->angle.x = ft_atoi(tab[8]);
	obj->angle.y = ft_atoi(tab[9]);
	obj->angle.z = ft_atoi(tab[10]);
	obj->next = NULL;
	return (obj);
}
