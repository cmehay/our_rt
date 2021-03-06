/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmehay <cmehay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/22 14:54:37 by cmehay            #+#    #+#             */
/*   Updated: 2014/03/26 21:48:21 by cmehay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*cp;

	cp = (char*)s + ft_strlen(s);
	while (cp >= s)
	{
		if (*cp == (char)c)
			return (cp);
		cp--;
	}
	return (NULL);
}
