/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-banv <ede-banv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 11:52:16 by ede-banv          #+#    #+#             */
/*   Updated: 2020/10/29 14:02:54 by ede-banv         ###   ########.fr       */
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

void	path_id(char **comm, t_all *all)
{
	char		**paths;
	struct stat	file;
	char		*path;
	int			i;
	int			err;

	i = 0;
	err = 0;
	if (!(path = find_path(all)))
		;//no path found
	if(!(paths = ft_split(path, ':')))
		;//malloc error
	while (paths && paths[i])
	{
		if (!(path = ft_strjoin_free(paths[i], "/", 0)))
			;//erreur de malloc
		if (!(path = ft_strjoin_free(path, comm[0], 1)))
			;//erreur de malloc
		if (stat(path, &file) == -1)
			err = 1;
		else if ((file.st_mode & S_IFREG) == S_IFREG)
		{
			err = 0;
			if (execve_fct(comm, path, all))
				break ;
		}
		ft_free((void **)&path);
		i++;
	}
	if (err == 1)
	{
		error_msg(NULL, strerror(errno));
		all->err = 127;
	}
	errno = 0;
	free_read(&paths, &path);
}
