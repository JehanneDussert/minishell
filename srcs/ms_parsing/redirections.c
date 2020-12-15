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

void	ft_redir_plus(char **comd, t_all *all, int *i)
{
	char	*tmp;
	char	*file;
	int		j;

	j = 0;
	tmp = ft_strtrim(&comd[0][*i], " ");
	if (tmp[j] == '>' && tmp[j + 1] == '>')
	{
		ft_create_file(tmp, &file);
		all->fd = open(file, O_WRONLY | O_APPEND, S_IRWXU);
		ft_putnbr_fd(all->fd, 2);
	}
	else if (tmp[j] == '>')
	{
		ft_create_file(tmp, &file);
		all->fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
	}
	ft_free((void **)&tmp);
	ft_free((void **)&file);
	all->fd_copy = dup(1);
	dup2(all->fd, 1);
	close(all->fd);
	(*i) += j;
}

int		ft_redir_less(char **comd, t_all *all, int *i)
{
	// prbl with grep
	(*i)++;
	while (comd[0][*i] == ' ')
		(*i)++;
	if ((all->fd = open(&comd[0][*i], O_WRONLY)) < 0)
		return (0);
	all->fd_copy = dup(0);
	dup2(all->fd, 0);
	close(all->fd);
	return (1);
}

int		ft_reverse(char **comd, int *i)
{
	char	*tmp;
	int		k;

	tmp = ft_strtrim(&comd[0][*i], " ");
	k = 0;
	if (tmp[k] == '<' && tmp[k + 1] == '>')
		k += 2;
	while (tmp[k] == ' ')
		k++;
	if ((open(&tmp[k], O_CREAT | O_WRONLY, S_IRWXU)) >= 0)
	{
		ft_free((void **)&tmp);
		return (0);
	}
	ft_free((void **)&tmp);
	(*i) += k;
	return (1);
}

int		ft_redirections(char **comd, t_all *all, int j)
{
	int	i;

	i = 0;
	all->fd = 1;
	while (comd[0][i])
	{
		if (comd[0][i] == '<' && comd[0][i + 1] == '>')
		{
			ft_reverse(comd, &i);
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
			return (0); // i should put an error msg if the file does not exist, i think it's gonna be easy
		i++;
	}
	comd[0] = ft_return_new_comd(comd);
	return (1);
}

int		ft_check_redirection(char **comm, t_all *all)
{
	int	i;
	int	j;

	j = 0;
	while(comm[j])
	{
		i = 0;
		while (comm[j][i])
		{
			if (comm[j] && is_charset(comm[j][i], "><"))
			{
				if (!ft_redirections(&comm[j], all, j))
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
