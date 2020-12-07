/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 14:15:17 by jdussert          #+#    #+#             */
/*   Updated: 2020/11/27 16:10:49 by user42           ###   ########.fr       */
=======
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 14:15:17 by jdussert          #+#    #+#             */
/*   Updated: 2020/10/30 17:04:13 by marvin           ###   ########.fr       */
>>>>>>> 23288b1f787ad4ab994c291e6126d9dc150d2697
/*                                                                            */
/* ************************************************************************** */

#include "srcs/includes/minishell.h"

char	*if_pipes(char **commands, t_all *all, int *res)
{
	int		count;
	int		i;

	i = 0;
	count = 0;
	ft_count_commands(&count, commands);
	if (!(all->cmd = malloc(sizeof(t_cmd) * (count + 1))))
		*res = -1;
	all->cmd[count].cmd = NULL;
	while (*res == 0 && all->cmd[i].cmd)
	{
		if (!(all->cmd[i].cmd = ft_split_quote(commands[i],
		"\t\n\r\v \f")))
		{
			all->err = 1;
			ft_malloc_error(NULL);
			free_read(&commands, NULL);
			free_commands(all);
			return (NULL);
		}
		ft_free((void **)&commands[i]);
		i++;
	}
	pipes_id(all);
	ft_free((void **)&all->cmd);
	return ("done");
}

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

char	*ft_read(t_all *all)
{
	char	*line;
<<<<<<< HEAD
	char	*line_d;
	char	**buf;
	int		count;
	int		n;
=======
	char	**buf;
	int		count;
>>>>>>> 23288b1f787ad4ab994c291e6126d9dc150d2697

	count = 0;
	buf = NULL;
	line = NULL;
<<<<<<< HEAD
	if ((n = get_next_line(1, &line)) == 1)
		if (!(read_checks(all, &count, &buf, line)))
			return ("error");
	while (n == 0)
	{
		if (line[0] == '\0')
		{
			ft_free((void **)&line);
			return (NULL);
		}
		n = get_next_line(1, &line_d);
		line = ft_strjoin_free(line, line_d, 3);
		if (!(read_checks(all, &count, &buf, line)))
			return ("error");
=======
	if ((get_next_line(1, &line)) == 1)
		if (!(read_checks(all, &count, &buf, line)))
			return ("error");
	if (!buf)
	{
		free_read(NULL, &line);
		return (NULL);
>>>>>>> 23288b1f787ad4ab994c291e6126d9dc150d2697
	}
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
	tmp = NULL;
	while (x != 0)
	{
		dup2(all.fd_copy, 1);
		close(all.fd_copy);
		ft_putstr_fd("~:", 1);
		if ((tmp = ft_read(&all)) == NULL)
			x = 0;
	}
	free_all(&all);
	byebye();
	return (1);
}
