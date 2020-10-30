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

void	ft_stock_comd(char **comd)
{
	int	fd;

	if ((fd = open(comd[2], O_WRONLY)) == -1)
		ft_putendl_fd("error", 1); // erreur
	if (!ft_strcmp(comd[1], ">>")) // fichier exist + && >>
	{
		write(fd, comd[1], sizeof comd[1]);
	}
	/*else if (!ft_strcmp(comd[1], ">")) // fichier exist && >
	{

	}
	else // fichier does not exist
	{

	}*/
	close(fd);
}

void	ft_apply_comd(char **comd)
{
	(void)comd;
}

void	ft_redirections(char **comd)
{
	if (is_charset('>', comd[0]) == 1)
		ft_stock_comd(comd);
	else if (is_charset('<', comd[0]) == 1)
		ft_apply_comd(comd);
}
