#include "../../libft/libft.h"
#include "../../incs/parsing_incs/minishell_parsing.h"

static t_return_status	_export_display(char **env);
static t_return_status	_get_key_on(char *line, char **key_pt);
static void	_display_unic_export(char *env_line);
static t_return_status	_get_content_on(char *line, char **key_pt);

void	modify_env(char *key, char **args, char **env);

void		replace_content(char *line, char **env);

void	replace_content(char *line, char **env)
{
	size_t	equal_idx;

	equal_idx = ft_index_of(line, '=');
	if (equal_idx == (size_t)-1)
		equal_idx = ft_strlen(line);
	while (*env)
	{
		if (ft_strncmp(line, *env, equal_idx) == 0 && ((*env)[equal_idx] == 0 || (*env)[equal_idx] == '='))
		{
			free(*env);
			*env = line;
			break;
		}
		env++;
	}
}
	

t_return_status	export_builtin(char **args, char ***env_pt)
{
	char		**tmp;

	if (ft_str_array_len(args) == 1)
		return (ft_free_split(args), _export_display(*env_pt), SUCCESS);
	tmp = args + 1;
	while (*tmp != NULL)
	{
		if (is_a_key_from_env(*tmp, *env_pt) == true && ft_strchr(*tmp, '=') != NULL)
			replace_content(*tmp, *env_pt);
		else
		{
			if (add_str_to_env(*tmp, env_pt) != SUCCESS)
				return (free(*args), free(args), FAILED_MALLOC);
		}
		tmp++;
	}
	return (free(*args), free(args), SUCCESS);
}


static t_return_status	_export_display(char **env)
{
	char *line;

	line = get_first_line_in_env(env);
	while (line != NULL && (line[0] == '_' && line[1] == '=') == false)
	{
		_display_unic_export(line);
		line = get_next_line_in_env(line, env);
	}
	return (SUCCESS);
}

static void	_display_unic_export(char *env_line)
{
	char	*content;

	content = ft_strchr(env_line, '=');
	if (content == NULL)
	{
		printf("declare -x %s\n", env_line);
		return ;
	}
	*(content++) = 0;
	printf("declare -x %s=\"%s\"\n", env_line, content);
	*(--content) = '=';
}

static t_return_status	_get_key_on(char *line, char **key_pt)
{
	size_t	idx;

	idx = ft_index_of(line, '=');
	if (idx == (size_t)-1)
		return (ft_strdup_on(line, key_pt));
	return (ft_substr_on(line, 0, idx, key_pt));
}

static t_return_status	_get_content_on(char *line, char **key_pt)
{
	size_t	idx;

	idx = ft_index_of(line, '=');
	if (idx == (size_t)-1)
	{	
		*key_pt = NULL;
		return (SUCCESS);
	}
	return (ft_substr_on(line, idx + 1, ft_strlen(line + idx + 1), key_pt));
}

#ifdef TST_EXPORT
int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;

	av = ft_str_array_dup(av);
	env = ft_str_array_dup(env);
	export_builtin(av, &env);
	ft_free_split(env);
}
#endif
