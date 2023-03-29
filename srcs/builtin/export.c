#include "../../libft/libft.h"
#include <stddef.h>

static t_return_status	_export_display(char **env);
static t_return_status	_get_key_on(char *line, char **key_pt);
static t_return_status	_display_unic_export(char *env_line);
static t_return_status	_get_content_on(char *line, char **key_pt);

t_return_status	add_str_to_env(char *line, char ***env_pt);
void	modify_env(char *key, char **args, char **env);
t_return_status	compare_and_modify_export_args(char **args, char **env);

t_return_status	key_is_in_env(char *line, char **env);
t_return_status	arg_has_content(char *line);
void		replace_content(char *line, char **env);

t_return_status	key_is_in_env(char *line, char **env)
{
	size_t	i;

	while (*env)
	{
		i = 0;
		while (line[i] == (*env)[i] && line[i] && (*env)[i] && line[i] != '=' && (*env)[i] != '=')
			i++;
		if ((line[i] == '=' || line[i] == 0) && ((*env)[i] == '=' && (*env)[i]))
			return (SUCCESS);
		env++;
	}
	return (FAILURE);
}

t_return_status	arg_has_content(char *line)
{
	if (ft_strchr(line, '=') != NULL)
		return (SUCCESS);
	return (FAILURE);
}

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
		return (ft_free_split(args), _export_display(*env_pt));
	tmp = args + 1;
	while (*tmp)
	{
		if (key_is_in_env(*tmp, *env_pt) == SUCCESS && arg_has_content(*tmp) == SUCCESS)
			replace_content(*tmp, *env_pt);
		else
		{
			printf("i was here\n");
			if (add_str_to_env(*tmp, env_pt) != SUCCESS)
				return (FAILED_MALLOC);
		}
		tmp++;
	}
	free(*args);
	free(args);
	return (SUCCESS);
}

t_return_status	add_str_to_env(char *line, char ***env_pt)
{
	char	**new_env;
	char	**env;
	size_t	i;

	new_env = (char **)malloc(sizeof(char *) * (ft_str_array_len(*env_pt) + 2));
	if (new_env == NULL)
		return (FAILED_MALLOC);
	env = *env_pt;
	i = 0;
	while (env[i])
	{
		new_env[i] = env[i];
		i++;
	}
	new_env[i++] = line;
	new_env[i++] = NULL;
	free(env);
	*env_pt = new_env;
	return (SUCCESS);
}


static t_return_status	_export_display(char **env)
{
	char	**env_dup;
	size_t	i;

	env_dup = ft_str_array_dup(env);
	if (env_dup == NULL)
		return (FAILURE);
	i = 0;
	while (env[i] != NULL)
		_display_unic_export(env[i++]);
	ft_free_split(env_dup);
	return (SUCCESS);
}

static	t_return_status	_display_unic_export(char *env_line)
{
	char *key;
	char *content;

	key = NULL;
	content = NULL;
	if (_get_key_on(env_line, &key) != SUCCESS
		|| _get_content_on(env_line, &content) != SUCCESS)
		return (free(key), free(content), FAILED_MALLOC);
	if (printf("export %s", key) == -1)
		return (free(key), free(content), FAILED_WRITE);
	if (content != NULL)
		if (printf("=\'%s\'", content) == -1)
			return (free(key), free(content), FAILED_WRITE);
	if (printf("\n") != -1)
		return (free(content), free(key), FAILED_WRITE);
	return (free(content), free(key), SUCCESS);
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
	ft_print_split(env);
	ft_free_split(env);
}
#endif
