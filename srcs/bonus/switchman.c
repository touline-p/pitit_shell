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

t_return_status fill(t_string_token **instructions_arr, t_string_token *str_tok_lst)
{
	size_t			i;
	t_string_token	*next;

	i = 0;
	while (str_tok_lst->token != EOL)
	{
		instructions_arr[i++] = str_tok_lst;
		go_to_next_logical_door(str_tok_lst, &next);
		while (str_tok_lst->next != next)
			str_tok_lst = str_tok_lst->next;
		if (str_tok_lst->next->token != EOL)
		{
			str_tok_lst->next = string_token_creator();
			str_tok_lst->next->token = EOL;
			str_tok_lst->next->next = NULL;
		}
		str_tok_lst = next;
	}
	instructions_arr[i] = NULL;
	return (SUCCESS);
}

int _get_next_index(int last, t_string_token **instructions_arr)
{
	t_emt to_search;

	to_search = AND;
	if (last == -1)
		return (0);
	if (g_ret_val != 0)
		to_search = OR;
	while (instructions_arr[last] && instructions_arr[last]->token != to_search)
		string_token_destructor(instructions_arr[last++]);
	if (instructions_arr[last])
		return (last);
	return (-1);
}

t_return_status	launch_instructions_arr(t_data *data, t_string_token **instructions_arr, char ***env)
{
	t_string_token	*actual;

	data->index = 0;
	while (data->index != -1)
	{
		actual = instructions_arr[data->index];
		execution(data, actual, env);
		data->index = _get_next_index(++data->index, instructions_arr);
	}
	free(instructions_arr);
	return (SUCCESS);
}

t_return_status	switchman(t_data *data, t_string_token *token_lst, char ***env_pt)
{

	data->instructions_arr = malloc(sizeof(t_string_token *) * (count_instructions_node(token_lst) + 1));
	if (data->instructions_arr == NULL)
		return (FAILURE);
	fill(data->instructions_arr, token_lst);
	launch_instructions_arr(data, data->instructions_arr, env_pt);
	return (SUCCESS);
}

//static size_t _count_block(t_string_token *pin)
//{
//	size_t	count;
//
//	count = 1;
//	while (pin->token != EOL)
//	{
//		if (pin->token == AND || pin->token == OR)
//			count++;
//		if (pin->token == O_PRTSS)
//		{
//			while (pin->token != C_PRTSS)
//				pin = pin->next;
//		}
//		pin = pin->next;
//	}
//	return (count);
//}

//#define TST_SWITCHMAN
#ifdef TST_SWITCHMAN
int main(int ac, char **av, char **env)
{
	(void)ac; (void)av;
	t_string_token *str_tok;
	t_data	data;

	data.prompt = NULL;
	env = ft_str_array_dup(env);
	char *line;
	while (1) {
		line = readline(">");
		if (!line)
			return (0);
		add_history(line);
		get_lexed_str_token_lst_from_line(line, &str_tok, env);
		del_space_token(str_tok);
		switchman(&data, str_tok, &env);
	}
}
#endif
