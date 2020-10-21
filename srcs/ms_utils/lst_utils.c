/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-banv <ede-banv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 12:27:04 by ede-banv          #+#    #+#             */
/*   Updated: 2020/10/21 14:47:36 by ede-banv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


t_lst	*ft_lstnew_ms(void *w1, void *w2)
{
	t_lst	*newelem;

	if (!(newelem = (t_lst *)malloc(sizeof(t_lst))))
		return (NULL);
	newelem->key = w1;
	newelem->content = w2;
	newelem->next = NULL;
	return (newelem);
}

t_lst	*ft_lstlast_ms(t_lst *lst)
{
	if (lst == NULL)
		return (lst);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back_ms(t_lst **alst, t_lst *new)
{
	if (new == NULL || alst == NULL)
		return ;
	if (*alst == NULL)
	{
		*alst = new;
		return ;
	}
	ft_lstlast_ms(*alst)->next = new;
}

void	lst_add_env(char **env, t_all *all)
{
	int	i;
	t_lst	*tmp;
	char	*w1;
	char	*w2;
	char	*ptr;

	i = 0;
	while(env && env[i])
	{
		if((ptr = ft_strchr(env[i], '=')))
		{
			*ptr = '\0';
			if (!(w1 = ft_strdup(env[i])))
				;//error malloc
			if (!(w2 = ft_strdup(ptr + 1)))
				;//error malloc
		}
		else //no = | is it necessaire?
		{
			if (!(w1 = ft_strdup(env[i])))
				;//error malloc
			w2 = NULL;
		}
		if(!(tmp = ft_lstnew_ms(w1, w2)))
			;//erreur malloc
		ft_lstadd_back_ms(&all->alst, tmp);
		i++;
	}
}
