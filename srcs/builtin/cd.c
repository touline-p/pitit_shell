#include "../../libft/libft.h"
#include "../../incs/parsing_incs/minishell_parsing.h"

static t_return_status	_update_pwd_var(char **env);

t_return_status	cd_builtin(char **av, char ***env_pt)
{
	(void)env_pt;
	if (ft_str_array_len(av) != 2)
		return (dprintf(2, "cd: bad arguments number\n"), ft_free_split(av), SUCCESS);
//	if (ft_str_array_len(av) == 1)
//		return (_go_to_home(env_pt));

	chdir(av[1]);
	if (errno)
	{
		perror(av[1]);
		return (FAILURE);
	}
	ft_free_split(av);
	if (_update_pwd_var(*env_pt) != SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}

static t_return_status	_update_pwd_var(char **env)
{
	char	*old_pwd;
	char	*new_pwd;
	char	*tmp;

	old_pwd = ft_strjoin("OLDPWD=", get_env_content_from_key("PWD", env));
	if (old_pwd == NULL)
		return (FAILED_MALLOC);
	tmp = getcwd(NULL, 0);
	if (tmp == NULL)
		return (free(old_pwd), FAILED_MALLOC);
	new_pwd = ft_strjoin("PWD=", tmp);
	free(tmp);
	replace_content_in_env(old_pwd, env);
	replace_content_in_env(new_pwd, env);
	return (SUCCESS);
}


#ifdef TST_CD
int main(int ac, char **av, char **env)
{
	(void)ac; (void)av; (void)env;

	env = ft_str_array_dup(env);
	av = ft_str_array_dup(av);
	cd_builtin(av, &env);
	ft_free_split(env);
	return (0);
}
#endif