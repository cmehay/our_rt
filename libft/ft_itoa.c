/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-segu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/28 18:39:11 by sde-segu          #+#    #+#             */
/*   Updated: 2013/12/05 01:56:59 by sde-segu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static int		ft_len(int n)
{
	int		len;

	len = 0;
	if (n == 0)
		len = 1;
	if (n < 0)
		len = len + 1;
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char			*ft_itoa(int n)
{
	int		len;
	char	*result;
	int		t;

	len = ft_len(n);
	t = n;
	result = (char*)malloc(sizeof(char) * len + 1);
	if (result == NULL)
		return (NULL);
	if (t == -2147483648)
		return (ft_strdup("-2147483648"));
	if (t < 0)
	{
		result[0] = '-';
		t = -t;
	}
	else if (t == 0)
		result[0] = 48;
	while (t != 0)
	{
		result[--len] = t % 10 + '0';
		t = t / 10;
	}
	return (result);
}