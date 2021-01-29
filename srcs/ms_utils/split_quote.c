/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 17:43:38 by ede-banv          #+#    #+#             */
/*   Updated: 2021/01/29 10:46:44 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		is_a_sep(char str, char *seps)
{
	int i;

	i = 0;
	while (seps[i])
	{
		if (seps[i] == str && seps[i])
			return (1);
		i++;
	}
	return (0);
}

int		word_count(char *str, char *charset)
{
	int	i;
	int	w;
	int	d;
	int	s;

	i = 0;
	w = 0;
	d = 0;
	s = 0;
	while (str && str[i])
	{
		while (d == 0 && s == 0 && is_a_sep(str[i], charset) && str[i])
			i++;
		if (((d == 1 || s == 1) || !(is_a_sep(str[i], charset))) && str[i])
			w++;
		while (((d == 1 || s == 1) || !(is_a_sep(str[i], charset))) && str[i])
			i++;
	}
	return (w + 1);
}

int		malloc_w_len(char *str, char *charset, char **result)
{
	int i;
	int k;
	int len;
	int	d;
	int	s;

	ft_init_quote(&i, &k, &d, &s);
	while (str && str[i])
	{
		while (d == 0 && s == 0 && is_a_sep(str[i], charset) && str[i])
			i++;
		len = 0;
		while (((d == 1 || s == 1) || !(is_a_sep(str[i], charset))) && str[i])
		{
			i++;
			len++;
		}
		if (!(is_a_sep(str[i - 1], charset)) && str[i - 1])
			if (!(result[k++] = malloc(sizeof(char) * (len + 1))))
				return (0);
	}
	result[k] = NULL;
	return (1);
}

char	**tab_fill(char *str, char *charset, char **result)
{
	int i;
	int k;
	int l;
	int	d;
	int	s;

	i = 0;
	k = 0;
	d = 0;
	s = 0;
	while (str && str[i])
	{
		while (d == 0 && s == 0 && is_a_sep(str[i], charset) && str[i])
			i++;
		l = 0;
		while (((d == 1 || s == 1) || !(is_a_sep(str[i], charset))) && str[i])
			result[k][l++] = str[i++];
		if (!(is_a_sep(str[i - 1], charset)) && str[i - 1])
			result[k++][l] = '\0';
	}
	return (result);
}

char	**ft_split_quote(char *str, char *charset)
{
	char **result;

	if (!(result = malloc(sizeof(char *) * word_count(str, charset))))
		return (NULL);
	if (malloc_w_len(str, charset, result))
		return (tab_fill(str, charset, result));
	else
		return (NULL);
}
