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

void    ft_command_exec(char *comm)
{
    int i;

    i = 0;
    (void)i;
    (void)comm;
    //compter les pipes?
    //faire premier split par pipes
    //checker s'il y avait des pipes: changer variable?
    //split par whitespace
    //gerer commande par commande selon le premier token

}

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
    if ((n = get_next_line(1, &line)) == 1)
    {
        if (!check_double(line, ";|")) //fonction qui checke les erreurs de ma ligne
            //erreur, fonction ft_error a return
        buf = ft_split_quote(line, ";");
        if (buf)
            ft_count_commands(&count, buf);
        else
            //message d'erreur
        while (i != count)
        {
            ft_command_exec(buf[i++]);
        }
    }
    // pour le compilo j'ai add ce return en attendant
    return(*buf);
}

int     main(void)
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