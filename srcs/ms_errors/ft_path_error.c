/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehannedussert <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 17:26:23 by jehannedu         #+#    #+#             */
/*   Updated: 2020/12/29 17:26:24 by jehannedu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_path_error(t_all *all, char **comm)
{
	all->err = 1;
	return (ft_malloc_error(comm[0]));
}
