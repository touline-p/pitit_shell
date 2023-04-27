#include "minishell_parsing.h"
#include "../../../incs/parsing_incs/minishell_parsing.h"

void	replace_space_by_minus(unsigned int nb, char *content)
{
	(void) nb;
	if (*content == ' ')
			*content = -' ';
	content++;
}

static t_return_status	_expand_the_g_ret_val(char **pin_pt)
{
	free(*pin_pt);
	*pin_pt = ft_itoa(g_ret_val);
	if (*pin_pt == NULL)
		return (FAILURE);
	return (SUCCESS);
}

t_return_status	replace_dollar_str_by_env_value(char **pin_pt, char **env)
{
	char	*content;

	if (ft_strlen(*pin_pt) == 1)
		return (SUCCESS);
	if (ft_strcmp(*pin_pt, "?"))
		return (_expand_the_g_ret_val(pin_pt));
	content = get_env_content_from_key(*pin_pt + 1, env);
	free(*pin_pt);
	if (content == NULL)
		*pin_pt = ft_strdup("");
	else
		*pin_pt = ft_strdup(content);
	if (*pin_pt == NULL)
		return (FAILED_MALLOC);
	ft_striteri(*pin_pt, &replace_space_by_minus);
	return (SUCCESS);
}

#ifdef TEST_REPLACE_VAR

int main(int ac, char **av, char **env)
{
	(void )ac; (void)av;
	char *a = ft_strdup("$USER");
	char *b = ft_strdup("$bonjour");
	char *c = ft_strdup("$AHBAH");
	if (replace_dollar_str_by_env_value(&a, env) == SUCCESS)
		printf("a :->%s<-\n", a);
	if (replace_dollar_str_by_env_value(&b, env) == SUCCESS)
		printf("b :->%s<-\n", b);
	if (replace_dollar_str_by_env_value(&c, env) == SUCCESS)
		printf("c :->%s<-\n", c);
	free(a);
	free(b);
	free(c);
}

#endif
