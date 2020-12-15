/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 14:11:39 by jdussert          #+#    #+#             */
/*   Updated: 2020/12/07 11:15:58 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# include "minishell.h"
# include <sys/types.h>

typedef struct	s_cmd
{
	int			pipe[2];
	char		**cmd;
	pid_t		pid;
}				t_cmd;

typedef struct	s_exit
{
	int			e;
	int			d;
}				t_exit;

typedef struct	s_lst
{
	struct s_lst	*next;
	char			*key;
	char			*content;
	int				tmp;
}				t_lst;

typedef struct	s_all
{
	t_lst		*alst;
	t_exit		*exit;
	t_cmd		*cmd;
	int			err;
	int			fd;
	int			prog;
	int			fd_copy;
}				t_all;

#endif
