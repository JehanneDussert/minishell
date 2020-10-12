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

char    **ft_read()
{
    char    *line;
    char    **comd;
    int     n;
    int     i;

    n = 1;
    i = 0;
    while ((n = get_next_line(1, &line)) == 1)
    {
        // Peut etre : prevoir 1 struct qui permette de compter le nb de cmd 
        // + sous struct[nb_cmd] avec la comd et le pipe s'il existe
        comd = ft_split(line, ';'); 
        // il faut prevoir le cas ou il y a des "" par ex : echo ";" 
        while (comd[i])
        {
            printf("this is command %d - %s\n", i, comd[i]);
            i++;
        }
    }
    return(comd);
}

int     main()
{
    int     x;
    char    **tmp;

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
