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

void	ft_stock_comd(char **comd, t_all *all)
{
	(void)all;
	if (!ft_strcmp(comd[1], ">>")) // fichier exist + && >>
	{
		;
	}
	else if (!ft_strcmp(comd[1], ">")) // fichier exist && >
	{

	}
	else // fichier does not exist
	{

	}
}

void	ft_apply_comd(char **comd, t_all *all)
{
	(void)comd;
	(void)all;
}

void	ft_redirections(char **comd, t_all *all)
{
	int	i;

	i = 0;
	while (comd[i])
	{
		while (comd[i] && comd[i][0] != '>' && comd[i][0] != '<')
			i++;
		if ((all->fd = open(comd[i], O_WRONLY)) == -1)
		{
			if (comd[i] && comd[i][0] == '>' && comd[i][1] == '>')
			{
				i++;
				all->fd = open(comd[i], O_CREAT | O_WRONLY);
			}
		}
		i++;
	}
		//ft_putendl_fd("error", 1); // erreur
	/*dup2(all->fd, 1);
	if (is_charset('>', comd[1][0]) == 1)
		ft_stock_comd(comd, all);
	else if (is_charset('<', comd[1][0]) == 1)
		ft_apply_comd(comd, all);*/
	close(all->fd);
}
