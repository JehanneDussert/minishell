/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_fcts.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-banv <ede-banv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 12:05:33 by ede-banv          #+#    #+#             */
/*   Updated: 2020/10/26 12:05:33 by ede-banv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_read(char ***buf, char **line)
{
	if (!line && !buf)
		return ;
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
