/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   welcome_bye.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-banv <ede-banv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 17:16:59 by ede-banv          #+#    #+#             */
/*   Updated: 2020/10/21 12:29:33 by ede-banv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    welcomer(void) //font from http://patorjk.com/software/taag/#p=display&h=1&v=1&f=Banner3&t=Minishell
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

void	byebye(void)
{
	ft_putendl_fd("\nThank you for using our Minishell!", 1);
	ft_putendl_fd("___  _    ____     ___  _    ____ ", 1);
	ft_putendl_fd("| |_)\\ \\_/| |_     | |_)\\ \\_/| |_ ", 1);
	ft_putendl_fd("|_|_) |_| |_|__    |_|_) |_| |_|__ ", 1);
}