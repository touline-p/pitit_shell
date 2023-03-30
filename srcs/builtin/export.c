#include "../../libft/libft.h"
#include "../../incs/parsing_incs/minishell_parsing.h"

static t_return_status	_export_display(char **env);
static void				_display_unic_export(char *env_line);

void	modify_env(char *key, char **args, char **env);

t_return_status	export_builtin(char **args, char ***env_pt)
{
	char		**tmp;

	if (ft_str_array_len(args) == 1)
		return (ft_free_split(args), _export_display(*env_pt), SUCCESS);
	tmp = args + 1;
	while (*tmp != NULL)
	{
		if (has_a_key_from_env(*tmp, *env_pt) == true
			&& ft_strchr(*tmp, '=') == NULL)
			;
		else if (has_a_key_from_env(*tmp, *env_pt) == true)
			replace_content_in_env(*tmp, *env_pt);
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
