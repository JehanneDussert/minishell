/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_msg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdussert <jdussert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 15:11:25 by ede-banv          #+#    #+#             */
/*   Updated: 2021/01/26 12:04:08 by jdussert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	error_msg(char *bin, char *message)
{
	ft_putstr_fd("Minishell: ", 2);
	if (bin)
	{
		ft_putstr_fd(bin, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(message, 2);
}

int		ft_syntax_error(char *error, t_all *all)
{
	if (ft_strcmp(error, "pipe") == 0 || ft_strcmp(error, "quote") == 0)
		all->err = 130;
	else
		all->err = 2;
	if (ft_strcmp(error, "pipe") == 0)
		error_msg(NULL, "syntax error : double separator tokens.");
	else if (ft_strcmp(error, "sc") == 0)
		error_msg(NULL, "syntax error : double separator tokens.");
	else if (ft_strcmp(error, "ps") == 0)
		error_msg(NULL, "syntax error : pipe or semi-colon error.");
	else if (ft_strcmp(error, "chevrons") == 0)
		error_msg(NULL, "syntax error : redirection symbol syntax error.");
	else if (ft_strcmp(error, "quote") == 0)
		error_msg(NULL, "syntax error : quote error.");
	return (0);
}

int		ft_malloc_error(char *bin)
{
	error_msg(bin, "memory allocation error.");
	return (0);
}

void	ft_ambiguous_redir(char ***new, char **tmp)
{
	error_msg(*tmp, "ambiguous redirection");
	ft_free((void **)tmp);
	free_read(NULL, (*new));
}
