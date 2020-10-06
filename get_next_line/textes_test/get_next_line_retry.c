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

char	*ft_restock(char *stock, int i)
{
	char	*tmp;

	if (!(tmp = ft_substr(stock, i, ft_strlen(stock))))
		return (NULL);
	free(stock);
	if (!(stock = ft_substr(tmp, 0, ft_strlen(tmp))))
		return (NULL);
	free(tmp);
	return (stock);
}

int		get_next_line(int fd, char **line)
{
	static char	*stock;
	char		*buf;
	int			red;
	int			i;

	i = 0;
	if (fd < 0 || BUFFER_SIZE < 1 || !line)
		return (-1);
	if (!(buf = malloc(sizeof(*buf) * (BUFFER_SIZE + 1))))
		return (ft_free(buf, stock, -1));
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
	while ((red = read(fd, buf, BUFFER_SIZE)) >= 0)
	{
		buf[BUFFER_SIZE] = '\0';
		if (red == 0)
		{
			ft_bzero(*line, ft_strlen(*line));
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
			while (stock[i] != '\n')
				i++;
			if (!(*line = ft_substr(stock, 0, i)))
				return (ft_free(buf, stock, -1));
			if (red == BUFFER_SIZE)
			{
				if (!(stock = ft_restock(stock, i + 1)))
					return (ft_free(buf, stock, -1));
			}
			return (ft_free(buf, stock, 1));
		}
	}
	return (ft_free(buf, stock, 1));
}
