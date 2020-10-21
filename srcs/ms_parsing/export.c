/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-banv <ede-banv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 14:20:42 by ede-banv          #+#    #+#             */
/*   Updated: 2020/10/21 14:46:12 by ede-banv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"



void	export_id(char **cmd, t_all *all)
{
	int 	i;
	t_lst	*tmp;
	char	*ptr;
	char	*w1;
	char	*w2;

	i = 0;
	if (!cmd[1])
	{
		//afficher en ordre alphabetique precede par "declare -x"
	}
	else
	{
		while (cmd[i])
		{
			if (check_errors())

			i++;
		}
	}

}