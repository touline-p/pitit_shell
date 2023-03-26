#include "../../incs/parsing_incs/minishell_parsing.h"
#include "../../incs/parsing_incs/prototypes_parsing.h"
#include "../../incs/execution_incs/structures_execution.h"

#include "../../libft/libft.h"

t_return_status	get_lexed_str_token_lst_from_line(char *line, t_string_token **str_tok_pt)
{
	t_token			*simple_tok_lst;
	t_string_token	*str_token_lst;

	simple_tok_lst = token_lst_constructor(line);
	if (simple_tok_lst == NULL)
		return (FAILED_MALLOC);
	preserve_token_lst(simple_tok_lst);
	str_token_lst = token_lst_to_str_token(simple_tok_lst);
	split_toklst_on_meta(simple_tok_lst);
	if (simple_tok_lst == NULL)
		return (FAILED_MALLOC);
	*str_tok_pt = str_token_lst;
	return (SUCCESS);
}
