/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enums_parsing.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wangthea <wangthea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 18:28:34 by wangthea          #+#    #+#             */
/*   Updated: 2023/03/20 19:22:10 by wangthea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUMS_PARSING_H
# define ENUMS_PARSING_H

/*---- typedef enums ---------------------------------------------------------*/

typedef enum e_ret_status	t_ret_status;

/*----------------------------------------------------------------------------*/

enum e_ret_status
{
	success,
	failure,
	malloc_fail,
	write_fail
};

#endif