/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-segu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/03 19:37:44 by sde-segu          #+#    #+#             */
/*   Updated: 2013/12/05 01:57:37 by sde-segu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*elem;
	t_list	*tmp;

	elem = *alst;
	while (elem)
	{
		tmp = elem->next;
		(*del)(elem->content, elem->content_size);
		free(elem);
		elem = tmp;
	}
	*alst = NULL;
}
