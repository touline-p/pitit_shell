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
//#define TST_GNL
#ifdef TST_GNL

int main(int ac, char **av)
{
	(void)ac;
	char *string;
	printf("%s\n", string = get_first_line_in_env(av + 1));
	while (string)
		printf("%s\n", string = get_next_line_in_env(string ,av + 1));

}

#endif

// #define TST_EXPORT
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

#ifdef TST_UNSET

int	main(int ac, char **av, char **env)
{
	(void)ac; (void)av; (void)env;

	env = ft_str_array_dup(env);
	av = ft_str_array_dup(av);
	unset_builtin(av, &env);
	ft_print_split(env);
	ft_free_split(env);
	return (0);
}

#endif

#ifdef TST_PWD

int	main(int ac, char **av, char **env)
{
	av = ft_str_array_dup(av);
	env = ft_str_array_dup(env);
	pwd_builtin(av, &env);
	ft_free_split(env);
	return (0);
}

#endif

#ifdef TST_ECHO

int	main(int ac, char **av, char **env)
{
	(void)ac; (void)av; (void)env;

	env = ft_str_array_dup(env);
	av = ft_str_array_dup(av);
	echo_builtin(av, &env);
	ft_free_split(env);
	return (0);
}

#endif

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

#ifdef TST_ENV

int	main(int ac, char **av, char **env)
{
	(void)ac; (void)av; (void)env;

	env = ft_str_array_dup(env);
	av = ft_str_array_dup(av);
	env_builtin(av, &env);
	ft_free_split(env);
	return (0);
}

#endif
