/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quote2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdussert <jdussert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 12:10:47 by idussert          #+#    #+#             */
/*   Updated: 2021/01/12 11:59:15 by jdussert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	if_in_quote(int *d, int *s, char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			g_all.env = 1;
		if (str[i] == '\\' && (str[i + 1] == '\'' || str[i + 1] == '\"'))
			i += 2;
		if (str[i] == '\"')
			while (str[++i] != '\"')
			{
				g_all.quote = 1;
				(*d)++;
			}
		else if (str[i] == '\'')
			while (str[++i] != '\'')
			{
				g_all.quote = 1;
				(*s)++;
			}
		i++;
	}
}
