//
// Created by bpoumeau on 4/5/23.
//
#include "../../libft/libft.h"
#include "../../incs/parsing_incs/minishell_parsing.h"

t_return_status	split_t_string_token_on(t_string_token **string_token_pt);


void go_to_next_(t_emt token, t_string_token *tmp, t_string_token **str_tok)
{
	if (tmp == NULL)
		return ;
	if (tmp->next)
		tmp = tmp->next;
	while (tmp->token != token && tmp->token != EOL)
	{
		if (tmp->token == O_PRTSS)
			go_to_next_(C_PRTSS, tmp, &tmp);
		else
			tmp = tmp->next;
	}
	*str_tok = tmp;
}
void	display_t_emt_string(t_string_token *token);

int profondeur = 0;

void go_to_next_logical_door(t_string_token *src, t_string_token **dst)
{
	t_string_token	*and_pt;
	t_string_token	*or_pt;

	go_to_next_(AND, src, &and_pt);
	go_to_next_(OR, src, &or_pt);
	if (and_pt < or_pt)
		*dst = and_pt;
	else
		*dst = or_pt;
}

size_t	count_instructions_node(t_string_token *str_tok_lst)
{
	size_t			count;
	t_string_token	*tmp;

	count = 0;
	tmp = str_tok_lst;
	while (tmp->token != EOL)
	{
		count++;
		go_to_next_logical_door(tmp, &tmp);
	}
	return (count);
}

void fill(t_string_token **instructions_arr, t_string_token *str_tok_lst)
{
	size_t	i;

	i = 0;
	while (str_tok_lst->token != EOL)
	{
		instructions_arr[i++] = str_tok_lst;
		go_to_next_logical_door(str_tok_lst, &str_tok_lst);
	}
	instructions_arr[i] = NULL;
}

t_return_status	switchman(t_string_token *token_lst)
{
	t_string_token	**instructions_arr;

	instructions_arr = malloc(sizeof(void *) * (count_instructions_node(token_lst) + 1));
	if (instructions_arr == NULL)
		return (FAILURE);
	fill(instructions_arr, token_lst);
//	if (put_eol(instructions_arr) != SUCCESS)
//		return (FAILURE);
	return (SUCCESS);
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

//#define TST_SWITCHMAN
#ifdef TST_SWITCHMAN
int main(int ac, char **av, char **env)
{
	(void)ac; (void)av;
	t_string_token *str_tok;

	char *line;
	while (1) {
		line = readline(">");
		if (!line)
			return (0);
		add_history(line);
		get_lexed_str_token_lst_from_line(line, &str_tok, env);
		del_space_token(str_tok);
		switchman(str_tok);
		string_token_destructor(str_tok);
	}
}
#endif
