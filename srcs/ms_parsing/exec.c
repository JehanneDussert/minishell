/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-banv <ede-banv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 14:53:40 by jdussert          #+#    #+#             */
/*   Updated: 2020/10/29 13:59:17 by ede-banv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**make_envp(t_all *all)
{
	char	**res;
	int		size;
	t_lst	*tmp;
	char	*buf;
	int		i;

	i = 0;
	size = ft_lstsize((t_list *)all->alst);
	if (!(res = malloc(sizeof(char *) * (size + 1))))
		return (NULL);
	tmp = all->alst;
	while (tmp)
	{
		if (tmp->content)
		{
			buf = ft_strjoin(tmp->key, "=");
			res[i++] = ft_strjoin(buf, tmp->content);
			ft_free((void **)&buf);
		}
		tmp = tmp->next;
	}
	res[i] = NULL;
	return (res);
}

int		execve_fct(char **comm, char *path, t_all *all)
{
	char	**envp;
	pid_t	pid;
	int		status;
	int		r;

	pid = fork();
	envp = make_envp(all);
	r = 1;
	if (pid == 0)
	{
		execve(path, comm, envp);
		error_msg("execve", strerror(errno));
		exit(1);
		r = 0;
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		all->err = WEXITSTATUS(status);
	// gerer les signaux: changer la valeur de retour en cas de signaux
	free_read(&envp, NULL);
	return (r);
}

int		ft_exec(char **comm, t_all *all)
{
	struct stat	file;

	if (stat(comm[0], &file) == -1)
	{
		error_msg("exec", strerror(errno));
		all->err = 127;
		errno = 0;
		return (0);
	}
	else if ((file.st_mode & S_IFREG) == S_IFREG)
	{
		execve_fct(comm, comm[0], all);
		/*pid = fork();
		envp = make_envp(all);
		if (pid == 0)
		{
			execve(comm[0], comm, envp);
			error_msg("execve", strerror(errno));
			exit(1);
		}
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			all->err = WEXITSTATUS(status);*/
	}
	else
	{
		error_msg("exec", "path does not point to a regular file");
		all->err = 126;
	}
	return (1);
}
