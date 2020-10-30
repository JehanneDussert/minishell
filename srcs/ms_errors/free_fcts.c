/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_fcts.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 14:15:42 by ede-banv          #+#    #+#             */
/*   Updated: 2020/10/26 17:45:05 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_read(char ***buf, char **line)
{
	int	i;
	char	**tmp;

	i = 0;
	if (!line && !buf)
		return ;
	if (line && *line)
		ft_free((void **)line);
	if (buf)
	{
		tmp = *buf;
		while (tmp[i])
		{
			ft_free((void **)&tmp[i]);
			i++;
		}
		ft_free((void **)buf);
		*buf = NULL;
	}
}

void	free_commands(t_all *all)
{
	int	i;

	i = 0;
	while (all->cmd && all->cmd[i].cmd)
	{
		free_read(&all->cmd[i].cmd, NULL);
	}
}

void	free_all(t_all *all)
{
	ft_free((void **)&all->exit);
	free_commands(all);
	ft_lstclear_ms(&all->alst, free);
}
