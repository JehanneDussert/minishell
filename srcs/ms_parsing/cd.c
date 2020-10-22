/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 13:27:08 by ede-banv          #+#    #+#             */
/*   Updated: 2020/10/22 22:05:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cd_chdir(char *path, int *catch, t_all *all)
{
	if (chdir(path) == -1)
	{
		error_msg("cd", strerror(errno));
		errno = 0;
		all->err = 1;
		*catch = 1;
	}
}

void	cd_home(t_all *all, int *catch)
{
	t_lst	*tmp;
	int		done;

	tmp = all->alst;
	done = 0;
	while (tmp)
	{
		if (!ft_strcmp("HOME", tmp->key))
		{
			cd_chdir(tmp->content, catch, all);
			done = 1;
		}
		tmp = tmp->next;
	}
	if (done == 0)
	{
		error_msg("cd", "home environment variable not set.");
		catch = 1;
		all->err = 1;
	}
}

void	cd_id(char **cmd, t_all *all)
{
	int		count;
	int		catch;

	count = 0;
	catch = 0;
	ft_count_commands(&count, cmd);
	if (count == 1)
	{
		cd_home(all, &catch);
	}
	else if (count > 1)
	{
		cd_chdir(cmd[1], &catch, all);
	}
	if (catch == 0)
		all->err = 0;
}
