/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_id.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 16:33:36 by ede-banv          #+#    #+#             */
/*   Updated: 2020/10/19 12:35:32 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*command_id(char **comm, t_exit *exit)
{
    //identifier la commande selon le 1er token
    //free comm
    return(*comm);
}

char	*pipes_id(char **comm, t_exit *exit)
{
    //cette fonction va se servir de command id donc cest dans comand id que le debut de l'excecution des commandes va se faire
    //si ca se ser de command_id comm va etre free dans command id
    return (*comm);
}