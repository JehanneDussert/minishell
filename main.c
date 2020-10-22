/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 20:54:57 by marvin            #+#    #+#             */
/*   Updated: 2020/10/06 20:54:57 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "srcs/includes/minishell.h"

void    ft_count_commands(int *count, char **buf)
{
    int i;

    i = 0;
    while (buf[i++])
    {
        *count += 1;
    }
}

void    ft_command_exec(char *comm, t_all *all)
{
    int     i;
    char    **commands;
    int     count;
    int     res;

    i = 0;
    res = 0;
    if (!(commands = ft_split_quote(comm, "|")))
        res = -1;
    if (res == 0 && !commands[1] && !(command_id((ft_split_quote(commands[i], "\t\n\r\v \f")), all, 1)))
        res = -1;
    if (res == 0 && commands[1])
    {
        ft_count_commands(&count, commands);
        if (!(all->cmd = malloc(sizeof(t_cmd) * (count + 1))))
            res = -1;
        all->cmd[count].cmd = NULL;
        //fork de minishell pr le pipe (a demander a marc)
        while (res == 0 && all->cmd[i].cmd)
        {
            if (!(all->cmd[i].cmd = ft_split_quote(commands[i], "\t\n\r\v \f")))
            {
                ft_malloc_error(NULL);
                free_read(&commands, NULL);
                //free t_cmd
                return;
            }
            ft_free((void **)&commands[i]);
            i++;
        }
        pipes_id(all);
    }
    if (res == -1)
    {
        ft_malloc_error(NULL);
        free_read(&commands, NULL);
        return;
    }
    ft_free((void **)commands);
}

char    *ft_read(t_all *all)
{
    char    *line;
    char    **buf;
    int     count;
    int     i;

    count = 0;
    i = 0;
    buf = NULL;
    line = NULL;
    if ((get_next_line(1, &line)) == 1)
    {
        if (!(ft_check_errors_line(line, all)))
        {
            free_read(&buf, &line);
            return ("done");
        }
        buf = ft_split_quote(line, ";");
        if (buf)
            ft_count_commands(&count, buf);
        else
        {
            free_read(&buf, &line);
            ft_malloc_error(NULL);
            return ("erreur");
        }
        while (i != count)
            ft_command_exec(buf[i++], all);
    }
    free_read(&buf, &line);
    if (all->exit->e == 1 || all->exit->d == 1)
        return (NULL);
    return("done");
}

int     main(void)
{
    int     x;
    char    *tmp;
    t_all   all;

    x = 1;
    welcomer();
    ft_init_all(&all);
    while (x != 0)
    {
        ft_putstr_fd("~:", 1);
        tmp = ft_read(&all);
        if (tmp == NULL)
            x = 0;
    }
    //free all
    byebye();
    return (1);
}