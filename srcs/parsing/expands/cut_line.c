
#include "minishell_parsing.h"

static size_t			count_indep_words(char *line);
static t_ret_status 	check_allocations(char **line_arr, size_t arr_len);
static t_ret_status		alloc_each_cells(char *line, char **line_arr);
static void				fill_cells(char *line, char **line_arr);

t_ret_status	cut_line_on(char *line, char ***res_pt)
{
	char	**line_arr;

	*res_pt = NULL;
	line_arr = malloc(sizeof(char *) * count_indep_words(line));
	if (line_arr == NULL
		|| alloc_each_cells(line, line_arr) != success)
		return (free(line), free(line_arr), failed_malloc);
	fill_cells(line, line_arr);
	*res_pt = line_arr;
	return (free(line), success);
}


static size_t	count_indep_words(char *line)
{
	size_t	count;

	count = 1;
	while (*line)
	{
		count++;
		while (*line && *line != '$')
			line++;
		if (*line)
		{
			count++;
			line++;
		}
		while (*line && ft_isalnum(*line))
			line++;
	}
	return (count);
}

static	t_ret_status 	check_allocations(char **line_arr, size_t arr_len)
{
	int	tmp;

	tmp = arr_len;
	while (arr_len--)
	{
		if (line_arr[arr_len] == NULL)
			break ;
		if (arr_len == 0)
			return (success);
	}
	while (tmp--)
		free(line_arr[tmp]);
	return (failed_malloc);
}

static	t_ret_status	alloc_each_cells(char *line, char **line_arr)
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

#ifdef TST_CUT_LINE

#include <stdio.h>

int main(int ac, char **av, char **env)
{
	(void)ac; (void)av; (void)env;

	char	*line = ft_strdup("expand qui marche $USER");
	char 	**line_arr;
	cut_line_on(line, &line_arr);
	char **tmp = line_arr;
	int i = 0;
	while (tmp && *tmp)
	{
		i++;
		printf("%d, %s\n", i, *tmp);
		tmp++;
	}
	ft_free_split(line_arr);
}

#endif
