/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes_parsing.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wangthea <wangthea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 18:38:27 by wangthea          #+#    #+#             */
/*   Updated: 2023/03/20 19:20:56 by wangthea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPES_PARSING_H
# define PROTOTYPES_PARSING_H

# include "enums_parsing.h"
# include "structures_parsing.h"

/*----- expands --------------------------------------------------------------*/

//cut_line.c
t_ret_status	cut_line_on(char *line, char ***res_pt);

//expands.c
t_ret_status	performe_expand_on_line(char **line_pt, char **env);

//replace_dollar_str_by_env_value.c
t_ret_status	replace_dollar_str_by_env_value(char **pin_pt, char **env);

/*----- expands --------------------------------------------------------------*/

#endif