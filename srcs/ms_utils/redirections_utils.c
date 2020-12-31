/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehannedussert <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 16:51:36 by jehannedu         #+#    #+#             */
/*   Updated: 2020/12/29 16:51:40 by jehannedu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_nb_to_print(char **comd, char *charset)
{
	int	w;
	int	i;

	w = 0;
	i = 0;
	ft_nb_backslash(comd[0]);
	while (comd[0] && comd[0][i++])
	{
		w += g_all.bs;
		while (comd[0][i] && ((charset[0] != '#' && !is_charset(comd[0][i], charset))
			|| (charset[0] == '#')))
		{
			if (charset[0] == '#' && comd[0][i] == '#')
				return (w);
			w++;
			i++;
		}
		if (is_charset(comd[0][i], "><\\"))
			ft_skip_redirection(comd, &i);
	}
	return (w);
}

void	ft_copy_clean_comd(char **comd, char **tmp, char *charset)
{
	int	i;
	int	j;
	int nb;

	i = 0;
	j = 0;
	nb = 0;
	while (comd[0] && comd[0][i])
	{
		while (comd[0][i] == '\\' && charset[0] == '\\' && g_all.bs > nb)
		{
			tmp[0][j] = charset[0];
			j++;
			i++;
			nb++;
		}
		while (comd[0][i] && ((charset[0] != '#' && !is_charset(comd[0][i], charset))
			|| (charset[0] == '#')))
		{
			if (charset[0] == '#' && comd[0][i] == ' ' && comd[0][i + 1] == '#')
				return ;
			tmp[0][j] = comd[0][i];
			j++;
			i++;
		}
		while (comd[0][i] == '\\' && charset[0] == '\\' && g_all.bs > nb)
		{
			tmp[0][j] = charset[0];
			j++;
			i++;
			nb++;
		}
		ft_skip_redirection(comd, &i);
	}
}

char	*ft_return_new_comd(char **comd, char *charset)
{
	char	*tmp;
	int		w;

	w = ft_nb_to_print(comd, charset);
	if ((tmp = ft_calloc(w + 1, sizeof(char))) == NULL)
		return (NULL);
	ft_copy_clean_comd(comd, &tmp, charset);
	free_read(NULL, comd);
	if (tmp)
	{
		comd[0] = ft_strdup(tmp);
		ft_free((void **)&tmp);
	}
	return (comd[0]);
}

char	*ft_create_file(char *str, char **file, int *j)
{
	int		i;

	i = 0;
	while (is_charset(str[*j], "> "))
		(*j)++;
	while (str[i + (*j)] && str[i + (*j)] != ' ')
		i++;
	(*file) = ft_substr(str, *j, i);
	return (*file);
}

void	ft_redirection_out(t_all *all)
{
	if (all->copy_stdout > 2)
	{
		dup2(all->copy_stdout, STDOUT);
		close(all->copy_stdout);
	}
	if (all->copy_stdin > 2)
	{
		dup2(all->copy_stdin, STDIN);
		close(all->copy_stdin);
	}
}
