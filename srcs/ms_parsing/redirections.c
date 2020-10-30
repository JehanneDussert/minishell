/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 14:21:15 by jehannedu         #+#    #+#             */
/*   Updated: 2020/10/30 17:12:47 by marvin           ###   ########.fr       */
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

/*void	ft_redirections(char **comd, t_all *all)
{
	if ((all->fd = open(comd[2], O_WRONLY)) == -1)
		ft_putendl_fd("error", 1); // erreur
	if (is_charset('>', comd[1][0]) == 1)
		ft_stock_comd(comd, all);
	else if (is_charset('<', comd[1][0]) == 1)
		ft_apply_comd(comd, all);
	close(all->fd);
}*/
