/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-banv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 14:32:22 by ede-banv          #+#    #+#             */
/*   Updated: 2019/11/07 12:48:22 by ede-banv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_free(char *buf, char *stock, int r)
{
	free(buf);
	if (r == 1)
		return (1);
	if (r == 0)
	{
		free(stock);
		return (0);
	}
	return (-1);
}
/*
char	*ft_fill_line(char *stock, char *line)
{
	int i;

	i = 0;
	while (stock[i] && stock[i] == '\n')
		i++;
	if (!(line = ft_substr(stock, 0, i + 1)))
		return (NULL);
	stock = &stock[i + 1];
	return (stock);
}
*/
int		get_next_line(int fd, char **line)
{
	char	*buf;
	static char	*stock = "\0";
	int		red;
	size_t		i;

	i = 0;
	if (fd < 0 || BUFFER_SIZE < 1 || !line)
		return (-1);
	if (!(buf = malloc(sizeof(*buf) * (BUFFER_SIZE + 1))))
		return (ft_free(buf, stock,  -1));	
	if (!(*line = malloc(sizeof(*line) * BUFFER_SIZE)))
		return (ft_free(buf, stock, -1));
	if (stock)
	{
		while (stock && stock[i])
		{
			if (stock[i] == '\n')
			{
				if (!(line[0] = malloc(sizeof(*line) * (i + 1))))
					return (ft_free(buf, stock, -1));
				ft_memcpy(line[0], stock, i);
				line[0][i] = '\0';
				stock = ft_substr(stock, i + 1, ft_strlen(&stock[i]));//proteger
				return (ft_free(buf, stock, 1));
			}
		i++;
		}
		if (!(*line = ft_strjoin(*line, stock)))
			return (ft_free(buf, stock, -1));
	}
/*	while ((red = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[BUFFER_SIZE] = '\0';
		if (!(stock = ft_strjoin(stock, buf)))
			return (ft_free(buf, stock, -1));
		if (ft_strchr(stock, '\n'))
		{
			if (!(stock = ft_fill_line(stock, *line)))
				return (ft_free(buf, stock, -4));
			printf("%s", line[0]);
			if (ft_strchr(line[0], '\n'))
				return (ft_free(buf, stock, 1));
			if (!ft_strchr(*line, '\n'))
				return (ft_free(buf, stock, 0));
		}
	}
*/	while ((red = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[BUFFER_SIZE] = '\0';
		if (!(*line = ft_strjoin(*line, buf)))
			return (ft_free(buf, stock, -1));
		if (ft_strchr(buf, '\n'))
		{
			stock = ft_substr(ft_strchr(line[0], '\n') + 1, 0, BUFFER_SIZE);//proteger
			ft_bzero(ft_strchr(line[0], '\n'), ft_strlen(line[0]));
			return (ft_free(buf, stock, 1));
		}
	}
	return (ft_free(buf, stock, 0));
}

int    main(void)
{
    int    fd = open("text.txt", O_RDONLY);
    char    **line;
    int n = 1;
	while (n == 1)
	{
		n = get_next_line(fd, line);
		printf("%d- ", n);
    	printf("%s\n", line[0]);
	}
}

//join buf et stock, puis s'il y a \n (strchr), fct qui fill line avec substr jusqu'a l'indice du /n dans stock. PUIS deplacement de pointer de stsock pour enlever la 1ere ligne. tu mets tout dans ton stock et quand red = 0. puis tu regardes stock. puis tu regardes s'il y a /n dans line return 1 sinon return 0. (strchr).
