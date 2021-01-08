/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quote2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 12:10:47 by jdussert          #+#    #+#             */
/*   Updated: 2021/01/08 16:00:16 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//maybe creer un int *** dans all, qui va stocker les indices de ts les \(" ou ')") dans chaque mot
//et le nb de backslashs seront comptes lors du compte pr la creation desmots.
//puis il sra utilise ds la creation du char ** pour y inclure les caracteres backslashes
//option 2 : une fct qui dans chauqe mot compte les \ et rajoute le nb au compte des malloc des mots
//et ds tab_fill creer une condition avant if in quote qui va mettre le caractere saute ds le tab result

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
