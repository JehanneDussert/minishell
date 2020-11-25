/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 11:52:16 by ede-banv          #+#    #+#             */
/*   Updated: 2020/11/25 14:57:27 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*find_path(t_all *all)
{
	t_lst	*tmp;

	tmp = all->alst;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "PATH"))
			return (tmp->content);
		tmp = tmp->next;
	}
	return (NULL);
}

int		path_two(char **comm, t_all *all, char **path, char **paths)
{
	struct stat	file;
	int			i;
	int 		r;

	i = 0;
	r = 0;
	while (paths && paths[i])
	{
		if (!(*path = ft_strjoin_free(paths[i], "/", 0)))
		{
			all->err = 1;
			return (ft_malloc_error(comm[0]));
		}
		if (!(*path = ft_strjoin_free(*path, comm[0], 1)))
		{
			all->err = 1;
			return (ft_malloc_error(comm[0]));
		}
		if (stat(*path, &file) == -1)
			r = 1;
		else if ((file.st_mode & S_IFREG) == S_IFREG)
		{
			r = 0;
			//signal ctrlc et ctrlbackslash
			if (execve_fct(comm, *path, all))
				break ;
		}
		ft_free((void **)path);
		i++;
	}
	return (r);
}

void	path_id(char **comm, t_all *all)
{
	char		**paths;
	char		*path;
	int			err;

	err = 0;
	if (!(path = find_path(all)))
	{
		error_msg(comm[0], "no such file or directory");
		all->err = 127;
		return ;
	}
	if(!(paths = ft_split(path, ':')))
	{
		ft_malloc_error(comm[0]);
		all->err = 1;
		return ;
	}
	err = path_two(comm, all, &path, paths);
	if (err == 1)
	{
		error_msg(comm[0], strerror(errno));
		all->err = 127;
	}
	errno = 0;
	free_read(&paths, &path);
}
