/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdussert <jdussert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 14:53:40 by jdussert          #+#    #+#             */
/*   Updated: 2020/10/21 15:43:06 by jdussert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// int execve(const char *filename, char *const *argv[], char *const *envp)
// never return execpt if it fails, return -1 

// filename : le nom de notre executable
// argv[] : tableau de chaines d'arguments qui doit se terminer par un pointeur NULL
// envp : environnement du nouveau programme qui doit se terminer par un pointeur NULL

int     ft_exec(char *filename)
{
    if (execve(filename) == -1)
        return (-1);
    return (0);
}