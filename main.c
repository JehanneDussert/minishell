/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdussert <jdussert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 14:15:17 by jdussert          #+#    #+#             */
/*   Updated: 2021/01/29 14:25:00 by jdussert         ###   ########.fr       */
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
	ft_check_quotes(&commands, all);
	if (!ft_check_redirection(commands, all, "><"))
		return (free_read(&commands, NULL));
	if (res == 0 && commands[0] && !commands[1] &&
	!(command_id((ft_split_quote(commands[0], "\t\n\r\v \f")), all)))
		res = -1;
	if (res == 0 && commands[0] && commands[1])
		if (!(if_pipes(commands, all, &res)))
			return ;
	ft_redirection_out(&g_all);
	if (res == -1)
	{
		all->err = 1;
		ft_malloc_error(NULL);
		return (free_read(&commands, NULL));
	}
	free_read(&commands, NULL);
}

char	*read_checks(t_all *all, int *count, char ***buf, char **line)
{
	int		i;

	i = 0;
	if (!ft_check_sep(line) || !(ft_check_errors_line(line[0], all)))
	{
		free_read(buf, line);
		return (NULL);
	}
	*buf = ft_split_quote(line[0], ";");
	if (*buf)
	{
		ft_putendl_fd("there is buf", 2);
		ft_count_commands(count, *buf);
	}
	else
	{
		ft_putendl_fd("free", 2);
		free_read(buf, line);
		all->err = 1;
		ft_malloc_error(NULL);
		return (NULL);
	}
	while ((*buf)[i] && i != *count)
	{
		ft_putendl_fd("bef command exec", 2);
		ft_command_exec((*buf)[i++], all);
		ft_putendl_fd("after command exec", 2);
	}
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
			ft_putendl_fd("there is 0", 2);
			return (0);
		}
		n = get_next_line(1, &line_d);
		*line = ft_strjoin_free(*line, line_d, 3);
		ft_putendl_fd("read d", 2);
		if (!(read_checks(all, &count, &buf, line)))
		{
			ft_putendl_fd("2", 2);
			return (2);
		}
	}
	ft_putendl_fd("out read d", 2);
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
		if (!(read_checks(all, &count, &buf, &line)))
			return ("error");
	if ((d = read_d(all, &line, buf, n)) != 1)
		return (d == 0 ? NULL : "error");
	if (!buf && line)
	{
		free_read(NULL, &line);
		return (NULL);
	}
	if (buf)
		free_read(&buf, &line);
	if (all->exit->e != -1 || all->exit->d == 1)
		return (NULL);
	ft_putendl_fd("out ft_read", 2);
	return ("done");
}

int		main(void)
{
	int		x;
	char	*tmp;

	x = 1;
	welcomer();
	ft_bzero(&g_all, sizeof(t_all));
	ft_init_all(&g_all);
	signal(SIGINT, c_handler);
	signal(SIGQUIT, d_handler);
	g_all.prog = 0;
	tmp = NULL;
	while (x > 0)
	{
		ft_putstr_fd("~:", 1);
		if ((tmp = ft_read(&g_all)) == NULL)
			x = (g_all.exit->e == -1 ? -1 : 0);
	}
	if (x == 0)
		exit(g_all.exit->e);
	free_all(&g_all);
	byebye();
	return (1);
}
