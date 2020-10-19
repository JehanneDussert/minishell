/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 14:51:22 by ede-banv          #+#    #+#             */
/*   Updated: 2020/10/19 10:59:50 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//ecrire fonction qui va checker les erreurs de la ligne en debut de ft read, avant meme de split
//erreurs a checker:
//-double ; ou | (DONE: check_double)
//-| en debut ou fin de commande (DONE: ft_synta_error_ps)
//-; en debut de commande (DONE: ft_synta_error_ps)
//-chevrons en fin de commande
//-chevrons qui sont sep par ws)

/*
** Ps : pipe + semi colon
*/

int		ft_syntax_error_ps(char *str)
{
	char *tmp;
	int	len;
	int	res;

	res = 1;
	tmp = ft_strtrim(str, " ");
	len = ft_strlen(tmp);
	if (tmp[0] == ';' || tmp[0] == '|' || tmp[len] == '|')
		res = 0;
	free(tmp);
	tmp = NULL;
	return (res);
}

int		is_charset(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (c == charset[i])
			return (1);
	}
	return (0);
}

int		check_double(char *str, char *charset)
{
	int	i;
	int	c;

	i = 0;
	while (str[i])
	{
		c = 0;
		if (is_charset(str[i], charset))
		{
			c++;
			i++;
		}
		while (ft_iswhitespace(str[i]))
			i++;
		if (c == 1 && is_charset(str[i], charset))
			return (0);
		i++;
	}
	return (1);
}