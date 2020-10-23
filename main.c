/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 14:23:51 by marvin            #+#    #+#             */
/*   Updated: 2020/10/23 14:23:51 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "srcs/includes/minishell.h"

void	ft_count_commands(int *count, char **buf)
{
	int i;

	i = 0;
	while (buf[i++])
	{
		*count += 1;
	}
}

char	*if_pipes(char **commands, t_all *all, int *res)
{
	int		count;
	int		i;

	i = 0;
	ft_count_commands(&count, commands);
	if (!(all->cmd = malloc(sizeof(t_cmd) * (count + 1))))
		*res = -1;
	all->cmd[count].cmd = NULL;
	while (res == 0 && all->cmd[i].cmd)
	{
		if (!(all->cmd[i].cmd = ft_split_quote(commands[i], 
		"\t\n\r\v \f")))
		{
			ft_malloc_error(NULL);
			free_read(&commands, NULL);
			//free t_cmd
			return (NULL);
		}
		ft_free((void **)&commands[i]);
		i++;
	}
	pipes_id(all);
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
	{
		if (!(if_pipes(commands, all, &res)))
			return ;
		/*ft_count_commands(&count, commands);
		if (!(all->cmd = malloc(sizeof(t_cmd) * (count + 1))))
			res = -1;
		all->cmd[count].cmd = NULL;
		while (res == 0 && all->cmd[i].cmd)
		{
			if (!(all->cmd[i].cmd = ft_split_quote(commands[i], 
			"\t\n\r\v \f")))
			{
				ft_malloc_error(NULL);
				free_read(&commands, NULL);
				//free t_cmd
				return ;
			}
			ft_free((void **)&commands[i]);
			i++;
		}
		pipes_id(all);*/
	}
	if (res == -1)
	{
		ft_malloc_error(NULL);
		free_read(&commands, NULL);
		return ;
	}
	ft_free((void **)commands);
}

char	*read_checks(t_all *all, int *count, char **buf, char *line)
{
	int		i;

	i = 0;
	if (!(ft_check_errors_line(line, all)))
	{
		free_read(&buf, &line);
		return (NULL);
	}
	buf = ft_split_quote(line, ";");
	if (buf)
		ft_count_commands(count, buf);
	else
	{
		free_read(&buf, &line);
		ft_malloc_error(NULL);
		return (NULL);
	}
	while (i != *count)
		ft_command_exec(buf[i++], all);
	return ("done");
}

char	*ft_read(t_all *all)
{
	char	*line;
	char	**buf;
	int		count;

	count = 0;
	buf = NULL;
	line = NULL;
	if ((get_next_line(1, &line)) == 1)
	{
		if (!(read_checks(all, &count, buf, line)))
			return ("error");
		/*if (!(ft_check_errors_line(line, all)))
		{
			free_read(&buf, &line);
			return ("erreur");
		}
		buf = ft_split_quote(line, ";");
		if (buf)
			ft_count_commands(&count, buf);
		else
		{
			free_read(&buf, &line);
			ft_malloc_error(NULL);
			return ("erreur");
		}
		while (i != count)
			ft_command_exec(buf[i++], all);*/
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
	t_all	all;

	x = 1;
	welcomer();
	ft_init_all(&all);
	while (x != 0)
	{
		ft_putstr_fd("~:", 1);
		tmp = ft_read(&all);
		if (tmp == NULL)
			x = 0;
	}
	//free all
	byebye();
	return (1);
}
