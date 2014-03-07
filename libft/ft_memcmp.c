/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-segu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/23 20:46:13 by sde-segu          #+#    #+#             */
/*   Updated: 2013/12/08 22:32:07 by sde-segu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*p;
	unsigned char	*z;

	i = 0;
	p = (unsigned char*) s1;
	z = (unsigned char*) s2;
	while (i < n)
	{
		if (s1 == 0 || s2 == 0)
			return (p[i] - z[i]);
		if (p[i] != z[i])
			return (p[i] - z[i]);
		i++;
	}
	return (0);
}