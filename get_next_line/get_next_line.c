/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-banv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 14:36:55 by ede-banv          #+#    #+#             */
/*   Updated: 2019/11/14 22:46:17 by ede-banv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_free_gnl(char **buf, char **stock, int i)
{
	if (*buf)
	{
		free(*buf);
		*buf = NULL;
	}
	if (i == 0)
	{
		if (*stock)
		{
			free(*stock);
			*stock = NULL;
		}
		return (0);
	}
	if (i == 1)
		return (1);
	if (*stock)
	{
		free(*stock);
		*stock = NULL;
	}
	return (-1);
}

char	*ft_restock(char **stock, int i)
{
	char	*tmp;

	if (!(tmp = ft_substr(*stock, i, ft_strlen(*stock))))
		return (NULL);
	free(*stock);
	*stock = NULL;
	if (!(*stock = ft_substr(tmp, 0, ft_strlen(tmp))))
	{
		free(tmp);
		tmp = NULL;
		return (NULL);
	}
	free(tmp);
	tmp = NULL;
	return (*stock);
}

int		ft_stock(char **line, char **stock, char **buf)
{
	int i;

	i = 0;
	if (*stock && ft_strchr(*stock, '\n'))
	{
		while ((*stock)[i] != '\n' && (*stock)[i])
			i++;
		if (!(*line = ft_substr(*stock, 0, i)))
			return (ft_free_gnl(buf, stock, -1));
		if (!(*stock = ft_restock(stock, i + 1)))
			return (ft_free_gnl(buf, stock, -1));
		return (ft_free_gnl(buf, stock, 1));
	}
	return (0);
}

int		ft_read_gnl(int fd, char **buf, char **stock, char **line)
{
	int red;

	while ((red = read(fd, *buf, BUFFER_SIZE)) >= 0)
	{
		buf[0][red] = '\0';
		if (!*stock)
		{
			if (!(*stock = ft_substr(*buf, 0, BUFFER_SIZE)))
				return (ft_free_gnl(buf, stock, -1));
		}
		else if (!(*stock = ft_noleak(stock, buf)))
			return (ft_free_gnl(buf, stock, -1));
		if (red == 0)
		{
			if (!(*line = ft_substr(*stock, 0, ft_strlen(*stock))))
				return (ft_free_gnl(buf, stock, -1));
			return (ft_free_gnl(buf, stock, 0));
		}
		if (ft_strchr(*stock, '\n'))
			return (ft_stock(line, stock, buf));
	}
	return (ft_free_gnl(buf, stock, -6));
}

int		get_next_line(int fd, char **line)
{
	static char	*stock;
	char		*buf;
	int			s;

	if (fd < 0 || BUFFER_SIZE < 1 || !line)
		return (-1);
	if (!(buf = malloc(sizeof(*buf) * (BUFFER_SIZE + 1))))
		return (-1);
	if ((s = ft_stock(line, &stock, &buf)) != 0)
		return (s);
	return (ft_read_gnl(fd, &buf, &stock, line));
}
