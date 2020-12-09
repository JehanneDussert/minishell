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
// FIXED : si plusieurs commandes séparées par des ; 
// ERREUR si | :  semble leaker + le pipe ne fonctionne pas

// LEAKS : s'il n'y a pas de pipe, c'est bien toute la commande qui est envoyée, dès 
// le commande[0] MAIS s'il y a un pipe, c'est comme si on m'envoyait la commande
// à partir du pipe
// ex : echo lol > test.txt : commande[0] sera bien echo
// ex : echo lol | cat -e > test.txt : commande[0] sera cat
// donc quand je vais free si y a un pipe, je ne free pas la première partie de la commande

int		ft_nb_to_print(char **comd)
{
	int	w;
	int	i;

	w = 0;
	i = 0;
	while (comd[0] && comd[0][i])
	{
		while (comd[0][i] && !is_charset(comd[0][i], "><"))
		{
			w++;
			i++;
		}
		ft_skip_redirection(comd, &i);
	}
	return (w);
}

void	ft_copy_clean_comd(char **comd, char **tmp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (comd[0] && comd[0][i])
	{
		while (comd[0][i] && !is_charset(comd[0][i], "><"))
		{
			tmp[0][j] = comd[0][i];
			j++;
			i++;
		}
		ft_skip_redirection(comd, &i);
	}
}

char	*ft_return_new_comd(char **comd)
{
	char	*tmp;
	int		w;

	w = ft_nb_to_print(comd);
	if ((tmp = ft_calloc(w + 1, sizeof(char))) == NULL)
		return (NULL);
	ft_copy_clean_comd(comd, &tmp);
	free_read(NULL, comd);
	if (tmp)
	{
		comd[0] = ft_strdup(tmp);
		ft_free((void **)&tmp);
	}
	return (comd[0]);
}

void	ft_redir_plus(char **comd, t_all *all, int *i)
{
	if (comd[0][*i] == '>' && comd[0][*i + 1] == '>')
	{
		while (is_charset(comd[0][*i], "> "))
			(*i)++;
		if ((all->fd = open(&comd[0][*i], O_WRONLY)) >= 0)
			all->fd = open(&comd[0][*i], O_WRONLY | O_APPEND, S_IRWXU);
	}
	else if (comd[0][*i] == '>')
	{
		while (is_charset(comd[0][*i], "> "))
			(*i)++;
		all->fd = open(&comd[0][*i], O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
	}
	all->fd_copy = dup(1);
	dup2(all->fd, 1);
	close(all->fd);
}

int		ft_redir_less(char **comd, t_all *all, int *i)
{
	// prbl
	i++;
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
			return ;
		/*else if (!is_charset(comd[i][0], "><") && (open(comd[i], O_WRONLY)) < 0)
		{
			//error_msg(comd[i], "No such file or directory");
			return ;
		}*/
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
