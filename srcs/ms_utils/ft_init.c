/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-banv <ede-banv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 11:17:46 by ede-banv          #+#    #+#             */
/*   Updated: 2020/10/21 12:25:25 by ede-banv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"



void	create_list(t_all *all)
{
	int	i;
	t_lst	*tmp;
	char	*w1;
	char	*w2;
	extern char	**environ;

	i = 0;

	while(environ[i])
	{
		if(!(tmp = ft_lstnew(environ[i], ft_strlen(environ[i]))))
			;//erreur malloc
		ft_lstadd_back(&all->alst, tmp);
		i++;
	}
}

void	ft_init_all(t_all *all)
{
	if (!(all->exit = ft_calloc(sizeof(t_exit), 1)))
		;
	create_list(all);
}