/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enums_execution.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twang <twang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 18:28:34 by wangthea          #+#    #+#             */
/*   Updated: 2023/03/22 14:49:48 by twang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUMS_EXECUTION_H
# define ENUMS_EXECUTION_H

/*---- typedef enums ---------------------------------------------------------*/

typedef enum e_token_recognition

/*----------------------------------------------------------------------------*/

enum e_token_recognition
{
    HERE_DOC,
    SIMPLE_COMMAND,
    BUILTIN
};

#endif