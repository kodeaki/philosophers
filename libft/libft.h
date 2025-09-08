/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpirinen <tpirinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:31:45 by tpirinen          #+#    #+#             */
/*   Updated: 2025/08/12 01:07:59 by tpirinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdarg.h>

# define HEX_LOWER "0123456789abcdef"
# define HEX_UPPER "0123456789ABCDEF"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 37
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

/*		Ascii		*/
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
int		ft_tolower(int c);
int		ft_toupper(int c);

/*		Memory		*/
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memset(void *s, int c, size_t n);

/*		Strings	*/
int		ft_atoi(const char *nptr);
char	*ft_itoa(int n);
char	**ft_split(char const *s, char c);
char	*ft_strchr(const char *s, int c);
void	ft_strcpy(char *dst, const char *src);
char	*ft_strdup(const char *s);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlen(const char *s);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strrchr(const char *s, int c);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);

/*		Print functions	
		In the libft project these were simple void functions but I modified
		them to return the amount of characters printed or -1 for error
		to be compatible with the ft_printf project.		*/
ssize_t	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
ssize_t	ft_putnbr_fd(int n, int fd);
ssize_t	ft_puthex_low_fd(unsigned int n, int fd);
ssize_t	ft_puthex_up_fd(unsigned int n, int fd);
ssize_t	ft_putptr_fd(void *p, int fd);
ssize_t	ft_putstr_fd(char *s, int fd);
ssize_t	ft_putunbr_fd(unsigned int n, int fd);

/*		Linked lists	*/
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

// FUNCTIONS ADDED AFTER LIBFT COMPLETETION:
/*		Errors		*/
int		ft_error_msg(char *err_msg, int err_code);

/*		Print functions	*/
int		ft_printf(const char *s, ...);
int		ft_fprintf(int fd, const char *s, ...);

/*		Strings	*/
size_t	ft_count_words(char const *s, char c);

/*		File reading	*/
char	*get_next_line(int fd);

/*		Int array */
void	ft_int_arr_copy(int *dest, int *src, int size);

#endif
