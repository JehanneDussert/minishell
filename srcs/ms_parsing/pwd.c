/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdussert <jdussert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 15:18:43 by ede-banv          #+#    #+#             */
/*   Updated: 2020/10/22 17:29:41 by jdussert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	pwd_id()
{
	char	*buf;

	if (!(buf = ft_calloc(sizeof(buf), 1024)))
	{
		ft_malloc_error("pwd");
		return ;
	}
	if (!(getcwd(buf, 1024)))
	{
		error_msg("pwd", strerror(errno));
		errno = 0;
		//changer la variable $?
	}
	ft_putendl_fd(buf, 1);
	ft_free((void **)&buf);
}//mettre $? a 0