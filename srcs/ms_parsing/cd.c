/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmadebanville <emmadebanville@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 13:27:08 by ede-banv          #+#    #+#             */
/*   Updated: 2021/01/02 01:37:40 by emmadebanvi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		*catch = 1;
		all->err = 1;
	}
}

void	olddir(t_all *all, int *catch, char *path)
{
	//check if OLDPWD exists in env, if not, create it and set it to the current dir (other fct?)
	//if - and OLDPWD, cd to OLDPWD
	//if OLDPWD doesnt exist and cd -: error messade "OLDPWD not set" and errcode 1
}

void	cd_chdir(char *path, int *catch, t_all *all)
{
	if (ft_strcmp(path, '~') || ft_strcmp(path, '-'))
	{
		if (ft_strcmp(path, '~'))
			cd_home(all, catch);
		else
		{
			;//back to previous place
		}
	}
	if (chdir(path) == -1)
	{
		error_msg("cd", strerror(errno));
		errno = 0;
		all->err = 1;
		*catch = 1;
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
