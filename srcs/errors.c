/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmehay <cmehay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/15 17:53:36 by cmehay            #+#    #+#             */
/*   Updated: 2014/03/15 19:34:08 by cmehay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	*display_parse_error(t_obj type, int line)
{
	char	**objs;

	objs = gimme_obj_list();
	ft_putstr_fd("Object type ", 2);
	ft_putstr_fd(objs[type - 1], 2);
	ft_putstr_fd(" ignored at line ", 2);
	ft_putnbr_fd(line, 2);
	ft_putendl_fd(".", 2);
	return (NULL);
}

void	display_ignored_line(int line)
{
	ft_putstr_fd("Line ", 2);
	ft_putnbr_fd(line, 2);
	ft_putendl_fd(" from map ignored.", 2);
}

int		return_parse_error(void)
{
	ft_putendl_fd("Parse error, camera is probably missing", 2);
	return (1);
}
