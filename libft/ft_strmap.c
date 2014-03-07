/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-segu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/28 01:43:34 by sde-segu          #+#    #+#             */
/*   Updated: 2013/12/01 23:32:21 by sde-segu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	int		i;
	char	*result;

	i = 0;
	while (s[i] != '\0')
		i++;
	result = (char*)malloc(sizeof(char) * i);
	i = 0;
	while (s[i] != '\0')
	{
		result[i] = f(s[i]);
		i++;
	}
	return (result);
}