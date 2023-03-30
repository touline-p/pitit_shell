#include "../../libft/libft.h"
#include "../../incs/parsing_incs/minishell_parsing.h"

static char *_get_cwd_var(void);
static t_return_status	_reconstruct_env(char ***env_pt);
static t_return_status	_increment_shlvl(char ***env_pt);

t_return_status	env_init_on(char ***env_pt)
{
	char *line_cwd;

	if (*env_pt == NULL)
		return (_reconstruct_env(env_pt));
	*env_pt = ft_str_array_dup(*env_pt);
	if (get_line_from_key("OLDPWD", *env_pt) == NULL)
		add_str_to_env("OLDPWD", env_pt);
	_increment_shlvl(env_pt);
	if (get_line_from_key("PWD", *env_pt) == NULL)
	{
		line_cwd = _get_cwd_var();
		if (line_cwd == NULL)
			return (FAILED_MALLOC);
		add_str_to_env(line_cwd);
	}
	return (SUCCESS);
}

static t_return_status	_increment_shlvl(char ***env_pt)
{
	char *line;
	char *line_to_add;
	int shlvl;

	line = get_line_from_key("SHLVL", *env_pt);
	if (line == NULL)
	{
		line_to_add = ft_strdup("SHLVL=0");
		if (add_str_to_env(line_to_add, env_pt) != SUCCESS)
			return (FAILED_MALLOC);
		return (SUCCESS);
	}
	shlvl = ft_atoi(ft_strchr(line, '=') + 1);
	line_to_add = ft_strjoin_free_sec_sf("SHLVL=", ft_itoa(shlvl + 1));
	if (line_to_add == NULL)
		return (FAILED_MALLOC);
	replace_content_in_env(line, env_pt);
	return (SUCCESS);
}

static t_return_status	_reconstruct_env(char ***env_pt)
{
	char **new_env;

	new_env = malloc(sizeof(char *) * 4);
	if (new_env == NULL)
		return (FAILED_MALLOC);
	new_env[0] = ft_strdup("OLDPWD");
	new_env[1] = _get_cwd_var();
	new_env[2] = ft_strdup("SHLVL=\"1\"");
	if (new_env[0] == NULL || new_env[1] == NULL || new_env[2] == NULL)
		return (free(new_env[0]), free(new_env[1]), free(new_env[2]), free(new_env), FAILED_MALLOC);
	*env_pt = new_env;
	return (SUCCESS);
}

static char *_get_cwd_var(void)
{
	char	*cwd;
	char	*dst;
	size_t	len;

	cwd = getcwd(NULL, 0);
	dst = malloc(ft_strlen(cwd) + 5);
	if (dst == NULL || cwd == NULL)
		return (free(cwd), free(dst), NULL);
	ft_strcpy(dst, "PWD=");
	ft_strcpy(dst + 5, cwd);
	len = ft_strlen(cwd) + 5;
	dst[len] = 0;
	free(cwd);
	return (dst);
}

#ifdef  TST_GET_CMD_VAR

int main()
{
	char *line;

	line = _get_cwd_var();
	printf("%s\n", line);
	free(line);
}

#endif