/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_structs.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmehay <cmehay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 21:49:24 by cmehay            #+#    #+#             */
/*   Updated: 2014/03/26 21:53:04 by cmehay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_STRUCTS_H
# define LIBFT_STRUCTS_H

# include <unistd.h>

typedef enum	e_bool
{
	FALSE,
	TRUE
}				t_bool;

typedef struct	s_strlen
{
	size_t	s1;
	size_t	s2;
}				t_strlen;

typedef struct	s_alloc_lst
{
	ssize_t				ptr;
	struct s_alloc_lst	*next;
}				t_alloc_lst;

typedef struct	s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;

#endif
