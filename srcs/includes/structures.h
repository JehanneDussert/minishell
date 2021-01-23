/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdussert <jdussert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 14:11:39 by jdussert          #+#    #+#             */
/*   Updated: 2021/01/19 10:12:50 by jdussert         ###   ########.fr       */
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
	int			copy_stdout;
	int			copy_stdin;
	int			cmd_len;
}				t_all;

typedef struct	s_copy
{
	int			j;
	int			i;
	int			s;
	int			d;
}				t_copy;

#endif
