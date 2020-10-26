/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quote2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdussert <jdussert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 12:10:47 by jdussert          #+#    #+#             */
/*   Updated: 2020/10/26 12:12:02 by jdussert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_init_quote(int *i, int *k, int *d, int *s)
{
	*i = 0;
	*k = 0;
	*d = 0;
	*s = 0;
}

void	if_in_quote(int *d, int *s, int *i, char *str)
{
	if (str[*i] == '\\' && (str[*i + 1] == '\'' || str[*i + 1] == '\"'))
		*i += 2;
	if (str[*i] == '\"')
	{
		if (*d == 0 && *s == 0)
			(*d)++;
		else if (*d == 1 && *s == 0)
			(*d)--;
	}
	else if (str[*i] == '\'')
	{
		if (*s == 0 && *d == 0)
			(*s)++;
		else if (*s == 1 && *d == 0)
			(*s)--;
	}
}
