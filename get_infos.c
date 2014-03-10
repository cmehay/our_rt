/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_infos.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-segu <sde-segu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/25 07:13:36 by sde-segu          #+#    #+#             */
/*   Updated: 2014/02/25 07:13:37 by sde-segu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_data		*get_infos(int fd)
{
	char	*line;
	t_data	*list;

	list = (t_data *)malloc(sizeof(*list));
	get_next_line(fd, &line);
	get_next_line(fd, &line);
	list = init_list_with_cam(&list, line);
	while (get_next_line(fd, &line) > 0)
		fill_list_with_obj(&list, line);
	free(line);
	return (list);
}

t_data		*init_list_with_cam(t_data **list, char *line)
{
	char	**tab;
	t_data	*cam;

	cam = (t_data *)malloc(sizeof(*list));
	tab = ft_strsplit(line, ' ');
	cam->x = ft_atoi(tab[1]);
	cam->y = ft_atoi(tab[2]);
	cam->z = ft_atoi(tab[3]);
	cam->vectx = ft_atoi(tab[4]);
	cam->vecty = ft_atoi(tab[5]);
	cam->vectz = ft_atoi(tab[6]);
	cam->angle_x = ft_atoi(tab[7]);
	cam->angle_y = ft_atoi(tab[8]);
	cam->angle_z = ft_atoi(tab[9]);
	cam->next = NULL;
	return (cam);
}

int		fill_list_with_obj(t_data **list, char *line)
{
	int		i;
	char	**tab;
	t_data	*obj;
	t_data	*tmp;

	i = 0;
	tab = ft_strsplit(line, ' ');
	while (tab && tab[i])
		i++;
	if (i != 11)
		return (-1);
	tmp = (t_data *)malloc(sizeof(*tmp));
	obj = (t_data *)malloc(sizeof(*obj));
	obj = collect_info_about_obj(obj, tab);
	tmp = *list;
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = obj;
	}
	return (0);
}

t_data	*collect_info_about_obj(t_data *obj, char **tab)
{
	obj->what = ft_strdup(tab[0]);
	obj->x = ft_atoi(tab[1]);
	obj->y = ft_atoi(tab[2]);
	obj->z = ft_atoi(tab[3]);
	obj->radius = ft_atoi(tab[4]);
	obj->rgb[0] = ft_atoi(tab[5]);
	obj->rgb[1] = ft_atoi(tab[6]);
	obj->rgb[2] = ft_atoi(tab[7]);
	obj->angle_x = ft_atoi(tab[8]);
	obj->angle_y = ft_atoi(tab[9]);
	obj->angle_z = ft_atoi(tab[10]);
	obj->next = NULL;
	return (obj);
}
