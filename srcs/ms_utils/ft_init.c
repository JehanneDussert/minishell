/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-banv <ede-banv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 11:17:46 by ede-banv          #+#    #+#             */
/*   Updated: 2020/10/22 18:31:56 by ede-banv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	create_list(t_all *all)
{
	extern char	**environ;

	lst_add_env(environ, all);
}

void	ft_init_all(t_all *all)
{
	if (!(all->exit = ft_calloc(sizeof(t_exit), 1)))
	{
		ft_malloc_error(NULL);
		return ;
	}
	all->err = 0;
	create_list(all);
}