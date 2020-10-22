/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_fcts.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdussert <jdussert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 17:12:46 by jdussert          #+#    #+#             */
/*   Updated: 2020/10/22 17:12:46 by jdussert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_read(char ***buf, char **line)
{
	if (!line && !buf)
		return;
	if (line && *line)
		ft_free((void *)line);
	if (buf && *buf)
	{
		while (**buf)
		{
			ft_free((void *)buf);
			(**buf)++;
		}
		ft_free((void *)buf);
	}
}