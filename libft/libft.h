/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:23:19 by bpoumeau          #+#    #+#             */
/*   Updated: 2023/04/04 20:13:39 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdio.h>
# include <fcntl.h>

# include <stdarg.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdint.h>

# define HEXA_LOW "0123456789abcdef"
# define HEXA_UP "0123456789ABCDEF"

# define END "\033[0m"
# define GREY "\033[1;30m"
# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define BLUE "\033[1;34m"
# define PURPLE "\033[1;35m"

# define END "\033[0m"
# define BOLD "\033[1m"
# define ITALIC "\033[3m"
# define UNDERLINE "\033[4m"
# define DEL_LINE "\033[2K\r"

# ifndef ERT
#  define ERT

typedef enum e_ret_status
{
	SUCCESS,
	FAILURE,
	FAILED_MALLOC,
	FAILED_WRITE
}	t_return_status;

# endif

typedef unsigned char			t_uchar;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

//void		put_ert(t_ert signal);
t_return_status ft_join_str_arr_on(char **str_arr, char **line_pt);
char		*ft_strdup(const char *src);
t_return_status	ft_strdup_on(const char *src, char **str_pt);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strjoin_free_sec_sf(char *s1, char *s2);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_substr(char const *s, unsigned int start, size_t len);
t_return_status	ft_substr_on(char const *s, unsigned int start, size_t len, char **line_pt);
int			ft_atoi(const char *nptr);
int			ft_atoi_has_overflown(char *str);
char		*ft_itoa(int n);
int			*ft_intarr_set(int *tab, int value, size_t size);
void		*ft_memdup(void *src, size_t ln);
void		ft_swap(int *a, int *b);
int			ft_is_overflowing(char *str);
void		*ft_free_split(char **dst);
void		ft_free_int_arr(int **int_arr);
void		ft_print_split(char **split);
char		*ft_strjoin_three(char *a, char *b, char *c);
void		*per_n_ret(char *msg);
int			is_from(char c, char *base);
int			str_is_made_of(char *str, char *charset);
t_uchar		*ft_ustrdup(unsigned char *str);
int			ft_min(int a, int b);
int			ft_max(int a, int b);
char		*ft_get_env(char *key, char **env);
size_t 		ft_str_array_len(char **str_arr);
char 		**ft_str_array_dup(char **str_arr);
char 		**ft_strarray_join(char **first, char **second);

//t_ert		ft_atoi_on(const char *str, int *int_pt);
int	ft_dprintf(int fd, const char *str, ...);

void			ft_swap(int *a, int *b);
int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isascii(int c);
bool			ft_str_is_ascii(char *str);
int				ft_isdigit(int c);
int				ft_isprint(int c);
int				ft_issign(int c);
void			ft_bzero(void *dst, size_t n);
void			*ft_memchr(void *buf, int c, size_t length);
int				ft_memcmp(const void *s1, const void *s2, size_t lenght);
void			*ft_memcpy(void *dst, const void *src, size_t lenght);
void			*ft_memmove(void *dst, const void *src, size_t length);
void			*ft_memset(void *dst, int c, size_t length);
void			*ft_memcset(void *dst, int c, int till, size_t max_length);
void			ft_putendl_fd(char *c, int fd);
char			*ft_strchr(const char *s, int c);
size_t			ft_index_of(const char *s, int c);
void			ft_striteri(char *s, void (*f)(unsigned int, char*));
size_t			ft_strlcat(char *dst, const char *src, size_t size);
size_t			ft_strlcpy(char *dst, const char *src, size_t size);
size_t			ft_strlen(const char *s);
size_t			ft_ustrlen(unsigned char *s);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int				ft_strncmp(char *s1, char *s2, unsigned int n);
int				heredoc_strncmp(const char *s1, const char *s2, size_t n);
int				ft_strcmp(char *s1, char *s2);
int				ft_ustrcmp(t_uchar *s1, t_uchar *s2);
char			*ft_strrchr(const char *s, int c);
int				ft_tolower(int c);
int				ft_toupper(int c);
void			*ft_calloc(size_t n, size_t size);
char			**ft_split(char const *s, char c);
char			*ft_strdup(const char *src);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s1, char const *set);
char			*ft_substr(char const *s, unsigned int start, size_t len);
int				ft_atoi(const char *nptr);
int				ft_atoi_has_overflown(char *str);
char			*ft_itoa(int n);
int				*ft_intarr_set(int *tab, int value, size_t size);
void			*ft_memdup(void *src, size_t ln);
void			ft_swap(int *a, int *b);
int				ft_is_overflowing(char *str);
void			*ft_free_split(char **dst);
void			ft_free_int_arr(int **int_arr);
void			ft_print_split(char **split);
char			*ft_strjoin_three(char *a, char *b, char *c);
void			*per_n_ret(char *msg);
int				is_from(char c, char *base);
int				str_is_made_of(char *str, char *charset);
int				ft_min(int a, int b);
int				ft_max(int a, int b);
char			*ft_get_env(char *key, char **env);
t_uchar			*ft_ustrdup(unsigned char *str);

//t_ert			ft_atoi_on(const char *str, int *int_pt);

/** Pipes utils **/

void			close_pipe_arr(int **pipe_arr);
void			ft_print_pipe_arr(int **pipe_arr);

/**	INT_ARR_UTILS **/
size_t			int_arr_ret_min_indx(int *int_arr, size_t ln);
void			ft_int_array_set(int *tab, int value, size_t size);

/** STR_CPY **/

char			*ft_strcpy_rn(char *dst, char *src);
char			*ft_strcpy(char *dst, char *src);

/** LST **/

void			ft_lstclean(t_list *head, void (*del)(void *));
//t_ert			ft_lstnew_on(void *content, t_list **list_ptr);
//t_ert			ft_lstnew_onsf(void *content, t_list **list_ptr);

/**	LSTSTR **/

//t_ert			ft_lststr_to_str(t_list *lst, char **str);
size_t			ft_lststrlen(t_list *lst);

/** GNL **/

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

//t_ert			ft_gnl_on(int fd, char **line_pt);

/**---- utils ---- **/

int				open_file(const char *av);

/**---- printf ---- dprintf ---- **/

int				ft_printf(const char *str, ...);
int				ft_dprintf(int fd, const char *str, ...);
size_t			ft_putchar_fd(int c, int fd);
size_t			ft_putstr_fd(char *s, int fd);
size_t			ft_putnbr_base(unsigned long nbr, char *base, int fd);
size_t			ft_putnbr_unsigned_fd(unsigned int n, int fd);
size_t			ft_putnbr_fd(int n, int fd);

char	*ft_strnstr(const char *haystack, const char *needle, size_t len);

#endif
