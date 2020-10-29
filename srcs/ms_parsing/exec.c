/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-banv <ede-banv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 14:53:40 by jdussert          #+#    #+#             */
/*   Updated: 2020/10/29 11:30:29 by ede-banv         ###   ########.fr       */
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
			ft_free((void **)&buf);
		}
		tmp = tmp->next;
	}
	res[i] = NULL;
	return (res);
}

// recuperer variables d'environnement dans liste chainee et les mettre ds un char * envp (make_envp) (DONE)
// chercher si binaire existe dans PATH (cf env PATH) -> PATH a save dans char *
// chercher l'executable, /bin/ls
// envoyer la commande **comm

int		ft_exec(char **comm, t_all *all)
{
	char		**envp;
	struct stat	file;
	pid_t		pid;
	int			status;

	stat(comm[0], &file); //on check l'etat du path
	int binaire = file.st_mode & S_IFREG;
	if (binaire == S_IFREG) // si cest un fichier regulier on excecute
	{
		pid = fork(); // on fork pour que execve puisse executer le process
		envp = make_envp(all);
		if (pid == 0)
		{
			//if (execve(comm[0], comm, envp) == -1) // cette condition est useless dixit mli
			execve(comm[0], comm, envp);
			error_msg("execve", strerror(errno));
			errno = 0;
			exit(1); //on exit le processus fils
		}
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			all->err = WEXITSTATUS(status);
		// gerer les signaux:c hanger la cvaleur de retour en cas de signaux
	}
	else
	{
		error_msg("exec", "path does not point to a regular file");
		all->err = 126; //si le fichier existe
		//127 si le fichier existe pas

	}

	return (0);
}
