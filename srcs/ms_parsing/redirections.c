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

void	ft_redirections(char **comd, t_all *all)
{
	int	i;

	i = 0;
	while (comd[i])
	{
		if ((comd[i][0] == '>' || comd[i][0] == '<') && (all->fd = open(comd[i], O_WRONLY)) == -1)
		{
				i++;
				all->fd = open(comd[i], O_CREAT | O_WRONLY);
		}
		else if (comd[i][0] == '>' && comd[i][1] == '>' && (all->fd = open(comd[i], O_WRONLY)) != -1)
		{
			;// add at the end of file
		}
		else if (comd[i][0] == '<' && (all->fd = open(comd[i], O_WRONLY)) != -1)
		{
			;// rm & write a new file
		}
		i++;
	}
	/*dup2(all->fd, 1);*/
	close(all->fd);
}
