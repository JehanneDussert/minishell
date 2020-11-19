/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehannedussert <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 14:21:15 by jehannedu         #+#    #+#             */
/*   Updated: 2020/10/30 14:21:17 by jehannedu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// comd : comd + redirection
// tmp : doit contenir comd sans la redirection (< ou > + comd[i])
// free comd + on re-remplit avec tmp et on free tmp

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
		if (j <= w && !is_charset((*comd)[i][0], "><"))
			(*tmp)[j++] = ft_substr((*comd)[i], 0, ft_strlen((*comd)[i]));
		else if ((*comd)[i + 1])
			ft_free((void **)&(*comd)[i++]);
		ft_free((void **)&(*comd)[i]);
	}
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
	ft_copy_clean_comd(comd, &tmp, w);
	if (((*comd) = ft_calloc(w + 1, sizeof(char *))) == NULL)
		return (NULL);
	while (tmp && tmp[++i])
	{
		(*comd)[i] = ft_substr(tmp[i], 0, ft_strlen(tmp[i]));
		ft_free((void **)&tmp[i]);
	}
	return (comd);
}

void	ft_create_new_file(char *comd, int *fd)
{
	*fd = open(comd, O_RDWR | O_CREAT, S_IRWXU | O_TRUNC);
}

void	ft_redirections(char ***comd, t_all *all)
{
	int	i;

	i = 0;
	all->fd = 1;
	while ((*comd)[i])
	{
		if (((*comd)[i][0] == '>' || (*comd)[i][0] == '<')
			&& (all->fd = open((*comd)[i], O_WRONLY)) == -1)
			ft_create_new_file((*comd)[++i], &all->fd);
		else if ((*comd)[i][0] == '>' && (*comd)[i][1] == '>'
				&& (all->fd = open((*comd)[i], O_WRONLY)) != -1)
			;//ft_write_new_comd(comd[i], all);
		else if ((*comd)[i][0] == '<' &&
				(all->fd = open((*comd)[i], O_WRONLY)) != -1)
			;//ft_replace_file(comd[i], all);
		i++;
	}
	comd = ft_return_new_comd(comd);
	all->fd_copy = dup(1);
	dup2(all->fd, 1);
	//close(all->fd);
}
