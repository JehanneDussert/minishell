/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 14:21:15 by jehannedu         #+#    #+#             */
/*   Updated: 2020/12/07 16:25:39 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// ERREUR : fichier.txt < grep i : doit dire "grep : no such file or directory"
// pour l'instant dit "grep : no such..." ET "fichier.txt : no such..."
// SPECIFIC case not fixed : echo hello | cat -e <> file.txt : should create file.txt and that's all
// US : create file.txt + echo hello$
// SPECIFIC case fixed : echo hello <> file.txt : create file.txt + echo hello

void	ft_redir_plus(char **comd, t_all *all, int *i)
{
	char	*tmp;
	int		j;

	j = 0;
	tmp = ft_strtrim(&comd[0][*i], " ");
	if (tmp[j] == '>' && tmp[j + 1] == '>')
	{
		while (is_charset(tmp[j], "> "))
			j++;
		if ((all->fd = open(&tmp[j], O_WRONLY)) >= 0)
			all->fd = open(&tmp[j], O_WRONLY | O_APPEND, S_IRWXU);
	}
	else if (tmp[j] == '>')
	{
		while (is_charset(tmp[j], "> "))
			j++;
		all->fd = open(&tmp[j], O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
	}
	ft_free((void **)&tmp);
	all->fd_copy = dup(1);
	dup2(all->fd, 1);
	close(all->fd);
	(*i) += j;
}

int		ft_redir_less(char **comd, t_all *all, int *i)
{
	// prbl
	(*i)++;
	while (comd[0][*i] == ' ')
		(*i)++;
	if ((all->fd = open(&comd[0][*i], O_WRONLY)) < 0)
		return (0);
	printf("this is fd :%d\n", all->fd);
	all->fd_copy = dup(0);
	dup2(all->fd, 0);
	close(all->fd);
	return (1);
}

int		ft_reverse(char **comd, int *i)
{
	if (comd[0][*i] == '<' && comd[0][(*i) + 1] == '>')
		(*i) += 2;
	while (comd[0][*i] == ' ')
		(*i)++;
	if ((open(&comd[0][*i], O_CREAT | O_WRONLY)) < 0)
		return (0);
	return (1);
}

void	ft_redirections(char **comd, t_all *all)
{
	int	i;

	i = 0;
	all->fd = 1;
	while (comd[0][i])
	{
		if (comd[0][i] == '<' && comd[0][i + 1] == '>' && !ft_reverse(comd, &i))
			return ;
		else if (is_charset(comd[0][i], ">"))
			ft_redir_plus(comd, all, &i);
		else if (comd[0][i] == '<' && (!ft_redir_less(comd, all, &i)))
			return ; // i should put an error msg if the file does not exist, i think it's gonna be easy
		i++;
	}
	comd[0] = ft_return_new_comd(comd);
}

void	ft_check_redirection(char **comm, t_all *all)
{
	int	i;

	i = 0;
	while (comm[0][i])
	{
		if (comm[0] && is_charset(comm[0][i], "><"))
		{
			ft_redirections(comm, all);
			break ;
		}
		else
			i++;
	}
}
