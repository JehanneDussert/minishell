/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_id.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 16:33:36 by ede-banv          #+#    #+#             */
/*   Updated: 2020/10/19 17:25:13 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*command_id(char **comm, t_exit *exit)//puisque je fais read 
{
    //identifier la commande selon le 1er token
    if (!ft_strncmp(comm[0], "echo", 4))
        ;//fct vers echo
    else if (!ft_strncmp(comm[0], "cd", 2))
        ;//fct vrs cd
    else if (!ft_strncmp(comm[0], "pwd", 3))
        ;//fct vrs pwd
    else if (!ft_strncmp(comm[0], "export", 6))
        ;//fct vrs export
    else if (!ft_strncmp(comm[0], "unset", 5))
        ;//fct vrs unset
    else if (!ft_strncmp(comm[0], "env", 3))
        ;//fct vrs env
    else if (!ft_strncmp(comm[0], "exit", 4))
        exit->e = 1;
    else if (!ft_strncmp(comm[0], "./", 2))
        ;//fct vrs execution de binaire
    //chevrons aussi
    //cntrl stuff?
    //si on free comm ici est-ce que ca marcher avec pipe?
    return("done");
}

char	*pipes_id(t_cmd **cmd, t_exit *exit)
{
    int i;
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
        pipe(&cmd[i]->pipe);
        dup2(cmd[i]->pipe[1], 1);
        cmd[i]->pid = fork();
        command_id(cmd[i]->cmd, exit);
        i++;
    }
    i = 0;
    while (cmd[i]->cmd)
    {
        waitpid(cmd[i]->pid);//a voir la redaction
        //voir comment gerer les bails de pipes
        i++;
    }
    return ("done");
}