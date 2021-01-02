/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_id.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmadebanville <emmadebanville@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 16:33:36 by ede-banv          #+#    #+#             */
/*   Updated: 2021/01/01 22:13:43 by emmadebanvi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*command_id(char **comm, t_all *all, int mode)
{
	if (!ft_strcmp(comm[0], "echo"))
		ft_echo(comm, all);
	else if (!ft_strcmp(comm[0], "cd"))
		cd_id(comm, all);
	else if (!ft_strcmp(comm[0], "pwd"))
		pwd_id(all);
	else if (!ft_strcmp(comm[0], "export"))
		export_id(comm, all);
	else if (!ft_strcmp(comm[0], "unset"))
		ft_unset(comm, all);
	else if (!ft_strcmp(comm[0], "env"))
		env_id(comm, all);
	else if (!ft_strcmp(comm[0], "exit"))
		ft_exit_fct(all, comm);
	else if (ft_strchr(comm[0], '/'))
		ft_exec(comm, all);
	else
		path_id(comm, all);
	if (mode == 1)
		free_read(&comm, NULL);
	return ("done");
}

void	in_fork(t_all *all, int i)
{
	if (i != 0)
	{
		dup2(all->cmd[i - 1].pipe[0], 0);
		close(all->cmd[i - 1].pipe[1]);
	}
	if (all->cmd[i + 1].cmd)
		dup2(all->cmd[i].pipe[1], 1);
	command_id(all->cmd[i].cmd, all, 0);
	if (i != 0)
		close(all->cmd[i - 1].pipe[0]);
	close(all->cmd[i].pipe[1]);
	if (!all->cmd[i + 1].cmd)
		close(all->cmd[i].pipe[0]);
	exit(0);
}

char	*pipes_id(t_all *all)
{
	int	i;
	int	status;

	i = -1;
	while (all->cmd[++i].cmd)
	{
		pipe(all->cmd[i].pipe);
		all->cmd[i].pid = fork();
		if (all->cmd[i].pid == 0)
			in_fork(all, i);
		else if (all->cmd[i].pid == -1)
		{
			error_msg("fork", "unable to create fork");
			all->err = 1;
		}
	}
	i = -1;
	while (all->cmd[++i].cmd)
	{
		waitpid(all->cmd[i].pid, &status, 0);
		close(all->cmd[i].pipe[0]);
		close(all->cmd[i].pipe[1]);
	}
	free_commands(all);
	return ("done");
}

char	*if_pipes(char **commands, t_all *all, int *res)
{
	int		count;
	int		i;

	i = -1;
	count = 0;
	ft_count_commands(&count, commands);
	if (!(all->cmd = malloc(sizeof(t_cmd) * (count + 1))))
		*res = -1;
	all->cmd[count].cmd = NULL;
	while (*res == 0 && all->cmd[++i].cmd)
	{
		if (!(all->cmd[i].cmd = ft_split_quote(commands[i],
		"\t\n\r\v \f")))
		{
			all->err = 1;
			ft_malloc_error(NULL);
			free_read(&commands, NULL);
			free_commands(all);
			return (NULL);
		}
		ft_free((void **)&commands[i]);
	}
	pipes_id(all);
	ft_free((void **)&all->cmd);
	return ("done");
}
