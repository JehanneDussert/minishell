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

void    welcomer() //font from http://patorjk.com/software/taag/#p=display&h=1&v=1&f=Banner3&t=Minishell
{
    ft_putstr_fd("Welcome to our\n", 1);
    ft_putstr_fd("##     ## #### ##    ## ####  ######  ##     ## ######## ##       ##\n", 1);
    ft_putstr_fd("###   ###  ##  ###   ##  ##  ##    ## ##     ## ##       ##       ##\n", 1);
    ft_putstr_fd("#### ####  ##  ####  ##  ##  ##       ##     ## ##       ##       ##\n", 1);
    ft_putstr_fd("## ### ##  ##  ## ## ##  ##   ######  ######### ######   ##       ##\n", 1);
    ft_putstr_fd("##     ##  ##  ##  ####  ##        ## ##     ## ##       ##       ##\n", 1);
    ft_putstr_fd("##     ##  ##  ##   ###  ##  ##    ## ##     ## ##       ##       ##\n", 1);
    ft_putstr_fd("##     ## #### ##    ## ####  ######  ##     ## ######## ######## ########\n", 1);
    ft_putchar_fd('\n', 1);
}

void    ft_count_commands(int *count, char **buf)
{
    int i;

    i = 0;
    while (buf[i++])
    {
        *count += 1;
    }
}

void    ft_command_exec(char *comm, t_exit *exit)
{
    int     i;
    char    **commands;
    t_cmd   *cmd;
    int     count;

    i = 0;
    if (!(commands = ft_split_quote(comm, "|")))
        ;//error
    if (!commands[1] && !(command_id((ft_split_quote(commands[i], "\t\n\r\v \f")), exit))) //free le split ds command_id?
        ;//error
    ft_count_commands(&count, commands);//compter le nb de commandes
    if (!(cmd = malloc(sizeof(t_cmd) * (count + 1))))//creer le t_cmd * de bonne taille
        ;//error
    cmd[count].cmd = NULL;
    //fork de minishell pr le pipe
    while (cmd[i].cmd)
    {
        if (!(cmd[i].cmd = ft_split_quote(commands[i], "\t\n\r\v \f")))
            ;//error
        ft_free((void *)commands[i]);
        i++;
    }
    pipes_id(&cmd, exit);
    //free les cmd dans t_cmd ou command_id
    free(commands);
}

char    *ft_read()
{
    char    *line;
    char    **buf;
    int     count;
    int     i;
    t_exit  exit;

    count = 0;
    i = 0;
    buf = NULL;
    line = NULL;
    exit.e = 0;
    exit.d = 0;
    if ((get_next_line(1, &line)) == 1)
    {
        if (!(ft_check_errors_line(line)))
        {
            //free_read(&buf, &line);
            return ("done");
        }
        buf = ft_split_quote(line, ";");
        if (buf)
            ft_count_commands(&count, buf);
        //else
            //message d'erreur
        while (i != count)
            ft_command_exec(buf[i++], &exit);
    }
    //free_read(&buf, &line);
    if (exit.e == 1 || exit.d == 1)
        return (NULL);
    return("done");
}//il reste 3 lignes

int     main()
{
    int     x;
    char    *tmp;

    x = 1; //x is the variable that will mean the program will end
    //welcome message to begin the program.
    welcomer();
    while (x != 0) //x = 0 means the program closed
    {
        ft_putstr_fd("~:", 1);
        tmp = ft_read();//fct qui read et dispatche (grosse fct) return NULL si exit ou ctrl d on empty line
        if (tmp == NULL)
            x = 0;
    }
    //bye bye message
    return (1);
}