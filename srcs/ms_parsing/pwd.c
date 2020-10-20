/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-banv <ede-banv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 15:18:43 by ede-banv          #+#    #+#             */
/*   Updated: 2020/10/20 16:33:46 by ede-banv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	pwd_id(char **cmd)
{
	char	*buf;

	if (!(buf = malloc(sizeof(buf) * 1024)))
		;//erreur de malloc
	if (!(getcwd(buf, 1024)))
	{
		error_msg("pwd", strerror(errno));
		errno = 0;
		//changer la variable $?
	}
}