/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-segu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/23 17:39:37 by sde-segu          #+#    #+#             */
/*   Updated: 2013/11/30 19:33:44 by sde-segu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	*ft_memccpy(void *s1, const void *s2, int c, size_t n)
{
	size_t			i;
	unsigned char	*p;
	unsigned char	*z;

	i = 0;
	p = (unsigned char*)s2;
	z = (unsigned char*)s1;
	while (i < n)
	{
		z[i] = p[i];
		if (z[i] == (char)c)
			return (z + i + 1);
		i++;
	}
	return (NULL);
}