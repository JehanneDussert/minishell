/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 13:27:08 by ede-banv          #+#    #+#             */
/*   Updated: 2021/01/03 17:01:14 by ubuntu           ###   ########.fr       */
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

int		pwdexist(t_all *all, int *catch, int mode, t_lst *tmp)
{
	char	*buf;
	int		used;

	used = 0;
	if (!(buf = ft_calloc(sizeof(buf), 1024)))
	{
		all->err = 1;
		*catch = 1;
		ft_malloc_error("cd");
		return (0);
	}
	if (!tmp->content && mode == 1)//mode 1 : cd -
	{
		all->err = 1;
		*catch = 1;
		error_msg("cd", "OLDPWD not set");
	}
	else if (tmp->content && mode == 1)
	{
		getcwd(buf, 1024);
		chdir(tmp->content);
		ft_free((void **)&tmp->content);
		tmp->content = buf;
		used = 1;
	}
	else if (mode == 0)
	{
		getcwd(buf, 1024);
		ft_free((void **)&tmp->content);
		tmp->content = buf;
		used = 1;
	}
	if (used == 0)
		ft_free((void **)&buf);
	return (1);
}

int		olddir(t_all *all, int *catch, int mode)
{
	t_lst	*tmp;
	char	*buf;
	int		f;
	int		used;

	f = 0;
	used = 0;
	tmp = all->alst;
	buf = ft_calloc(sizeof(buf), 1024);
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "OLDPWD"))
		{
			f = 1;
			ft_free((void **)&buf);
			return (pwdexist(all, catch, mode, tmp));
		}
		tmp = tmp->next;
	}
	if (f == 0 && mode == 0)
	{
		getcwd(buf, 1024);
		ft_lstadd_back_ms(&all->alst, ft_lstnew_ms(ft_strdup("OLDPWD"), buf));
		used = 1;
	}
	else if (mode == 1)
	{
		all->err = 1;
		*catch = 1;
		error_msg("cd", "OLDPWD not set");
	}
	if (used == 0)
		ft_free((void **)&buf);
	return (1);
}

void	cd_chdir(char *path, int *catch, t_all *all)
{
	if (!ft_strcmp(path, "~") || !ft_strcmp(path, "-"))
	{
		if (!ft_strcmp(path, "~"))
			cd_home(all, catch);
		else
			olddir(all, catch, 1);
	}
	else if (*catch == 0 && olddir(all, catch, 0) && chdir(path) == -1)
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
		cd_home(all, &catch);
	else if (count > 1)
	{
		cd_chdir(cmd[1], &catch, all);
	}
	if (catch == 0)
		all->err = 0;
}
