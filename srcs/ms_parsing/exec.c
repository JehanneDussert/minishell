/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 14:53:40 by jdussert          #+#    #+#             */
/*   Updated: 2020/10/27 01:23:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// int execve(const char *filename, char *const *argv[], char *const *envp)
// never return except if it fails, return -1

// filename : le nom de notre executable
// argv[] : tableau de chaines d'arguments qui doit se terminer par un pointeur NULL
// envp : environnement du n ouveau programme qui doit se terminer par un pointeur NULL

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
			ft_free(buf);
		}
		tmp = tmp->next;
	}
	return (res);
}

int     ft_exec(char **comm, t_all *all)
{
    // recuperer variables d'environnement dans liste chainee et les mettre ds un char * envp (make_envp)
    // chercher si binaire existe dans PATH (cf env PATH) -> PATH a save dans char *
    // chercher l'executable, /bin/ls
    // envoyer la commande **comm
    //if (execve() == -1)
    //    return (-1);
	char		**envp;
	struct stat	file;
	pid_t		pid;
    
	stat(comm[0], &stat); //on check l'etat du path
	if (file.st_mode == S_IFREG) // si cest un fichier regulier on excecute
	{
		pid = fork(); // on fork pour que execve puisse executer le process
		envp = make_envp(all);
		if (pid == 0)
		{
			if (execve(comm[0], comm, envp) == -1)
			{
				error_msg("execve", strerror(errno));
				errno = 0;
			}
			exit(0); //on exit le processus fils
		}
    return (0);
}