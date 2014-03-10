/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmehay <cmehay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/19 16:05:29 by cmehay            #+#    #+#             */
/*   Updated: 2014/03/09 18:56:03 by cmehay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdint.h>

typedef enum	e_bool
{
	FALSE,
	TRUE
}				t_bool;

# define BUFF_SIZE 200

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

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct	s_list	*next;
}					t_list;

void	*ft_memset(void *b, int c, size_t len);
void	ft_bzero(void *s, size_t n);
void	ft_putchar_fd(char c, int fd);
void	ft_putchar(char c);
void	ft_putstr_fd(char const *s, int fd);
void	ft_putstr(char const *s);
void	ft_putnbr_fd(int64_t n, int fd);
void	ft_putnbr(int64_t n);
void	ft_putendl_fd(char const *s, int fd);
void	ft_putendl(char const *s);
size_t	ft_strlen(char const *s);
char	*ft_strcat(char *s1, const char *s2);
char	*ft_strncat(char *s1, const char *s2, size_t n);
char	*ft_strtrim(char const *s);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_atoi(const char *str);
int		ft_toupper(int c);
int		ft_tolower(int c);
void	*ft_memalloc(size_t size);
char	*ft_strnew(size_t size);
void	*ft_memcpy(void *s1, const void *s2, size_t n);
void	*ft_memccpy(void *s1, const void *s2, int c, size_t n);
void	*ft_memmove(void *s1, const void *s2, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	*ft_strdup(const char *s1);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
char	*ft_strcpy(char *s1, const char *s2);
char	*ft_strncpy(char *s1, const char *s2, size_t n);
char	*ft_strrchr(const char *s, int c);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strstr(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *s1, const char *s2, size_t n);
void	ft_memdel(void **ap);
void	ft_arraydel(char **array);
char	*ft_itoa(int64_t n);
int		ft_strequ(char const *s1, char const *s2);
int		ft_strnequ(char const *s1, char const *s2, size_t n);
void	ft_strdel(char **as);
void	ft_strclr(char *s);
void	ft_striter(char *s, void (*f)(char *));
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
char	*ft_strmap(char const *s, char (*f)(char));
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_strsub(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_strsplit(char const *s, char c);

/*
** Additum
*/
int		get_next_line(int const fd, char **line);
int		ft_strtest(char *str, int (*f)(int));
char	*ft_strrep(char *s1, char *s2, char *str);
int		ft_higher(int *array, int len);
int		ft_higher_idx(int *array, int len);
int		ft_lower(int *array, int len);
int		ft_lower_idx(int *array, int len);
void	ft_lstadd(t_list **alst, t_list *new);
void	ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void	ft_lstiter(t_list *list, void (*f)(t_list *elem));
void	ft_lstdelone(t_list **alst, void (*del)(void *, size_t));

/*
** mem_lst.c
*/
void	add_to_lst(void *ptr);
void	*cool_malloc(size_t len);
void	cool_free(void *ptr);
void	free_for_all(t_alloc_lst *lst);

/*
** Cool functions
** Those functions use cool_malloc instead of malloc
*/
char	*cool_strnew(size_t size);
char	*cool_itoa(int64_t n);
void	cool_strdel(char **as);
void	cool_memdel(void **ap);
void	cool_arraydel(char **array);
char	*cool_strdup(const char *s1);
char	*cool_strjoin(char const *s1, char const *s2);
char	*cool_strmap(char const *s, char (*f)(char));
char	*cool_strmapi(char const *s, char (*f)(unsigned int, char));
char	**cool_strsplit(char const *s, char c);
char	*cool_strsub(char const *s, unsigned int start, size_t len);
char	*cool_strtrim(char const *s);
int		cool_next_line(int const fd, char **line);
char	*cool_strrep(char *s1, char *s2, char *str);

#endif
