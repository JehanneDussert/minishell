/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_id.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-banv <ede-banv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 16:33:36 by ede-banv          #+#    #+#             */
/*   Updated: 2020/10/22 18:15:24 by ede-banv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*command_id(char **comm, t_all *all, int mode)//puisque je fais read
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
        all->exit->e = 1;
    else if (ft_strchr(comm[0], '/'))
        ft_exec(comm);//check si cest un binaire et excecuter le binaire
    //else on regarde pour binaire a excecuter (s'il y a un / dans le 1er mot)
    //s'il y a pas de / on cherche dans PATH
    if (mode == 1)
        free_read(&comm, NULL);
    return("done");
}

//pipes_id
    //boucle
    //  pipe
    //  dup2
    //  fork (pid dans pid de cmd)
    //  command_id
    //boucle
    //  wait_pid qui attend le pid du fils de chaque fork
char	*pipes_id(t_all *all)
{
    int i;
    int status;

    i = 0;
    while (all->cmd[i].cmd)
    {
        pipe(all->cmd[i].pipe);
        all->cmd[i].pid = fork();
        if (all->cmd[i].pid == 0)
        {
            if (i != 0)
            {
                dup2(all->cmd[i - 1].pipe[0], 0);
                close(all->cmd[i - 1].pipe[1]);
            }
            if (all->cmd[i + 1].cmd)
                dup2(all->cmd[i].pipe[1], 1);
            command_id(all->cmd[i].cmd, all, 0);
            close(all->cmd[i - 1].pipe[0]);
            close(all->cmd[i].pipe[1]);
            if (!all->cmd[i + 1].cmd)
                close(all->cmd[i].pipe[0]);
            exit(0);
        }
        else if (all->cmd[i].pid == -1)
            ;//erreur de fork
        i++;
    }
    i = 0;
    while (all->cmd[i].cmd)
    {
        waitpid(all->cmd[i].pid, &status, 0);//a voir la redaction
        close(all->cmd[i].pipe[0]);
        close(all->cmd[i].pipe[1]);
        //voir comment gerer les bails de pipes
        i++;
    }
    //free ts les t_cmd->cmd
    return ("done");
}