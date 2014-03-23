/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmehay <cmehay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/25 07:08:57 by sde-segu          #+#    #+#             */
/*   Updated: 2014/03/23 15:13:51 by cmehay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "rt.h"

static void	rotate_ligth(t_data *scene, t_env *e)
{
	t_data	*current;
	float	mem;

	current = scene;
	while (current)
	{
		if (e->angle[2])
		{
			mem = current->pos.x;
			current->pos.x = cos(e->angle[2] * M_PI / 180) * mem + sin(e->angle[2] * M_PI / 180) * current->pos.y;
			current->pos.y = -sin(e->angle[2] * M_PI / 180) * mem + cos(e->angle[2] * M_PI / 180) * current->pos.y;
		}
		if (e->angle[1])
		{
			mem = current->pos.x;
			current->pos.x = cos(e->angle[1] * M_PI / 180) * mem + sin(e->angle[1] * M_PI / 180) * current->pos.z;
			current->pos.z = -sin(e->angle[1] * M_PI / 180) * mem + cos(e->angle[1] * M_PI / 180) * current->pos.z;
		}
		if (e->angle[0])
		{
			mem = current->pos.y;
			current->pos.y = cos(e->angle[0] * M_PI / 180) * mem + sin(e->angle[0] * M_PI / 180) * current->pos.z;
			current->pos.z = -sin(e->angle[0] * M_PI / 180) * mem + cos(e->angle[0] * M_PI / 180) * current->pos.z;
		}
		current = current->next;
	}
}

int			main(int argc, char **argv)
{
	t_data	*scene;
	t_env	*e;
	int		fd;

	e = (t_env *)safe_malloc(sizeof(t_env));
	if (argc == 1)
		ft_putstr("enter a scene\n");
	if (argc == 2)
	{
		if ((fd = open(argv[1], O_RDONLY)) > 0)
		{
			if (!(scene = get_infos(e, fd)))
				return (return_parse_error());
			set_mlx(e, get_cam());
			mlx_expose_hook(e->mlx->win, expose_hook, e);
			rotate_ligth(scene, e);
			raytracer(e, &scene);
			downscale(e);
			mlx_key_hook(e->mlx->win, key_hook, e);
			mlx_loop(e->mlx->mlx);
		}
	}
	return (0);
}
