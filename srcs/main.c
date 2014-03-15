/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmehay <cmehay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/25 07:08:57 by sde-segu          #+#    #+#             */
/*   Updated: 2014/03/15 19:34:09 by cmehay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		main(int argc, char **argv)
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
			if (!(scene = get_infos(fd)))
				return (return_parse_error());
			set_mlx(e, get_cam());
			raytracer(e, &scene);
			mlx_key_hook(e->mlx->win, key_hook, e);
			mlx_expose_hook(e->mlx->win, expose_hook, e);
			mlx_loop(e->mlx->mlx);
		}
	}
	return (0);
}
