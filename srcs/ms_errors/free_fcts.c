/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_fcts.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-banv <ede-banv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 14:15:42 by ede-banv          #+#    #+#             */
/*   Updated: 2020/10/26 14:20:51 by ede-banv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_read(char ***buf, char **line)
{
	if (!line && !buf)
		return ;
	if (line && *line)
		ft_free((void *)line);
	if (buf && *buf)
	{
		while (**buf)
		{
			ft_free((void *)buf);
			(**buf)++;
		}
		ft_free((void *)buf);
	}
}

void	free_commands(t_all *all)
{
	int	i;

	while(all->cmd[i].cmd)
	{
		free_read(all->cmd[i].cmd, NULL);
	}
}

void	free_all(t_all *all)
{
	ft_free((void **)&all->exit);
	free_commands(all);
}
