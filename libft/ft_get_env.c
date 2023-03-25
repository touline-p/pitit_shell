#include "libft.h"

char *ft_get_env(char *str, char **env)
{
    while (*env)
    {
        if (ft_strncmp(str, *env, ft_strlen(str)) == 0
            && ft_strchr(*env, '=') == *env + ft_strlen(str))
            return (ft_strdup(*env + ft_strlen(str) + 1));
		env++;
    }
    return (ft_strdup(""));
}

#ifdef TST_FT_GET_ENV

# include <stdio.h>

int main(int ac, char **av, char **env)
{
	while (*av)
	{
		char	*line;
		printf("%s : ->%s<-\n", *av, line = ft_get_env(*av, env));
		av++;
		free(line);
	}
    return (0);
}
#endif