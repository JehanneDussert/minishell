/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 17:31:39 by marvin            #+#    #+#             */
/*   Updated: 2020/10/06 17:31:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include "minishell.h"
# include <sys/types.h>

typedef struct  s_cmd
{
    int     pipe[2];
    char    **cmd;
    pid_t   pid;
}               t_cmd;

typedef struct  s_exit
{
    int e;
    int d;
}               t_exit;

#endif