/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-segu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/20 12:29:13 by sde-segu          #+#    #+#             */
/*   Updated: 2013/12/08 22:27:38 by sde-segu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t		i;
	size_t		j;

	i = 0;
	j = ft_strlen(s2);
	if (j == 0)
		return ((char*)s1);
	while (s1[i] != '\0' && i < n - 1)
	{
		if (ft_strncmp(s1 + i, s2, j) == 0)
			return ((char*)(s1 + i));
		i++;
	}
	return (NULL);
}