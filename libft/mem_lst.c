/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmehay <cmehay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/29 11:23:20 by cmehay            #+#    #+#             */
/*   Updated: 2014/03/26 21:46:27 by cmehay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_alloc_lst	*gimme_ptr_lst(t_bool reset)
{
	static t_alloc_lst	*lst = NULL;

	if (reset)
		return ((lst = NULL));
	if (!lst)
	{
		lst = (t_alloc_lst*)malloc(sizeof(t_alloc_lst));
		lst->ptr = -1;
		lst->next = NULL;
	}
	return (lst);
}

t_bool				add_to_lst(void *ptr)
{
	t_alloc_lst	*new_item;
	t_alloc_lst	*current_lst;

	if (!(new_item = (t_alloc_lst*)malloc(sizeof(t_alloc_lst))))
		return (FALSE);
	new_item->ptr = (ssize_t)ptr;
	new_item->next = NULL;
	current_lst = gimme_ptr_lst(FALSE);
	if (!current_lst)
		return (FALSE);
	while (current_lst->next)
		current_lst = current_lst->next;
	current_lst->next = new_item;
	return (TRUE);
}

void				*cool_malloc(size_t len)
{
	void	*alloc;

	if (!(alloc = ft_memalloc(len)))
		return (alloc);
	if (!add_to_lst(alloc))
	{
		free(alloc);
		return (NULL);
	}
	return (alloc);
}

void				cool_free(void *ptr)
{
	t_alloc_lst	*lst;
	t_alloc_lst	*prev;

	prev = NULL;
	lst = gimme_ptr_lst(FALSE);
	while (lst->next)
	{
		if (lst->ptr == (ssize_t)ptr)
		{
			free(ptr);
			if (prev)
				prev->next = lst->next;
			free(lst);
			return ;
		}
		prev = lst;
		lst = lst->next;
	}
	if (lst->ptr == (ssize_t)ptr)
	{
		free(ptr);
		if (prev)
			prev->next = NULL;
		free(lst);
	}
}

void				free_for_all(t_alloc_lst *lst)
{
	if (!lst)
		lst = gimme_ptr_lst(FALSE);
	if (lst->next)
		free_for_all(lst->next);
	if (lst->ptr && lst->ptr != -1)
	{
		free((void*)lst->ptr);
		free(lst);
	}
	else
	{
		free(lst);
		gimme_ptr_lst(TRUE);
	}
}
