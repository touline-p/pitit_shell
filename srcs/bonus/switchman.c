//
// Created by bpoumeau on 4/5/23.
//

/*
#include "../../libft/libft.h"
#include "../../incs/parsing_incs/minishell_parsing.h"

int	ret_val;

t_return_status	split_t_string_token_on(t_string_token **string_token_pt);


void go_to_next_(t_emt token, t_string_token **str_tok)
{
	t_string_token	*tmp;

	tmp = *str_tok;
	while (tmp->token != token && tmp->token != EOL)
		tmp = tmp->next;
	*str_tok = tmp;
}

t_return_status	switchman(t_string_token *token_lst)
{
	while (token_lst->token != EOL)
	{
		exec(token_lst);
		if (ret_val == 0)
			go_to_next_(AND, &token_lst);
		else
			go_to_next_(OR, &token_lst);

	}
}
static size_t _count_block(t_string_token *pin)
{
	size_t	count;

	count = 1;
	while (pin->token != EOL)
	{
		if (pin->token == AND || pin->token == OR)
			count++;
		if (pin->token == O_PRTSS)
		{
			while (pin->token != C_PRTSS)
				pin = pin->next;
		}
		pin = pin->next;
	}
	return (count);
}

#define TST_SWITCHMAN
#ifdef TST_SWITCHMAN
int main(int ac, char **av, char **env)
{
	(void)ac; (void)av;
	t_string_token *str_tok;

	char *line;
	while (1) {
		line = readline(">");
		get_lexed_str_token_lst_from_line(line, &str_tok, env);
		printf("%ld\n", _count_block(str_tok));
		display_str_token(str_tok);
		string_token_destructor(str_tok);
	}
}
#endif
*/
