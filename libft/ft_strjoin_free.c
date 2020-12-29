/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-banv <ede-banv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 14:00:11 by ede-banv          #+#    #+#             */
/*   Updated: 2020/10/29 14:02:12 by ede-banv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** FT_STRJOIN_FREE
** si to_free = 0, rien n'est free
** si to_free = 1, s1 est free
** si to_free = 2, s2 est free
** si to_free = 3, s1 et s2 sont free
*/

char	*ft_strjoin_free(char const *s1, char const *s2, int to_free)
{
	char *res;

	res = ft_strjoin(s1, s2);
	if (to_free & 1)
		ft_free((void **)&s1);
	if (to_free & 2)
		ft_free((void **)&s2);
	return (res);
}
