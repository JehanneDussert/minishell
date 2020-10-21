/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-banv <ede-banv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 14:20:42 by ede-banv          #+#    #+#             */
/*   Updated: 2020/10/21 15:02:07 by ede-banv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		export_errors(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalpha(str[i]) && str[i] != '_')
			return (0);
		if (ft_isalpha(str[i]) || str[i] == '_')
			return (1);
		i++;
	}
	return (1);
}

void	export_id(char **cmd, t_all *all)
{
	int 	i;

	i = 0;
	if (!cmd[1])
	{
		//while ()
	}
	else
	{
		while (cmd[i])
		{
			if (export_errors(cmd[i]))
				lst_add_env(&cmd[i], all);
			i++;
		}
	}

}