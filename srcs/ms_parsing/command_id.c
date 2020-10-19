/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_id.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 16:33:36 by ede-banv          #+#    #+#             */
/*   Updated: 2020/10/19 15:06:52 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*command_id(char **comm, t_exit *exit)//puisque je fais read 
{
    //identifier la commande selon le 1er token
    free_read(&comm, NULL);
    return("done");
}

char	*pipes_id(t_cmd **cmd, t_exit *exit)
{
    //cette fonction va se servir de command id donc cest dans comand id que le debut de l'excecution des commandes va se faire
    //si ca se sert de comm_id
    return ("done");
}