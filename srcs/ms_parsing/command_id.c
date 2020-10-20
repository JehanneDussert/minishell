/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_id.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdussert <jdussert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 16:33:36 by ede-banv          #+#    #+#             */
/*   Updated: 2020/10/20 17:56:39 by jdussert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*command_id(char **comm, t_exit *exit)//puisque je fais read
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
        ;//fct vrs export
    else if (!ft_strcmp(comm[0], "unset"))
        ft_unset(comm);//fct vrs unset
    else if (!ft_strcmp(comm[0], "env"))
        ;//fct vrs env
    else if (!ft_strcmp(comm[0], "exit"))
        exit->e = 1;
    //else on regarde pour binaire a excecuter (s'il y a un / dans le 1er mot)
    //s'il y a pas de / on cherche dans PATH
    //si on free comm ici est-ce que ca marcher avec pipe?
    return("done");
}

char	*pipes_id(t_cmd **cmd, t_exit *exit)
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
    while (cmd[i]->cmd)
    {
        pipe(cmd[i]->pipe);
        cmd[i]->pid = fork();
        if (cmd[i]->pid == 0)
        {
            if (i != 0)
            {
                dup2(cmd[i - 1]->pipe[0], 0);
                close(cmd[i - 1]->pipe[1]);
            }
            if (cmd[i + 1]->cmd)
                dup2(cmd[i]->pipe[1], 1);
            command_id(cmd[i]->cmd, exit);
            close(cmd[i - 1]->pipe[0]);
        }
        else if (cmd[i]->pid == -1)
            ;//erreur de fork
        i++;
    }
    i = 0;
    while (cmd[i]->cmd)
    {
        waitpid(cmd[i]->pid, &status, 0);//a voir la redaction
        close(cmd[i]->pipe[0]);
        close(cmd[i]->pipe[1]);
        //voir comment gerer les bails de pipes
        i++;
    }
    return ("done");
}