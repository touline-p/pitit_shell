#include "../../../libft/libft.h"
#include "../../../incs/parsing_incs/minishell_parsing.h"

bool	is_a_key_from_env(char *key, char **env)
{
	if (get_line_from_key(key, env) != NULL)
		return (true);
	return (false);
}

char    *get_line_from_key(char *key, char **env)
{
	char    **pin;
	size_t  ln;

	pin = env;
	ln = ft_strlen(key);
	while (*pin)
	{
		if (ft_strncmp(*pin, key, ln) == 0 \
			&& ((*pin)[ln] == 0 || (*pin)[ln] == '='))
			return (*pin);
		pin++;
	}
	return (*pin);
}

char 	**get_line_addr_from_key(char *key, char **env)
{
	char    **pin;
	size_t  ln;

	pin = env;
	ln = ft_strlen(key);
	while (*pin)
	{
		if (ft_strncmp(*pin, key, ln) == 0 \
			&& ((*pin)[ln] == 0 || (*pin)[ln] == '='))
			return (pin);
		pin++;
	}
	return (pin);
}

char    *get_env_content_from_key(char *key, char **env)
{
	char	*line;
	char	*ret_val;

	line = get_line_from_key(key, env);
	ret_val = ft_strchr(line, '=');
	if (ret_val)
		return (ret_val + 1);
	return (NULL);
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

void	replace_content_in_env(char *line, char **env)
{
	char **line_to_replace;

	*ft_strchr(line, '=') = 0;
	line_to_replace = get_line_addr_from_key(line, env);
	*ft_strchr(line, 0) = '=';
	free(*line_to_replace);
	*line_to_replace = line;
}

#ifdef TST_ENV_UTILS

int	main(int ac, char **av, char **env)
{
	(void)av; (void)ac; (void)env;

	printf("$USER is a key from env %i\n", is_a_key_from_env("USER", env));
	printf("$USERY is a key from env %i\n", is_a_key_from_env("USERY", env));
	printf("$USE is a key from env %i\n", is_a_key_from_env("USE", env));
	printf("$USER content : %s\n", get_env_content_from_key("USER", env));
	printf("$USER line : %s\n", get_line_from_key("USER", env));
	printf("$USERY line : %p\n", get_line_from_key("USERY", env));
	printf("$USE line : %p\n", get_line_from_key("USE", env));
	return (0);
}
#endif
