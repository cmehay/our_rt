/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-segu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/23 21:07:05 by sde-segu          #+#    #+#             */
/*   Updated: 2013/12/08 22:33:22 by sde-segu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	*ft_memcpy(void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*p;
	unsigned char	*z;

	i = 0;
	p = (unsigned char*) s2;
	z = (unsigned char*) s1;
	while (i < n)
	{
		z[i] = p[i];
		i++;
	}
	return (s1);
}