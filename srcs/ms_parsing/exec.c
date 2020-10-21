/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdussert <jdussert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 14:53:40 by jdussert          #+#    #+#             */
/*   Updated: 2020/10/21 16:39:44 by jdussert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// int execve(const char *filename, char *const *argv[], char *const *envp)
// never return except if it fails, return -1 

// filename : le nom de notre executable
// argv[] : tableau de chaines d'arguments qui doit se terminer par un pointeur NULL
// envp : environnement du nouveau programme qui doit se terminer par un pointeur NULL

int     ft_exec(char **comm)
{
    // recuperer variables d'environnement dans liste chainee : tt ce qui est dans env
    // chercher si binaire existe dans PATH (cf env PATH) -> PATH a save dans char *
    // chercher l'executable, /bin/ls
    // envoyer la commande **comm
    //if (execve() == -1)
    //    return (-1);
    (void)comm;
    return (0);
}