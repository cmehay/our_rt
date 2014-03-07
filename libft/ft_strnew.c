/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-segu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/27 20:04:30 by sde-segu          #+#    #+#             */
/*   Updated: 2013/12/08 22:38:04 by sde-segu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strnew(size_t size)
{
	size_t	i;
	char	*result;

	i = 0;
	result = (char*)malloc(sizeof(char) * size);
	if (result == NULL)
		return (NULL);
	while (i <= size)
	{
		result[i] = '\0';
		i++;
	}
	return (result);
}