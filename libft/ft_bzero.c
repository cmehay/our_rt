/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-segu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/23 14:30:15 by sde-segu          #+#    #+#             */
/*   Updated: 2013/12/05 01:53:06 by sde-segu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t				i;
	unsigned char		*p;

	i = 0;
	p = (unsigned char*) s;
	if (n == 0)
		return ;
	while (i < n)
	{
		p[i] = '\0';
		i++;
	}
}
