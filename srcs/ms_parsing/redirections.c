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

int		ft_nb_to_print(char ***comd)
{
	int	w;
	int	i;

	w = 0;
	i = -1;
	while ((*comd) && (*comd)[++i])
	{
		if (!is_charset((*comd)[i][0], "><"))
			w++;
		else
			i++;
	}
	return (w);
}

void	ft_copy_clean_comd(char ***comd, char ***tmp, int w)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while ((*comd) && (*comd)[++i])
	{
		ft_putstr_fd("redirections, copy clean comd : ", 2);
		ft_putendl_fd((*comd)[i], 2);
		if (j <= w && !is_charset((*comd)[i][0], "><"))
		{
			(*tmp)[j++] = ft_strdup((*comd)[i]);
		}
		else if ((*comd)[i + 1])
		{
			ft_free((void **)&(*comd)[i++]);
		}
		ft_free((void **)&(*comd)[i]);
	}
	ft_free((void **)&(*comd));
}

char	***ft_return_new_comd(char ***comd)
{
	char	**tmp;
	int		i;
	int		w;

	i = -1;
	w = ft_nb_to_print(comd);
	if ((tmp = ft_calloc(w + 1, sizeof(char *))) == NULL)
		return (NULL);
	tmp[w] = NULL;
	ft_putstr_fd("redir, first comd sent :", 2);
	ft_putendl_fd((*comd)[0], 2);
	ft_copy_clean_comd(comd, &tmp, w);
	if (((*comd) = ft_calloc(w + 1, sizeof(char *))) == NULL)
		return (NULL);
	(*comd)[w] = NULL;
	while (tmp && tmp[++i])
	{
		(*comd)[i] = ft_strdup(tmp[i]);
		ft_free((void **)&tmp[i]);
	}
	ft_free((void **)&tmp);
	return (comd);
}

void	ft_redir_plus(char ***comd, t_all *all, int *i)
{
	if ((*comd)[*i][0] == '>' && (*comd)[*i][1] == '>'
		&& (all->fd = open((*comd)[(*i) + 1], O_WRONLY)) >= 0)
		all->fd = open((*comd)[++(*i)], O_WRONLY | O_APPEND, S_IRWXU);
	else if ((*comd)[*i][0] == '>')
		all->fd = open((*comd)[++(*i)], O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
	all->fd_copy = dup(1);
	dup2(all->fd, 1);
	close(all->fd);
}

int		ft_redir_less(char ***comd, t_all *all, int i)
{
	// prbl
	if ((all->fd = open((*comd)[i + 1], O_WRONLY)) < 0)
		return (0);
	printf("this is fd :%d\n", all->fd);
	all->fd_copy = dup(0);
	dup2(all->fd, 0);
	close(all->fd);
	return (1);
}

int		ft_reverse(char ***comd, int *i)
{
	if ((open((*comd)[++(*i)], O_CREAT | O_WRONLY)) < 0)
		return (0);
	return (1);
}

void	ft_redirections(char ***comd, t_all *all)
{
	int	i;

	i = 0;
	all->fd = 1;
	while ((*comd)[i])
	{
		if ((*comd)[i][0] == '<' && (*comd)[i][1] == '>' && !ft_reverse(comd, &i))
			return ;
		else if (is_charset((*comd)[i][0], ">"))
			ft_redir_plus(comd, all, &i);
		else if ((*comd)[i][0] == '<' && (!ft_redir_less(comd, all, i)))
			return ;
		/*else if (!is_charset((*comd)[i][0], "><") && (open((*comd)[i], O_WRONLY)) < 0)
		{
			//error_msg((*comd)[i], "No such file or directory");
			return ;
		}*/
		i++;
	}
	comd = ft_return_new_comd(comd);
}

void	ft_check_redirection(char ***comm, t_all *all)
{
	int	i;

	i = 0;
	while ((*comm) && (*comm)[i])
	{
		if (is_charset((*comm)[i][0], "><"))
		{
			ft_redirections(comm, all);
			return ;
		}
		i++;
	}
}
