/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quote2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-banv <ede-banv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 12:10:47 by jdussert          #+#    #+#             */
/*   Updated: 2020/10/26 12:43:47 by ede-banv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	if_in_quote(int *d, int *s, int *i, char *str)
{
	if (str[*i] == '$')
		g_all.env = 1;
	if (str[*i] == '\\' && (str[*i + 1] == '\'' || str[*i + 1] == '\"'))
		*i += 2;
	if (str[*i] == '\"')
	{
		g_all.quote = 1;
		if (*d == 0 && *s == 0)
			(*d)++;
		else if (*d == 1 && *s == 0)
			(*d)--;
	}
	else if (str[*i] == '\'')
	{
		g_all.quote = 1;
		if (*s == 0 && *d == 0)
			(*s)++;
		else if (*s == 1 && *d == 0)
			(*s)--;
	}
}
