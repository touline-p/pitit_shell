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
