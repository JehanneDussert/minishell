/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdussert <jdussert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 14:51:22 by ede-banv          #+#    #+#             */
/*   Updated: 2020/10/22 17:11:19 by jdussert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//ecrire fonction qui va checker les erreurs de la ligne en debut de ft read, avant meme de split
//erreurs a checker:
//-double ; ou | (DONE: check_double)
//-| en debut ou fin de commande (DONE: ft_synta_error_ps)
//-; en debut de commande (DONE: ft_synta_error_ps)
//-2 chevrons en fin de commande (DONE : check_chevrons)
//-2 chevrons qui sont sep par ws) (DONE : check_chevrons)
//- <, > doivent marcher
//- check si les quotes sont fermes

/*
** Ps : pipe + semi colon
*/

int		ft_error_ps(char *str)
{
	char *tmp;
	int	len;
	int	res;

	res = 1;
	tmp = ft_strtrim(str, " ");
	len = ft_strlen(tmp) - 1;
	if (tmp[0] == ';' || tmp[0] == '|' || tmp[len] == '|')
		res = 0;
	ft_free((void *)&tmp);
	return (res);
}

int		ft_quote_error(char *str)
{
	int	i;
	int	q;
	int c;

	i = 0;
	q = 0;
	c = 0;
	while (str[i])
	{
		if (str[i] == '\"' && (i == 0 || str[i - 1] != '\\'))
			q++;
		else if (str[i] == '\'' && q % 2 != 0)
			c += 2;
		else if (str[i] == '\'')
			c++;
		i++;
	}
	if (q % 2 != 0 || c % 2 != 0)
		return (0);
	return (1);
}


int		is_charset(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}
int		check_chevrons(char *str)
{
	int	i;
	int	s;
	int	d;
	int	c;

	i = 0;
	s = 0;
	d = 0;
	c = 0;
	while (str[i])
	{
		if_in_quote(&d, &s, &i, str);
		if (c == 0 && (s == 0 && d == 0) && is_charset(str[i], "><"))
		{
			i++;
			c++;
		}
		else if ((s == 0 && d == 0) && c > 0 && ((str[i] == '>' && str[i - 1] != '>')
			|| (str[i] == '<' && str[i - 1] != '<')))
				return (0);
		if (s == 0 && d == 0 && i > 0 && str[i - 1] == '>' && skipspace(str, &i) &&
			(str[i] == ';' || str[i] == '|' || str[i] == '\0'))
			return (0);
		i++;
	}
	return (1);
}

int		check_double(char *str, char *charset)
{
	int	i;
	int	c;

	i = -1;
	while (str[++i])
	{
		c = 0;
		if (!is_charset(str[i], charset))
			continue ;
		if (is_charset(str[i], charset))
		{
			c++;
			i++;
		}
		while (ft_iswhitespace(str[i]))
			i++;
		if (c == 1 && is_charset(str[i], charset))
			return (0);
	}
	return (1);
}
