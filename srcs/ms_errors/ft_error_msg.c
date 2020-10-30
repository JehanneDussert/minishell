/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_msg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-banv <ede-banv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 15:11:25 by ede-banv          #+#    #+#             */
/*   Updated: 2020/10/26 12:37:19 by ede-banv         ###   ########.fr       */
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
	if (ft_strcmp(error, "double") == 0)
		error_msg(NULL, "syntax error : double separator tokens.");
	else if (ft_strcmp(error, "ps") == 0)
		error_msg(NULL, "syntax error : pipe or semi-colon error.");
	else if (ft_strcmp(error, "chevrons") == 0)
		error_msg(NULL, "syntax error : redirection symbol syntax error.");
	else if (ft_strcmp(error, "quote") == 0)
		error_msg(NULL, "syntax error : quote error.");
	all->err = 258;
	return (0);
}

int		ft_malloc_error(char *bin)
{
	error_msg(bin, "memory allocation error.");
	return (0);
}
