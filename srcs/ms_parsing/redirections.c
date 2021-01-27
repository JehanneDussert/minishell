/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdussert <jdussert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 14:21:15 by jehannedu         #+#    #+#             */
/*   Updated: 2021/01/27 14:54:30 by jdussert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_redir_plus(char **comd, t_all *all, int *i)
{
	char	*tmp;
	char	*file;
	int		j;

	j = 0;
	tmp = ft_strtrim(&comd[0][*i], " ");
	if (tmp[j] == '>' && tmp[j + 1] == '>')
	{
		if (all->redir == 1)
			ft_redirection_out(all);
		ft_create_file(tmp, &file, &j);
		all->fd = open(file, O_RDWR | O_APPEND | O_CREAT, 0644);
	}
	else if (tmp[j] == '>')
	{
		if (all->redir == 1)
			ft_redirection_out(all);
		ft_create_file(tmp, &file, &j);
		all->fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	}
	all->redir = 1;
	ft_free((void **)&tmp);
	ft_free((void **)&file);
	all->copy_stdout = dup(STDOUT);
	dup2(all->fd, STDOUT);
	close(all->fd);
	(*i) += j;
}

int		ft_redir_less(char **comd, t_all *all, int *i)
{
	char *file;

	file = ft_create_file(comd[0], &file, i);
	while (comd[0][*i] == ' ')
		(*i)++;
	if (all->redir == 1)
		ft_redirection_out(all);
	if ((all->fd = open(file, O_RDONLY)) < 0)
	{
		if (all->redir == 1)
			ft_redirection_out(all);
		error_msg(file, "No such file or directory");
		all->err = 1;
		return (0);
	}
	ft_free((void **)&file);
	all->copy_stdin = dup(STDIN);
	dup2(all->fd, STDIN);
	close(all->fd);
	all->redir = 1;
	return (1);
}

int		ft_reverse(char **comd, int *i, t_all *all)
{
	char	*tmp;
	int		k;

	tmp = ft_strtrim(&comd[0][*i], " ");
	k = 0;
	if (tmp[k] == '<' && tmp[k + 1] == '>')
		k += 2;
	while (tmp[k] == ' ')
		k++;
	if (all->redir == 1)
		ft_redirection_out(all);
	if ((open(&tmp[k], O_CREAT | O_WRONLY, 0644)) >= 0)
	{
		ft_free((void **)&tmp);
		return (0);
	}
	ft_free((void **)&tmp);
	(*i) += k;
	all->redir = 1;
	return (1);
}

int		ft_redirections(char **comd, t_all *all, int j, char *charset)
{
	int	i;

	i = 0;
	all->fd = 1;
	while (comd[0][i])
	{
		if (comd[0][i] == '<' && comd[0][i + 1] == '>')
		{
			ft_reverse(comd, &i, all);
			if (j > 0)
			{
				ft_free((void **)&comd[0]);
				return (0);
			}
			break ;
		}
		else if (is_charset(comd[0][i], ">"))
			ft_redir_plus(comd, all, &i);
		else if (comd[0][i] == '<' && (!ft_redir_less(comd, all, &i)))
			return (0);
		i++;
	}
	comd[0] = ft_return_new_comd(comd, charset);
	return (1);
}

int		ft_check_redirection(char **comm, t_all *all, char *charset)
{
	int	i;
	int	j;

	j = 0;
	while (comm[j])
	{
		i = 0;
		while (comm[j][i])
		{
			if (comm[j] && is_charset(comm[j][i], "><"))
			{
				if (!ft_redirections(&comm[j], all, j, charset))
					return (0);
				break ;
			}
			else
				i++;
		}
		j++;
	}
	return (1);
}
