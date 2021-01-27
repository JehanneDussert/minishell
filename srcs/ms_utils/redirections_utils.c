/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdussert <jdussert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 16:21:48 by jehannedu         #+#    #+#             */
/*   Updated: 2021/01/27 15:22:29 by jdussert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_copy_clean_comd(char **comd, char **tmp, char *charset)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	skipspace(comd[0], &i);
	while (comd[0] && comd[0][i])
	{
		while (comd[0][i] && (!is_charset(comd[0][i], charset)))
			ft_cmd_fill(comd, &tmp, &i, &j);
		ft_skip_redirection(comd, &i);
	}
}

char	*ft_return_new_comd(char **comd, char *charset)
{
	char	*tmp;
	int		w;

	w = ft_strlen(comd[0]);
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
	while (is_charset(str[*j], ">< "))
		(*j)++;
	while (str[*j + i] && !is_charset(str[*j + i], " \\><"))
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
	all->redir = 0;
}
