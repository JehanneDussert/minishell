/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 14:15:17 by jdussert          #+#    #+#             */
/*   Updated: 2020/11/28 14:11:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "srcs/includes/minishell.h"

void	ft_command_exec(char *comm, t_all *all)
{
	char	**commands;
	int		res;

	res = 0;
	if (!(commands = ft_split_quote(comm, "|")))
		res = -1;
	if (res == 0 && !commands[1] &&
	!(command_id((ft_split_quote(commands[0], "\t\n\r\v \f")), all, 1)))
		res = -1;
	if (res == 0 && commands[1])
		if (!(if_pipes(commands, all, &res)))
			return ;
	if (res == -1)
	{
		all->err = 1;
		ft_malloc_error(NULL);
		free_read(&commands, NULL);
		return ;
	}
	free_read(&commands, NULL);
}

char	*read_checks(t_all *all, int *count, char ***buf, char *line)
{
	int		i;

	i = 0;
	if (!(ft_check_errors_line(line, all)))
	{
		free_read(buf, &line);
		return (NULL);
	}
	*buf = ft_split_quote(line, ";");
	if (*buf)
		ft_count_commands(count, *buf);
	else
	{
		free_read(buf, &line);
		all->err = 1;
		ft_malloc_error(NULL);
		return (NULL);
	}
	while (i != *count)
		ft_command_exec((*buf)[i++], all);
	return ("done");
}

int		read_d(t_all *all, char **line, char **buf, int n)
{
	int		count;
	char	*line_d;

	while (n == 0)
	{
		if (*line[0] == '\0')
		{
			ft_free((void **)line);
			return (0);
		}
		n = get_next_line(1, &line_d);
		*line = ft_strjoin_free(*line, line_d, 3);
		if (!(read_checks(all, &count, &buf, *line)))
			return (2);
	}
	return (1);
}

char	*ft_read(t_all *all)
{
	char	*line;
	char	**buf;
	int		count;
	int		n;
	int		d;

	count = 0;
	buf = NULL;
	line = NULL;
	if ((n = get_next_line(1, &line)) == 1)
		if (!(read_checks(all, &count, &buf, line)))
			return ("error");
	if ((d = read_d(all, &line, buf, n)) != 1)
		return (d == 0 ? NULL : "error");
	free_read(&buf, &line);
	if (all->exit->e == 1 || all->exit->d == 1)
		return (NULL);
	return ("done");
}

int		main(void)
{
	int		x;
	char	*tmp;

	x = 1;
	welcomer();
	ft_bzero(&all, sizeof(t_all));
	ft_init_all(&all);
	signal(SIGINT, c_handler);
	signal(SIGQUIT, d_handler);
	all.prog = 0;
	while (x != 0)
	{
		ft_putstr_fd("~:", 1);
		tmp = ft_read(&all);
		if (tmp == NULL)
			x = 0;
	}
	free_all(&all);
	byebye();
	return (1);
}
