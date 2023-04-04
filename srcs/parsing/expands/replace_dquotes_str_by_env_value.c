//
// Created by bpoumeau on 4/3/23.
//

#include "../../../libft/libft.h"
#include "../../../incs/parsing_incs/minishell_parsing.h"


t_return_status	replace_dquotes_str_by_env_value(char **line_pt, char **env)
{
	char **str_arr;

	ft_striteri(*line_pt, &cpy_next_char);
	if (cut_line_on(*line_pt, &str_arr) != SUCCESS
		|| join_arr_on(str_arr, line_pt, env) != SUCCESS)
		return (FAILED_MALLOC);
	return (SUCCESS);
}

