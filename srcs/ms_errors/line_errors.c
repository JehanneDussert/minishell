/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdussert <jdussert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 14:51:22 by ede-banv          #+#    #+#             */
/*   Updated: 2021/01/19 15:41:17 by jdussert         ###   ########.fr       */
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
		else if (str[i] == '\"' && ft_check_bs(str, i - 1))
			d++;
		else if (str[i] == '\'' && d % 2)
			s += 2;
		else if (str[i] == '\'' && ft_check_bs(str, i - 1))
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
			i++;
			if (str[i] == '\0')
				return (1);
		}
		else if (c == 0 && (s == 0 && d == 0) && is_charset(str[i], "><"))
		{
			i++;
			c++;
		}
		if ((s == 0 && d == 0) && c > 0 && (str[i] == '<' && str[i - 1] == '>'))
		{
			ft_putnbr_fd(1, 2);
			return (0);
		}
		if ((s == 0 && d == 0) && c > 0 && (str[i - 1] == '<' && str[i] == ' '
			&& skipspace(str, &i) && str[i] == '>'))
		{
			ft_putnbr_fd(2, 2);
			return (0);
		}
		if (s == 0 && d == 0 && i > 0 && str[i - 1] == '>' && skipspace(str, &i)
		&& (str[i] == ';' || str[i] == '|' || str[i] == '\0'))
		{
			ft_putnbr_fd(3, 2);
			return (0);
		}
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
