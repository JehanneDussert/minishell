/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdussert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 15:55:43 by jdussert          #+#    #+#             */
/*   Updated: 2019/11/19 10:20:29 by jdussert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "get_next_line.h"
# include <fcntl.h>

int	main(void)
{
	char	*line;
	int		fd;
	int		n;

	fd = open("long_texte.txt", O_RDONLY);
	n = get_next_line(fd, &line);
	while (n == 1)
	{
		printf("%d:%s\n", n, line);
		free(line);
		n = get_next_line(fd, &line);
	}
	printf("%d:%s\n", n, line);
	free(line);
	// Pour gerer les leaks //
//	while (1);
	return (0);
}
