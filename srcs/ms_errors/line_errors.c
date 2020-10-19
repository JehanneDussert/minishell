/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 14:51:22 by ede-banv          #+#    #+#             */
/*   Updated: 2020/10/19 11:50:03 by marvin           ###   ########.fr       */
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
	len = ft_strlen(tmp) - 1;
	if (tmp[0] == ';' || tmp[0] == '|' || tmp[len] == '|')
		res = 0;
	free(tmp);
	tmp = NULL;
	return (res);
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
		if ((s == 0 && d == 0) && str[i] != '>')
			return (0);
		else
			i++;
		if (s == 0 && d == 0 && skipspace(str, &i) && (str[i] == ';' || str[i] == '|'))
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

int		ft_check_errors_line(char *line)
{
	if (!check_double(line, ";|"))
		return(ft_syntax_error(line, "double"));
	if (!ft_syntax_error_ps(line))
		return(ft_syntax_error(line, "ps"));
	if (!check_chevrons(line))
		return(ft_syntax_error(line, "chevrons"));
	return(1);
}
