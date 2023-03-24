#include "../../libft/libft.h"

static t_ret_status	_export_display(char **env);
static t_ret_status	_get_key_on(char *line, char **key_pt);
static t_ret_status	_display_unic_export(char *env_line);
static t_ret_status	_get_content_on(char *line, char **key_pt);

void	modify_env(char *key, char **args, char **env);
t_ret_status	compare_and_modify_export_args(char **args, char **env);

t_ret_status	export_builtin(char **args, char ***env_pt)
{
	char **tmp;

	if (ft_str_array_len(args) == 1)
		return (ft_free_split(args), _export_display(*env_pt));
	if (compare_and_modify_export_args(args, *env_pt) == MLC_ERR)
		return (MLC_ERR);
	tmp = ft_strarray_join(*env_pt, args);
	free(args);
	if (tmp == NULL)
		return (MLC_ERR);
	free(*env_pt);
	*env_pt = tmp;
	return (SUCCESS);
}

t_ret_status	key_is_in_env(char *key, char **env, char ***env_line_pt)
{
	char	*key_env;

	while (*env)
	{
		if (_get_key_on(*env, &key_env) != SUCCESS)
			return (MLC_ERR);
		if (ft_strcmp(key, key_env) == 0)
		{
			*env_line_pt = env;
			free(key_env);
			return (SUCCESS);
		}
		free(key_env);
		env++;
	}
	return (FAILURE);
}

void	modify_env(char *key, char **args, char **env)
{
	char	**env_line_pt;

	if (key_is_in_env(key, env, &env_line_pt) == FAILURE
		|| ft_strchr(*args, '=') == NULL)
		return ;
	free(*env_line_pt);
	*env_line_pt = *args;
	*args = NULL;
}

static void	_resize_arr(char **args, size_t args_len)
{
	size_t	i;

	i = 0;
	while (i < args_len)
	{
		while (args[i] == NULL && args_len > i)
			args[i] = args[args_len--];
		i++;
	}
}

t_ret_status	compare_and_modify_export_args(char **args, char **env)
{
	char	*key;
	size_t	args_len;

	args_len = ft_str_array_len(args);
	while (*args)
	{
		if (_get_key_on(*args, &key) != SUCCESS)
			return (MLC_ERR);
		modify_env(key, args, env);
		free(key);
		args++;
	}
	//_resize_arr(args, args_len);
	return (SUCCESS);
}




static t_ret_status	_export_display(char **env)
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
}

static	t_ret_status	_display_unic_export(char *env_line)
{
	char *key;
	char *content;

	key = NULL;
	content = NULL;
	if (_get_key_on(env_line, &key) != SUCCESS
		|| _get_content_on(env_line, &content) != SUCCESS)
		return (free(key), free(content), MLC_ERR);
	if (printf("export %s", key) == -1)
		return (free(key), free(content), WRT_ERR);
	if (content != NULL)
		if (printf("=\'%s\'", content) == -1)
			return (free(key), free(content), WRT_ERR);
	if (printf("\n") != -1)
		return (free(content), free(key), WRT_ERR);
	return (free(content), free(key), SUCCESS);
}

static t_ret_status	_get_key_on(char *line, char **key_pt)
{
	size_t	idx;

	idx = ft_index_of(line, '=');
	if (idx == -1)
		return (ft_strdup_on(line, key_pt));
	return (ft_substr_on(line, 0, idx, key_pt));
}

static t_ret_status	_get_content_on(char *line, char **key_pt)
{
	size_t	idx;

	idx = ft_index_of(line, '=');
	if (idx == -1)
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
	ft_print_split(env);
}
#endif

/***
typedef struct s_process
{
	int fd_in;
	int fd_out;
	char *cmd;
	char **args;
}	t_process;
 ***/

/***
<start> <1str> <>> <2str> <3str> <<<> <4str> <5str> <end>
<start> <cmd> <>> <out_file> <argument1> <<<> <endfile> <argument2> <end>

<cmd> <arg1> <arg2> <NULL>

"cmd > outfile arg1 < infile arg2 | cmd args args"
"cmd arg1 arg2"

echo you > infile damn | cat this >> la dici

<echo> < you> <damn> <|> <cat> <this> <dici> <endl>

action 1

infile = stdin  && outfile = fd:infile;
cmd : echo -> builtin -> echo_builtin(structure, env_pt);
args : {"echo", "you", "damn", NULL};

pipe {};

action 2

infile = pipe[0]  && outfile = fd:la(open avec le flag O_append);
cmd = cat; -> pas builtin -> go path -> /bin/cat
args = {"cat", "this", "dici", NULL};
execve(cmd, args, *env_pt)
***/



