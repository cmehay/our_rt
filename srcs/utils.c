/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmehay <cmehay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/13 14:12:41 by cmehay            #+#    #+#             */
/*   Updated: 2014/03/23 20:20:37 by cmehay           ###   ########.fr       */
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

int		count_array(char **array)
{
	int	i;

	i = 0;
	while (array && *array++)
		i++;
	return (i);
}

char	*sanityze_str(char *str)
{
	char	*rtn;

	rtn = str;
	while (str && *str)
	{
		*str = (*str == '\t') ? ' ' : *str;
		str++;
	}
	return (rtn);
}

int		min_three(int a, int b, int c)
{
	int	rtn;

	rtn = a;
	if (b < rtn)
		rtn = b;
	if (c < rtn)
		rtn = c;
	return (rtn);
}

int		max_three(int a, int b, int c)
{
	int	rtn;

	rtn = a;
	if (b > rtn)
		rtn = b;
	if (c > rtn)
		rtn = c;
	return (rtn);
}
