/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-segu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/19 15:25:09 by sde-segu          #+#    #+#             */
/*   Updated: 2013/12/01 23:34:20 by sde-segu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strstr(const char *s1, const char *s2)
{
	int		i;
	int		j;

	i = 0;
	j = ft_strlen(s2);
	if (j == 0)
		return ((char*)s1);
	while (s1[i] != '\0')
	{
		if (ft_strncmp(s1 + i, s2, j) == 0)
			return ((char*)(s1 + i));
		i++;
	}
	return (NULL);
}