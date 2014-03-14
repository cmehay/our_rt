/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_infos.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmehay <cmehay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/25 07:13:36 by sde-segu          #+#    #+#             */
/*   Updated: 2014/03/14 14:49:14 by cmehay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_data		*get_infos(int fd)
{
	char	*line;
	t_data	*list;

	list = (t_data *)safe_malloc(sizeof(t_data));
	cool_next_line(fd, &line);
	cool_next_line(fd, &line);
	list = init_list_with_cam(line);
	while (cool_next_line(fd, &line) > 0)
		fill_list_with_obj(&list, line);
	cool_free(line);
	return (list);
}

t_data		*init_list_with_cam(char *line)
{
	char	**tab;
	t_data	*cam;

	cam = (t_data *)safe_malloc(sizeof(t_data));
	tab = ft_strsplit(line, ' ');
	cam->pos.x = ft_atoi(tab[1]);
	cam->pos.y = ft_atoi(tab[2]);
	cam->pos.z = ft_atoi(tab[3]);
	cam->vect.x = ft_atoi(tab[4]);
	cam->vect.y = ft_atoi(tab[5]);
	cam->vect.z = ft_atoi(tab[6]);
	cam->angle.x = ft_atoi(tab[7]);
	cam->angle.y = ft_atoi(tab[8]);
	cam->angle.z = ft_atoi(tab[9]);
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
	obj = (t_data *)safe_malloc(sizeof(t_data));
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
