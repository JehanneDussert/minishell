/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_id.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-banv <ede-banv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 16:33:36 by ede-banv          #+#    #+#             */
/*   Updated: 2020/10/21 14:59:33 by ede-banv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*command_id(char **comm, t_all *all)//puisque je fais read
{
    //identifier la commande selon le 1er token
    //builtin
    if (!ft_strcmp(comm[0], "echo"))
        ft_echo(comm);
    else if (!ft_strcmp(comm[0], "cd"))
        cd_id(comm);//fct vrs cd
    else if (!ft_strcmp(comm[0], "pwd"))
        pwd_id();//fct vrs pwd
    else if (!ft_strcmp(comm[0], "export"))
        export_id(comm, all);//fct vrs export
    else if (!ft_strcmp(comm[0], "unset"))
        ft_unset(comm);//fct vrs unset
    else if (!ft_strcmp(comm[0], "env"))
        ;//fct vrs env
    else if (!ft_strcmp(comm[0], "exit"))
        all->exit->e = 1;
    else if (ft_strchr(comm[0], '/'))
        ;//check si cest un binaire et excecuter le binaire
    //else on regarde pour binaire a excecuter (s'il y a un / dans le 1er mot)
    //s'il y a pas de / on cherche dans PATH
    //si on free comm ici est-ce que ca marcher avec pipe?
    return("done");
}

char	*pipes_id(t_all *all)
{
    int i;
    int status;
    //cette fonction va se servir de command id donc cest dans comand id que le debut de l'excecution des commandes va se faire
    //si ca se sert de comm_id

    i = 0;
    //boucle
    //  pipe
    //  dup2
    //  fork (pid dans pid de cmd)
    //  command_id
    //boucle
    //  wait_pid qui attend le pid du fils de chaque fork
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
            command_id(all->cmd[i].cmd, all);
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
    return ("done");
}