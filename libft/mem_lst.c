/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmehay <cmehay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/29 11:23:20 by cmehay            #+#    #+#             */
/*   Updated: 2014/03/12 15:02:13 by cmehay           ###   ########.fr       */
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

/*
** This function adds a pointer address to the list.
*/
void				add_to_lst(void *ptr)
{
	t_alloc_lst	*new_item;
	t_alloc_lst	*current_lst;

	new_item = (t_alloc_lst*)malloc(sizeof(t_alloc_lst));
	new_item->ptr = (ssize_t)ptr;
	new_item->next = NULL;
	current_lst = gimme_ptr_lst(FALSE);
	while (current_lst->next)
		current_lst = current_lst->next;
	current_lst->next = new_item;
}

/*
** This function allocates memory and adds pointer address to a list.
*/
void				*cool_malloc(size_t len)
{
	void	*alloc;

	if (!(alloc = ft_memalloc(len)))
		return (alloc);
	add_to_lst(alloc);
	return (alloc);
}

/*
** This function frees the ptr only if it sets on the list.
*/
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

/*
** This function frees all allocated memory
*/
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
