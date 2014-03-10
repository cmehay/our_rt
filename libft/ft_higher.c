/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_higher.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmehay <cmehay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/03 16:48:31 by cmehay            #+#    #+#             */
/*   Updated: 2014/03/03 17:22:27 by cmehay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_higher(int *array, int len)
{
	int	rtn;

	rtn = array[--len];
	while (len--)
		rtn = (array[len] > rtn) ? array[len] : rtn;
	return (rtn);
}

int	ft_higher_idx(int *array, int len)
{
	int	check;
	int	rtn;

	check = array[--len];
	rtn = len;
	while (len--)
	{
		if (array[len] > check)
		{
			check = array[len];
			rtn = len;
		}
	}
	return (rtn);
}
