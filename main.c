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
/*
void    ft_command_exec(char *comm)
{
    int     i;
    char    *commands;

    i = 0;
    if (!(commands = ft_split_quote(comm, "|")))
        ;//error
    if (!(command_id(ft_split_quote(commands[i++], "\t\n\r\v \f"))))
        ;//error
    while (commands[i])
    {
        if (!(pipes_id(ft_split_quote(commands[i++], "\t\n\r\v \f"))))
            ;//error
    }
    //free les splits par pipe
}
*/
char    *ft_read()
{
    char    *line;
    int     n;
    char    **buf;
    int     count;
    int     i;

    n = 1;
    count = 0;
    i = 0;
    buf = NULL;
    if ((n = get_next_line(1, &line)) == 1)
    {
        // rajouter un if check error == 0 -> on sort
        if (!(ft_check_errors_line(line)))
        {
            //message d'erreur
            ft_putstr_fd("\n", 1);
            ft_putstr_fd("done", 1);
            ft_putstr_fd("\n", 1);
            return ("done");
        }
        //ft_check_errors_line(line); //fonction qui checke les erreurs de ma ligne      
        buf = ft_split_quote(line, ";");
        if (buf)
            ft_count_commands(&count, buf);
        else
            //message d'erreur
        while (i != count)
        {
            //ft_command_exec(buf[i++]);
        }
    }
    //free buf et line
    return(*buf);
}

int     main()
{
    int     x;
    char    *tmp;

    x = 1; //x is the variable that will mean the program will end
    //welcome message to begin the program.
    //boucle w prompt?
    welcomer();
    while (x != 0) //x = 0 means the program closed
    {
        ft_putstr_fd("~:", 1);
        tmp = ft_read();//fct qui read et dispatche (grosse fct) return NULL si exit ou ctrl d on empty line
        if (tmp == NULL)
            x = 0;
    }
    return (1);
}