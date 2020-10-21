/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-banv <ede-banv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 11:17:46 by ede-banv          #+#    #+#             */
/*   Updated: 2020/10/21 11:37:25 by ede-banv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	create_list(t_all *all)
{
	int	i;
	t_list	*tmp;
	char	*tmp_word;
	extern char	**environ;

	i = 0;

	while(environ[i])
	{
		if(!(tmp_word = ft_strjoin("declare -x ", environ[i])))
			;//erreur malloc
		if(!(tmp = ft_lstnew(tmp_word, ft_strlen(tmp_word))))
			;//erreur malloc
		ft_lstadd_back(&all->alst, tmp);
		ft_free(tmp_word);
		i++;
	}
}

void	ft_init_all(t_all *all)
{
	all->exit->e = 0;
	all->exit->d = 0;
	create_list(all);
}