/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-segu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/23 13:18:04 by sde-segu          #+#    #+#             */
/*   Updated: 2013/12/01 23:29:08 by sde-segu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*copy;

	i = 0;
	copy = (char *) s;
	while (s[i] != '\0')
	{
		if (s[i] == (char) c)
		return (&copy[i]);
	i++;
	}
	if (copy[i] == '\0' && c == '\0')
		return (&(copy[i]));
	return (NULL);
}