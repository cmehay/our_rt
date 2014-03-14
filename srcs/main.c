/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmehay <cmehay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/25 07:08:57 by sde-segu          #+#    #+#             */
/*   Updated: 2014/03/13 15:19:32 by cmehay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		main(int argc, char **argv)
{
	t_data	*scene;
	t_env	*e;
	int		fd;

	e = (t_env *)malloc(sizeof(t_env));
	if (argc == 1)
		ft_putstr("enter a scene\n");
	if (argc == 2)
	{
		if ((fd = open(argv[1], O_RDONLY)) > 0)
		{
			scene = get_infos(fd);
			set_mlx(e, scene);
			raytracer(e, &scene);
			mlx_key_hook(e->mlx->win, key_hook, e);
			mlx_expose_hook(e->mlx->win, expose_hook, e);
			mlx_loop(e->mlx->mlx);
		}
	}
	return (0);
}
