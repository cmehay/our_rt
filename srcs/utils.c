/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmehay <cmehay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/13 14:12:41 by cmehay            #+#    #+#             */
/*   Updated: 2014/03/13 14:27:55 by cmehay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	*safe_malloc(size_t size)
{
	void	*rtn;

	rtn = cool_malloc(size);
	if (!rtn)
	{
		ft_putendl_fd("Can't malloc", 2);
		exit(2);
	}
	return (rtn);
}
