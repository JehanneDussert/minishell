/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-banv <ede-banv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 11:52:16 by ede-banv          #+#    #+#             */
/*   Updated: 2020/10/29 12:19:14 by ede-banv         ###   ########.fr       */
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
	int			count;
	char		**paths;
	struct stat	file;
	char		*path;
	int			i;

	//plusierues options de ou chercher separee par : (split normal)
	//join le path qu'on teste avec le nom de l'excecutable et regarder le stat
	if (!(path = find_path(all)))
		;//no path found
	if(!(paths = ft_split(path, ':')))
		;//malloc error
	while (paths && paths[i])
	{
		if (!(path = ft_strjoin(paths[i], comm[0])))
			;//erreur de malloc
		if (stat(path, &file) == -1)
		{
			error_msg(NULL, "no such file or directory");
			all->err = 127;
			return ;
		}
		else if ((file.st_mode & S_IFREG) == S_IFREG)
			execve_fct(comm, all);
		free(path);
		i++;
	}
}