#include "../../libft/libft.h"
#include "../../incs/parsing_incs/minishell_parsing.h"

static t_return_status	_export_display(char **env);
static void				_display_unic_export(char *env_line);

typedef t_return_status (*t_export_ft)(char *arg, char ***env_pt);

t_export_ft	_get_ft_to_do(char *line, char **env);

t_return_status	export_builtin(char **args, char ***env_pt)
{
	char		**tmp;

	if (ft_str_array_len(args) == 1)
		return (ft_free_split(args), _export_display(*env_pt), SUCCESS);
	tmp = args + 1;
	while (*tmp != NULL)
	{
		if ((*_get_ft_to_do(*tmp, *env_pt))(*tmp, env_pt) != SUCCESS)
			return (free(*args), ft_free_split(tmp), FAILED_MALLOC);
		tmp++;
	}
	return (free(*args), free(args), SUCCESS);
}


void _get_rid_of_plus(char *line)
{
	if (line == NULL)
		return ;
	while (*line != '=' && *line)
	{
		if (*line == '+')
		{
			ft_memmove(line, line + 1, ft_strlen(line));
			return ;
		}
		line++;
	}
}

t_return_status replace_content_in_env_pt(char *line, char ***env_pt)
{
	return (replace_content_in_env(line, *env_pt), SUCCESS);
}

t_return_status do_nothing_t_export_ft(char *line, char ***env_pt)
{
	(void)line;
	(void)env_pt;
	return (SUCCESS);
}

t_return_status concat_content_to_line_in_env(char *line, char ***env_pt)
{
	char	*content;
	char	**env_line;
	char 	*tmp;

	content = ft_strchr(line, '=');
	*(content++) = 0;
	env_line = get_line_addr_from_key(line, *env_pt);
	tmp = *env_line;
	*env_line = ft_strjoin(*env_line, content);
	free(tmp);
	free(line);
	return (SUCCESS);
}

t_export_ft	_get_ft_to_do(char *line, char **env)
{
	char *eq;
	char *plus;

	eq = ft_strchr(line, '=');
	plus = ft_strchr(line, '+');
	_get_rid_of_plus(line);
	if (has_a_key_from_env(line, env) == false)
	{
		return (&add_str_to_env);
	}
	if (eq == NULL)
		return (&do_nothing_t_export_ft);
	if (plus == eq - 1)
		return (&concat_content_to_line_in_env);
	return (&replace_content_in_env_pt);
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

#define TST_EXPORT
#ifdef TST_EXPORT
int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;

	av = ft_str_array_dup(av);
	env = ft_str_array_dup(env);
	export_builtin(av, &env);
	ft_print_split(env);
	del_str_from_env(get_line_from_key("USER", env), &env);
	printf("\n\n\nyouhou\n\n\n");
	ft_print_split(env);
	ft_free_split(env);
}
#endif
