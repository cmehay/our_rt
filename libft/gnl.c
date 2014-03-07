/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-segu <sde-segu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/25 03:12:06 by sde-segu          #+#    #+#             */
/*   Updated: 2014/02/25 03:12:12 by sde-segu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static char		*ft_strnjoin(char *s1, char *s2, int n)
{
	size_t	len;
	char	*str;
	size_t	j;

	j = 0;
	len = (s1 != NULL) ? ft_strlen((char *)s1) : 0;
	str = malloc(sizeof(char) * (len + n + 1));
	if (str == NULL)
		return (NULL);
	str = ft_strcpy(str, s1);
	while (j < (size_t)n)
	{
		*(str + len + j) = *s2;
		j++;
		s2++;
	}
	*(str + len + j) = '\0';
	if (s1)
		free(s1);
	return (str);
}

static char		*ft_strljoin(char *s1, char const *s2)
{
	size_t	len;
	size_t	size;
	char	*str;
	size_t	j;

	j = 0;
	len = (s1 != NULL) ? ft_strlen((char *)s1) : 0;
	size = ft_strlen((char *)s2);
	str = malloc(sizeof(char) * (size + len + 2));
	if (str == NULL)
		return (NULL);
	str = ft_strcpy(str, s1);
	while (j <= (size + 1))
	{
		str[len + j] = *s2;
		j++;
		s2++;
	}
	if (s1)
		free(s1);
	return (str);
}

int				gnl(int const fd, char **line)
{
	int			ret;
	static char	buff[BUFF_SIZE + 1] = {0};
	int			j;

	*line = NULL;
	ret = 1;
	if (fd < 0 || !ret)
		return (-1);
	while (1)
	{
		j = 0;
		while (ret && buff[j] != '\n' && buff[j] != '\0')
			j++;
		if (ret && buff[j] == '\n')
		{
			*line = ft_strnjoin(*line, buff, j);
			ft_memcpy(buff, buff + j + 1, BUFF_SIZE - j);
			return (1);
		}
		*line = ft_strljoin(*line, buff);
		ret = read(fd, buff, BUFF_SIZE);
		if (ret <= 0)
			return (ret);
		buff[ret] = '\0';
	}
}
