

#include "../../incs/execution_incs/minishell_execution.h"
#include "../../incs/parsing_incs/minishell_parsing.h"

static size_t			count_indep_words(char *line);
static t_return_status	check_allocations(char **line_arr, size_t arr_len);
static t_return_status	alloc_each_cells(char *line, char **line_arr);

t_return_status	cut_line_on(char *line, char ***res_pt)
{
	char	**line_arr;

	*res_pt = NULL;
	line_arr = malloc(sizeof(char *) * (count_indep_words(line) + 1));
	if (line_arr == NULL
		|| alloc_each_cells(line, line_arr) != SUCCESS)
		return (free(line), free(line_arr), FAILED_MALLOC);
	*res_pt = line_arr;
	return (free(line), SUCCESS);
}

typedef bool (*t_increment_ft)(char line_pt, void *arg);

bool	is_eq_to(char obj, void *to_compare)
{
	if (obj == (char)(long long)to_compare)
		return (true);
	return (false);
}

bool	isnotalnum(char obj, void *to_ignore)
{
	(void)to_ignore;
	return (ft_isalnum(obj) == false);
}

bool	is_from_base(char obj, void *base)
{
	return (is_from(obj, (char *)base));
}

void	increment_till_true(t_increment_ft increment_ft, \
								void *arg, char **line_pt)
{
	(*line_pt)++;
	while (**line_pt && (*increment_ft)(**line_pt, arg) == false)
		(*line_pt)++;
	if (increment_ft == &is_eq_to && (**line_pt))
		(*line_pt)++;
}

static void	_increment_count_and_reset_pin(size_t *count_pt, char **line_pt)
{
	const char	char_arr[4] = {'$', - '\'', - '"', '\0'};

	(*count_pt)++;
	if (**line_pt == - '"')
		increment_till_true(&is_eq_to, (void *)- '"', line_pt);
	else if (**line_pt == '$' && *(*line_pt + 1) == '?')
		*line_pt += 2;
	else if (**line_pt == - '\'')
		increment_till_true(&is_eq_to, (void *)- '\'', line_pt);
	else if (**line_pt == '$')
		increment_till_true(&isnotalnum, NULL, line_pt);
	else
		increment_till_true(&is_from_base, (void *)char_arr, line_pt);
}

static size_t	count_indep_words(char *line)
{
	size_t	count;

	count = 1;
	while (*line)
		_increment_count_and_reset_pin(&count, &line);
	return (count);
}

static t_return_status	check_allocations(char **line_arr, size_t arr_len)
{
	int	tmp;

	tmp = arr_len;
	if (arr_len == 0)
		return (SUCCESS);
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

void	increment_ln_reset_pin(t_increment_ft incr_ft, \
							size_t *ln_pt, char **line_pt, void *arg)
{
	if (ft_isalnum(**line_pt) != true)
	{
		(*line_pt)++;
		(*ln_pt)++;
	}
	while (**line_pt && (*incr_ft)(**line_pt, arg) == false)
	{
		(*line_pt)++;
		(*ln_pt)++;
	}
	if (incr_ft == &is_eq_to)
	{
		(*line_pt)++;
		(*ln_pt)++;
	}
}

size_t	count_word_ln_reset_pin(char **line_pt)
{
	const char	char_arr[4] = {'$', - '\'', - '"', '\0'};
	size_t		ln;

	ln = 0;
	if (**line_pt == - '"')
		increment_ln_reset_pin(&is_eq_to, &ln, line_pt, (void *)- '"');
	else if (**line_pt == '$' && *(*line_pt + 1) == '?')
	{
		*line_pt += 2;
		ln = 2;
	}
	else if (**line_pt == - '\'')
		increment_ln_reset_pin(&is_eq_to, &ln, line_pt, (void *)- '\'');
	else if (**line_pt == '$')
		increment_ln_reset_pin(&isnotalnum, &ln, line_pt, NULL);
	else
		increment_ln_reset_pin(&is_from_base, &ln, line_pt, (void *)char_arr);
	return (ln);
}

static	t_return_status	alloc_each_cells(char *line, char **line_arr)
{
	size_t	arr_indx;
	size_t	count;
	char	*tmp;

	*line_arr = ft_strdup("");
	arr_indx = 1;
	while (*line)
	{
		tmp = line;
		count = count_word_ln_reset_pin(&line);
		line_arr[arr_indx++] = ft_substr(tmp, 0, count);
	}
	line_arr[arr_indx] = NULL;
	return (check_allocations(line_arr, arr_indx));
}

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

	char	*line = ft_strdup("expand\"qui\" \'marche\'$USER ");
	char 	**line_arr;
	change(line);
	cut_line_on(line, &line_arr);
	char **tmp = line_arr;
	int i = 0;
	while (*tmp)
	{
		i++;
		printf("%d: ->%s<-, \n", i, *tmp);
		tmp++;
	}
	ft_free_split(line_arr);
}

#endif