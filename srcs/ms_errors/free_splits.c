/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_splits.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 13:49:36 by marvin            #+#    #+#             */
/*   Updated: 2020/10/19 13:49:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_read(char ***buf, char **line)
{
	if (*line)
		ft_free(line);
	if (*buf)
	{
		while (**buf)
		{
			ft_free(**buf);
			(**buf)++;
		}
		ft_free(*buf);
	}
}