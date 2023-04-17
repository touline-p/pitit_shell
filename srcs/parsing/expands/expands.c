/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expands.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:22:46 by twang             #+#    #+#             */
/*   Updated: 2023/03/21 18:02:40 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/execution_incs/minishell_execution.h"
#include "../../incs/parsing_incs/minishell_parsing.h"

//static t_return_status	_expand_str_and_split_space(t_string_token **pin_pt, char **env);

t_return_status	performe_expand_on_line(char **line_pt, char **env)
{
	char **line_arr;
	char **pin;

	if (cut_line_on(*line_pt, &line_arr) != SUCCESS)
		return (0);
	pin = line_arr;
	while (pin && *pin)
	{
		if (**pin == '$' && \
		replace_dollar_str_by_env_value(pin, env) != SUCCESS)
			return (ft_free_split(line_arr), FAILED_MALLOC);
		pin++;
	}
	if (ft_join_str_arr_on(line_arr, line_pt) != SUCCESS)
		return (ft_free_split(line_arr), FAILED_MALLOC);
	ft_free_split(line_arr);
	return (SUCCESS);
}

static size_t	_count_ln(t_string_token *token_lst)
{
	size_t	count;

	count = 0;
	token_lst = token_lst->next;
	while (token_lst->token != EOL)
	{
		count += ft_strlen(token_lst->content);
		count++;
		token_lst = token_lst->next;
	}
	printf("i has a %ld ln\n", count);
	return (count);
}

char **join_token_lst(t_string_token **arg)
{
	char *tmp;
	char *ret;
	t_string_token *token_lst;

	token_lst = *arg;
	tmp = malloc(_count_ln(token_lst) + 1);
	ret = tmp;
	token_lst = token_lst->next;
	while (token_lst->token != EOL && token_lst->token != PIPE)
	{
		tmp = ft_strcpy_rn(tmp, token_lst->content);
		*(tmp++) = ' ';
		token_lst = token_lst->next;
	}
	*tmp = 0;
	*arg = token_lst;
	return (ft_split(ret, ' '));
}


//t_return_status	expand_for_args(t_string_token *token_lst, char **env, char ***args_arr)
//{
//	char *str;
//
//	cut_all_lines(token_lst);
//	join_all_lines(token_lst, env);
//	str = join_token_lst(token_lst);
//	*args_arr = ft_split(str, ' ');
//	free(str);
//	return (SUCCESS);
//}

//static t_return_status	_expand_str_and_split_space(t_string_token **pin_pt, char **env)
//{
//	t_string_token	*tmp;
//
//	tmp = *pin_pt;
//	*pin_pt = tmp->next;
//	if (performe_expand_on_line(&(tmp->content), env) != SUCCESS)
//		return (FAILED_MALLOC);
//	if (split_t_string_token_on_space(&tmp) != SUCCESS)
//		return (FAILED_MALLOC);
//	while (tmp->next)
//		tmp = tmp->next;
//
//	return (SUCCESS);
//}
//#define TST_join_lst

#ifdef TST_join_lst
int main(int ac, char **av, char **env)
{
	(void)ac; (void)av;
	t_string_token *a;
	get_lexed_str_token_lst_from_line(ft_strdup("bonjour a tous | bonjour a toi"), &a, env);
	del_space_token(a);
	display_str_token(a);
	char *tmp = join_token_lst(a);
	puts(tmp);
	char **split = ft_split(tmp, ' ');
	free(tmp);
	printf("ceci est un super split\n");
	ft_print_split(split);
	string_token_destructor(a);
}
#endif
#ifdef TST_EXPAND

int	main(int ac, char **av, char **env)
{
	(void) ac;
	(void) av;
	char *line = ft_strdup("expand qui marche $USERU $test");
	printf("origine:\n->%s<-\n", line);
	if (performe_expand_on_line(&line, env) != SUCCESS)
		return (perror("allocation"), 1);
	printf("test:\n->%s<-\n", line);
	free(line);
	printf("I am so smart!\n");
	return (0);
}

#endif