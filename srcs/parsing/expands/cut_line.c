

#include "../../incs/execution_incs/minishell_execution.h"
#include "../../incs/parsing_incs/minishell_parsing.h"

static size_t			count_indep_words(char *line);
static t_return_status 	check_allocations(char **line_arr, size_t arr_len);
static t_return_status		alloc_each_cells(char *line, char **line_arr);
static void				fill_cells(char *line, char **line_arr);

t_return_status	cut_line_on(char *line, char ***res_pt)
{
	char	**line_arr;

	*res_pt = NULL;
	printf("i count : %li\n", count_indep_words(line));
	line_arr = malloc(sizeof(char *) * count_indep_words(line));
	if (line_arr == NULL
		|| alloc_each_cells(line, line_arr) != SUCCESS)
		return (free(line), free(line_arr), FAILED_MALLOC);
	fill_cells(line, line_arr);
	*res_pt = line_arr;
	return (free(line), SUCCESS);
}

typedef bool (t_increment_ft)(char line_pt, void *arg);

bool	is_eq_to(char obj, void *to_compare)
{
	printf("\tquote mode");
	if (obj == (char)(long long)to_compare) {
		printf("it s true \n");
		return (true);
	}
	printf("it s false \n");
	return (false);
}

bool	isnotalnum(char obj, void *to_ignore)
{
	(void)to_ignore;
	printf("\texpand mode\n");
	return (ft_isalnum(obj) == false);
}

bool	is_from_base(char obj, void *base)
{
	printf("\tchar mode\n");
	return (is_from(obj, (char *)base));
}

void increment_till_true(t_increment_ft *increment_ft, void *arg, char **line_pt)
{
	(*line_pt)++;
	while (**line_pt && (*increment_ft)(**line_pt, arg) == false) {
		printf("%c", **line_pt);
		(*line_pt)++;
	}
	if (increment_ft == &is_eq_to && (**line_pt))
		(*line_pt)++;
}

static void	_increment_count_and_reset_pin(size_t *count_pt, char **line_pt)
{
	const char	a[4] = {'$', -'\'', -'"', '\0'};

	(*count_pt)++;
	if (**line_pt == -'"')
		increment_till_true(&is_eq_to, (void *)-'"', line_pt);
	else if (**line_pt == -'\'')
		increment_till_true(&is_eq_to, (void *)-'\'', line_pt);
	else if (**line_pt == '$')
		increment_till_true(&isnotalnum, NULL, line_pt);
	else
		increment_till_true(&is_from_base, (void *)a, line_pt);
}



static size_t	count_indep_words(char *line)
{
	size_t	count;

	count = 1;
	while (*line) {
		printf("%c x", *line);
		_increment_count_and_reset_pin(&count, &line);
	}
	return (count);
}

static	t_return_status 	check_allocations(char **line_arr, size_t arr_len)
{
	int	tmp;

	tmp = arr_len;
	while (arr_len--)
	{
		if (line_arr[arr_len] == NULL)
			break ;
		if (arr_len == 0)
			return (SUCCESS);
	}
	while (tmp--)
		free(line_arr[tmp]);
	return (FAILED_MALLOC);
}

static	t_return_status	alloc_each_cells(char *line, char **line_arr)
{
	size_t	arr_indx;
	size_t	word_len;

	arr_indx = 0;
	while (*line)
	{
		word_len = 0;
		while (*line && *line != '$')
		{
			word_len++;
			line++;
		}
		line_arr[arr_indx++] = malloc(word_len + 1);
		if (*(line++) == '\0')
			break ;
		word_len = 1;
		while (ft_isalnum(*(line)) || *line == '_')
		{
			line++;
			word_len++;
		}
		line_arr[arr_indx++] = malloc(word_len + 1);
	}
	line_arr[arr_indx] = NULL;
	return (check_allocations(line_arr, arr_indx));
}

static void	fill_cells(char *line, char **line_arr)
{
	char	*pin;
	int 	j;

	j = 0;
	while (*line)
	{
		j = 0;
		pin = *(line_arr);
		while (*line && *line != '$')
			pin[j++] = *(line++);
		pin[j] = '\0';
		j = 0;
		pin = *(++line_arr);
		if (*line == 0)
			break;
		pin[j++] = *(line++);
		while (ft_isalnum(*line))
			pin[j++] = *(line++);
		pin[j] = 0;
		line_arr++;
	}
}
#define TST_CUT_LINE
#ifdef TST_CUT_LINE

#include <stdio.h>

void change(char *line)
{
	while (*line)
	{
		if (is_from(*line, "'\""))
			*line = -(*line);
		line++;
	}
}

int main(int ac, char **av, char **env)
{
	(void)ac; (void)av; (void)env;

	char	*line = ft_strdup("expa\"nd qu\"i ma\'rche\' $USER ");
	char 	**line_arr;
	change(line);
	cut_line_on(line, &line_arr);
	char **tmp = line_arr;
	int i = 0;
	while (i < 5)
	{
		i++;
		printf("%d: %p, \n", i, tmp);
		tmp++;
	}
	ft_free_split(line_arr);
}

#endif