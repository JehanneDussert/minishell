/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 14:51:22 by ede-banv          #+#    #+#             */
/*   Updated: 2021/02/01 09:37:09 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_error_ps(char *str)
{
	char	*tmp;
	int		len;
	int		res;

	res = 1;
	tmp = ft_strtrim(str, " ");
	len = ft_strlen(tmp) - 1;
	if (len >= 0 && (tmp[0] == ';' || tmp[0] == '|'))
		res = 0;
	ft_free((void **)&tmp);
	return (res);
}

int		ft_quote_error(char *str)
{
	int	i;
	int	d;
	int s;

	i = 0;
	d = 0;
	s = 0;
	while (str[i])
	{
		if (str[i] == '\"' && s % 2)
			d += 2;
		else if (str[i] == '\"' && (i == 0 || ft_check_bs(str, i - 1)))
			d++;
		else if (str[i] == '\'' && d % 2)
			s += 2;
		else if (str[i] == '\'')
			s++;
		i++;
	}
	if (d % 2 || s % 2)
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

	ft_init_quote(&i, &s, &d, &c);
	while (str[i])
	{
		if_in_quote(&d, &s, str);
		if (is_charset(str[i], "><") && i > 0 && str[i - 1] == '\\')
		{
			if (str[i + 1] == '\0')
				return (1);
		}
		else if (c == 0 && (s == 0 && d == 0) && is_charset(str[i], "><"))
		{
			i++;
			c++;
		}
		if ((s == 0 && d == 0) && !check_chevrons_cdts(str, &i, &c))
			return (0);
		i++;
	}
	return (1);
}

int		check_double(char *str, char *charset)
{
	int	i;
	int	c;

	i = 0;
	while (str[i++])
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
