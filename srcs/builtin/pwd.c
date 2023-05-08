/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoumeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 22:58:42 by bpoumeau          #+#    #+#             */
/*   Updated: 2023/04/26 22:58:43 by bpoumeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../incs/parsing_incs/minishell_parsing.h"

t_return_status	pwd_builtin(char **args, char ***env_pt)
{
	char	*pwd;

	(void)env_pt;
	if (ft_str_array_len(args) > 1)
		return (dprintf(2, "pwd: too many arguments\n"), \
						ft_free_split(args), FAILURE);
	ft_free_split(args);
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return (dprintf(2, "Bro j'ai pas trouve dsl, tu es perdu :(\n"), \
						FAILURE);
	printf("%s\n", pwd);
	free(pwd);
	ft_free_split(*env_pt);
	return (SUCCESS);
}
