/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 20:44:52 by ubuntu            #+#    #+#             */
/*   Updated: 2021/01/04 18:51:58 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		pwd_error(t_all *all, int *catch, int mode)
{
	if (mode == 0)
	{
		all->err = 1;
		*catch = 1;
		ft_malloc_error("cd");
		return (0);
	}
	else
	{
		all->err = 1;
		*catch = 1;
		error_msg("cd", "OLDPWD not set");
	}
	return (1);
}

int		pwdexist(t_all *all, int *catch, int mode, t_lst *tmp)
{
	char	*buf;

	if (!(buf = ft_calloc(sizeof(buf), 1024)))
		return (pwd_error(all, catch, 0));
	if (!tmp->content && mode == 1)
		pwd_error(all, catch, 1);
	else if (tmp->content && mode == 1)
	{
		getcwd(buf, 1024);
		chdir(tmp->content);
		ft_free((void **)&tmp->content);
		tmp->content = buf;
	}
	else if (mode == 0)
	{
		getcwd(buf, 1024);
		ft_free((void **)&tmp->content);
		tmp->content = buf;
	}
	if (!tmp->content && mode == 1)
		ft_free((void **)&buf);
	return (1);
}

int		create_oldpwd(t_all *all, int *catch, char **buf)
{
	char	*oldpwd;
	t_lst	*new;

	if (!(oldpwd = ft_strdup("OLDPWD")))
	{
		ft_free((void **)buf);
		return (pwd_error(all, catch, 0));
	}
	if (!(new = ft_lstnew_ms(oldpwd, *buf)))
	{
		ft_free((void **)buf);
		return (pwd_error(all, catch, 0));
	}
	ft_lstadd_back_ms(&all->alst, new);
	return (1);
}

int		olddir(t_all *all, int *catch, int mode)
{
	t_lst	*tmp;
	char	*buf;

	tmp = all->alst;
	if (!(buf = ft_calloc(sizeof(buf), 1024)))
		return (pwd_error(all, catch, 0));
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "OLDPWD"))
		{
			ft_free((void **)&buf);
			return (pwdexist(all, catch, mode, tmp));
		}
		tmp = tmp->next;
	}
	if (mode == 0)
	{
		getcwd(buf, 1024);
		if (!(create_oldpwd(all, catch, &buf)))
			return (0);
	}
	else if (mode == 1)
		ft_free((void **)&buf);
	return (mode == 1 ? pwd_error(all, catch, 1) : 1);
}
