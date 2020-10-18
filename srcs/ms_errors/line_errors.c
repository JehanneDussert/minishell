/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdussert <jdussert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 14:51:22 by ede-banv          #+#    #+#             */
/*   Updated: 2020/10/16 17:40:20 by jdussert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//ecrire fonction qui va checker les erreurs de la ligne en debut de ft read, avant meme de split
//erreurs a checker:
//-double ; ou | (DONE: check_double)
//-| en debut ou fin de commande
//-; en debut de commande
//-chevrons en fin de commande
//-chevrons qui sont sep par ws)

// fonction pour gerer error pipe + ;

int		ft_check_pipes_commas(char *str)
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