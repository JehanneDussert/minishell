/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_splits.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehannedussert <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 16:58:50 by jehannedu         #+#    #+#             */
/*   Updated: 2020/12/29 16:58:57 by jehannedu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_read(char ***buf, char **line)
{
	if (*line)
		ft_free((void *)line);
	if (*buf)
	{
		while (**buf)
		{
			ft_free((void *)buf);
			(**buf)++;
		}
		ft_free((void *)buf);
	}
}
