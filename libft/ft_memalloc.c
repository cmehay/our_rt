/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-segu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/27 19:41:58 by sde-segu          #+#    #+#             */
/*   Updated: 2013/12/01 19:48:58 by sde-segu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	*ft_memalloc(size_t size)
{
	size_t	i;
	char	*result;

	i = 0;
	result = malloc(size);
	if (result == NULL)
		return (NULL);
	while (i <= size)
	{
		result[i] = '\0';
		i++;
	}
	return (result);
}