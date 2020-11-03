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

char	***ft_return_new_comd(char ***comd)
{
	char	**tmp;
	int		i;
	int		w;

	i = -1;
	w = 0;
	while((*comd)[w] && !is_charset((*comd)[w][0], "><"))
		w++;
	if (!(tmp = malloc(sizeof(char *) * (w + 1))))
		return(NULL);
	while((*comd)[++i] && i < w)
	{
		tmp[i] = ft_substr((*comd)[i], 0, ft_strlen((*comd)[i]));
		ft_free((void **)&(*comd)[i]);
	}
	i = -1;
	if (!(*comd = malloc(sizeof(char *) * (w + 1))))
		return(NULL);
	while(tmp[++i] && !is_charset(tmp[i][0], "><"))
	{
		printf("this is tmp :%s\n", tmp[i]);
		// prbl here
		ft_memcpy((*comd)[i], tmp[i], ft_strlen(tmp[i]));
	}
	return(comd);
}

void	ft_create_new_file(char *comd, int *fd)
{
	*fd = open(comd, O_CREAT | O_RDWR);
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

void	ft_redirections(char ***comd, t_all *all)
{
	int	i;

	i = 0;
	all->fd = 0;
	while ((*comd)[i])
	{
		if (((*comd)[i][0] == '>' || (*comd)[i][0] == '<') && (all->fd = open((*comd)[i], O_WRONLY)) == -1)
			ft_create_new_file((*comd)[++i], &all->fd);
		else if ((*comd)[i][0] == '>' && (*comd)[i][1] == '>' && (all->fd = open((*comd)[i], O_WRONLY)) != -1)
			;//ft_write_new_comd(comd[i], all);
		else if ((*comd)[i][0] == '<' && (all->fd = open((*comd)[i], O_WRONLY)) != -1)
			;//ft_replace_file(comd[i], all);
		i++;
	}
	ft_putendl_fd("1", 1);
	ft_putendl_fd("2", 1);
	printf("here now\n");
	comd = ft_return_new_comd(comd);
	i = -1;
	printf("this is comd 0:%s", (*comd)[0]);
	//while ((*comd)[++i])
	//printf("new comd :%s\n", (*comd)[0]);
	//need to create a tmp that will truncate comm before >>
	//and free the cmd after
	printf("dup :%d\n", dup2(all->fd, 1));
	close(all->fd);
}
