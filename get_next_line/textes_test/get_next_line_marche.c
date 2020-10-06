/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-banv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 23:54:20 by ede-banv          #+#    #+#             */
/*   Updated: 2019/11/12 16:34:50 by ede-banv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_free(char *buf, char *stock, int r)
{
	//	free(buf);
	if (r == 1)
		return (1);
	if (r == 0)
	{
		free(stock);
		return (0);
	}
	return (-1);
}

char	*ft_restock(char *stock, int i)
{
	char	*tmp;

	if (!(tmp = ft_substr(stock, i, ft_strlen(stock))))
		return (NULL);
	free(stock);
	if (!(stock = ft_substr(tmp, 0, ft_strlen(tmp))))
	{
		free (tmp);
		return (NULL);
		}
	free(tmp);
	return (stock);
}

int		ft_stock(char *line, char *stock)
{
	int i;

	i = 0;
	if (stock)
	{
		while (stock[i])
		{
			if (stock[i] == '\n')
			{
				if (!(line = ft_substr(stock, 0, i)))
					return (-1);
				if (!(stock = ft_restock(stock, i + 1)))
					return (-1);
				return (1);
			}
			i++;
		}
	}
	return (2);
}

int		get_next_line(int fd, char **line)
{
	static char	*stock;
	char		buf[BUFFER_SIZE + 1];
	int			red;
	int			i;
	int			s;

	i = 0;
	if (fd < 0 || BUFFER_SIZE < 1 || !line)
		return (-1);
	if (stock)
	{
		while (stock[i])
		{
			if (stock[i] == '\n')
			{
				if (!(*line = ft_substr(stock, 0, i)))
					return (ft_free(buf, stock, -1));
				if (!(stock = ft_restock(stock, i + 1)))
					return (ft_free(buf, stock, -1));
				return (ft_free(buf, stock, 1));
			}
			i++;
		}
	}
	i = 0;
	/*	if (stock)
		{
		s = ft_stock(*line, stock);
		if (s == -1)
		return (ft_free(buf, stock, -1));
		if (s == 1)
		return (ft_free(buf, stock, 1));
		}
*/	while ((red = read(fd, buf, BUFFER_SIZE)) >= 0)
	{
		buf[BUFFER_SIZE] = '\0';
		if (red == 0)
		{
			if (!(*line = ft_substr(stock, 0, ft_strlen(stock))))
				return (ft_free(buf, stock, -1));
			//	ft_bzero(stock, ft_strlen(stock));
			return (ft_free(buf, stock, 0));
		}
		if (!stock)
		{
			if (!(stock = ft_substr(buf, 0, BUFFER_SIZE + 1)))
				return (ft_free(buf, stock, -1));
		}
		else
			if (!(stock = ft_strjoin(stock, buf)))
				return (ft_free(buf, stock, -1));
		if (ft_strchr(buf, '\n'))
		{
			//			s = ft_stock(*line, stock);
			//			if (s == -1)
			//				return (ft_free(buf, stock, -1));
			//			if (s == 1)
			//				return (ft_free(buf, stock, 1));

			while (stock[i] != '\n' && stock[i])
				i++;
			if (!(*line = ft_substr(stock, 0, i)))
				return (ft_free(buf, stock, -1));
			if (!(stock = ft_restock(stock, i + 1))) //this should happen if and only if it's not the last line. find  a way to tell
				return (ft_free(buf, stock, -1));
			return (1);
		}
	}
	return (ft_free(buf, stock, -1));
}

//there is an excess in the end, possibly related to the way the stock in handled when called for the last time.
