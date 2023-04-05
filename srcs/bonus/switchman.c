//
// Created by bpoumeau on 4/5/23.
//

#include "../../libft/libft.h"
#include "../../incs/parsing_incs/minishell_parsing.h"

int	ret_val;

t_return_status	split_t_string_token_on(t_string_token **string_token_pt);


t_return_status	switchman(t_string_token *token_lst)
{
	if (split_t_string_token_on(token_lst, &token_lst) != SUCCESS)
		return (FAILED_MALLOC);

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

t_return_status	split_t_string_token_on(t_string_token **string_token_pt)
{
	t_string_token	*tmp;
	t_string_token	*pin;

	tmp = malloc(sizeof(t_string_token) *(_count_block(*string_token_pt) + 1));
	if (tmp == NULL)
		return (FAILED_MALLOC);
	pin = *string_token_pt;
	*string_token_pt = tmp;
	while (*pin)
	{
		*tmp = *pin;
		while (pin->token != OR && pin->token != AND && pin->token != EOL)
			pin = pin->next;
	}
}