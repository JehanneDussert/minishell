/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-banv <ede-banv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 13:27:08 by ede-banv          #+#    #+#             */
/*   Updated: 2020/10/20 14:48:56 by ede-banv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cd_chdir(char *path)
{
	if (chdir(path) == -1)
	{
		error_msg("cd", strerror(errno));
		errno = 0;
		//il fo catch l'erreur et changer le bail de $?
	}
}

char *cd_id(char **cmd)
{
	int		count;
	int		i;

	count = 0;
	ft_count_commands(&count, cmd);
	if (count == 1)
	{
		cd_chdir();//go to home (variable d'env)
	}
	else if (count > 1)
	{
		cd_chdir(cmd[1]);
	}
}