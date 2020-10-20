/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdussert <jdussert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 14:51:22 by ede-banv          #+#    #+#             */
/*   Updated: 2020/10/20 16:49:26 by jdussert         ###   ########.fr       */
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

int		ft_syntax_error_ps(char *str)
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

	// checker si quote sont fermees
	// si \" on considere qu'il n'y a pas de "
	// si \' ca passe
	// si " ' " ok
	// si " " " non
	// les "" marchent tjrs par paires =/= les '

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
		if (str[i] == '"' && (i == 0 || str[i - 1] != 92))
			q++;
		else if (str[i] == 39 && q % 2 != 0)
			c += 2;
		else if (str[i] == 39)
			c++;
		i++;
	}
	if (q % 2 != 0 || c % 2 != 0)
		return (0);
	return (1);
}

int		check_chevrons(char *str)
{
	int	i;
	int	s;
	int	d;

	i = 0;
	s = 0;
	d = 0;
	while (str[i])
	{
		if_in_quote(&d, &s, &i, str);
		if ((s == 0 && d == 0) && str[i] == '>')
			i++;
		if ((s == 0 && d == 0) && i > 0 && str[i - 1] == '>' && str[i] != '>')
			return (0);
		else
			i++;
		if (s == 0 && d == 0 && i > 0 && str[i - 1] == '>' && skipspace(str, &i) && (str[i] == ';' || str[i] == '|' || str[i] == '\0'))
			return (0);
		i++;
	}
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

int		ft_check_errors_line(char *line)
{
	if (!check_double(line, ";|"))
		return(ft_syntax_error(line, "double"));
	else if (!ft_syntax_error_ps(line))
		return(ft_syntax_error(line, "ps"));
	else if (!ft_quote_error(line))
		return(ft_syntax_error(line, "quote"));
	// segfault here
	//else if (!check_chevrons(line))
	//	return(ft_syntax_error(line, "chevrons"));
	return(1);
}
