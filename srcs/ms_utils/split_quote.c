/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-banv <ede-banv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 17:43:38 by ede-banv          #+#    #+#             */
/*   Updated: 2020/10/13 17:49:11 by ede-banv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int		w_count(char *str, char *charset)
{
	int i;
	int w;

	i = 0;
	w = 0;
	while (str[i])
	{
		while ((is_a_sep(str[i], charset)) && str[i])
			i++;
		if (!(is_a_sep(str[i], charset)) && str[i])
			w++;
		while (!(is_a_sep(str[i], charset)) && str[i])
			i++;
	}
	return (w + 1);
}

int		malloc_w_len(char *str, char *charset, char **result)
{
	int i;
	int k;
	int len;

	i = 0;
	k = 0;
	while (str[i])
	{
		while (is_a_sep(str[i], charset) && str[i])
			i++;
		len = 0;
		while (!(is_a_sep(str[i], charset)) && str[i])
		{
			i++;
			len++;
		}
		if (!(is_a_sep(str[i - 1], charset)) && str[i - 1])
			if (!(result[k++] = malloc(sizeof(char) * (len + 1))))
				return (0);
	}
	if (!(result[k] = malloc(sizeof(NULL))))
		return (0);
	return (1);
}

char	**tab_fill(char *str, char *charset, char **result)
{
	int i;
	int k;
	int l;

	i = 0;
	k = 0;
	while (str[i])
	{
		while ((is_a_sep(str[i], charset)) && str[i])
			i++;
		l = 0;
		while (!is_a_sep(str[i], charset) && str[i])
			result[k][l++] = str[i++];
		if (!(is_a_sep(str[i - 1], charset)) && str[i - 1])
			result[k++][l] = '\0';
	}
	result[k] = NULL;
	return (result);
}

char	**ft_split_quote(char *str, char *charset)
{
	char **result;

	if (!(result = malloc(sizeof(char *) * w_count(str, charset))))
		return (0);
	if (malloc_w_len(str, charset, result))
		return (tab_fill(str, charset, result));
	else
		return (NULL);
}