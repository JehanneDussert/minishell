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

void	ft_create_new_file(char *comd, t_all *all)
{
	all->fd = open(comd, O_CREAT | O_RDWR);
}
/*
void	ft_write_new_comd(char *comd, t_all *all)
{
	;// add at the end of file
}

void	ft_replace_file(char *comd, t_all *all)
{
	;// rm & write a new file
}*/

void	ft_redirections(char **comd, t_all *all)
{
	int	i;

	i = 0;
	all->fd = 0;
	while (comd[i])
	{
		if ((comd[i][0] == '>' || comd[i][0] == '<') && (all->fd = open(comd[i], O_WRONLY)) == -1)
			ft_create_new_file(comd[++i], all);
		else if (comd[i][0] == '>' && comd[i][1] == '>' && (all->fd = open(comd[i], O_WRONLY)) != -1)
			;//ft_write_new_comd(comd[i], all);
		else if (comd[i][0] == '<' && (all->fd = open(comd[i], O_WRONLY)) != -1)
			;//ft_replace_file(comd[i], all);
		i++;
	}
	dup2(all->fd, 1);
	close(all->fd);
}
