/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-banv <ede-banv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 22:35:42 by ede-banv          #+#    #+#             */
/*   Updated: 2020/02/28 17:31:54 by ede-banv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content, int len)
{
	t_list	*newelem;

	if (!(newelem = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	newelem->content = content;
	newelem->nb = len;
	newelem->next = NULL;
	return (newelem);
}
