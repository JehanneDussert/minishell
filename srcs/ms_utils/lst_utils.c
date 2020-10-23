/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 12:27:04 by ede-banv          #+#    #+#             */
/*   Updated: 2020/10/23 15:03:49 by marvin           ###   ########.fr       */
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
	newelem->tmp = 0;
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
	if (alst && *alst == NULL)
	{
		*alst = new;
		return ;
	}
	ft_lstlast_ms(*alst)->next = new;
}

void	ft_lstdelone_ms(t_lst *lst, void (*del)(void *))
{
	if (lst && del)
	{
		del(lst->content);
		del(lst->key);
		free(lst);
	}
}
