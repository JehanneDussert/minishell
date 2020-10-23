/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 14:20:42 by ede-banv          #+#    #+#             */
/*   Updated: 2020/10/23 14:52:00 by marvin           ###   ########.fr       */
=======
/*   By: jdussert <jdussert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 14:20:42 by ede-banv          #+#    #+#             */
/*   Updated: 2020/10/23 11:37:53 by jdussert         ###   ########.fr       */
>>>>>>> 3f0e08175ef12a4dd61aaa40524412a6825666fa
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_line(t_lst *lst, int n)
{
	if (n == 1)
		ft_putstr_fd("declare -x ", 1);
	ft_putstr_fd(lst->key, 1);
	if (lst->content || n == 0)
		ft_putstr_fd("=", 1);
	if (lst->content && n == 1)
		ft_putstr_fd("\"", 1);
	ft_putstr_fd(lst->content, 1);
	if (lst->content && n == 1)
		ft_putendl_fd("\"", 1);
	else
		ft_putendl_fd("", 1);
	lst->tmp = 1;
}

void	ascii_tri_export(t_all *all)
{
	t_lst	*tmp;
	int		count;
	t_lst	*small;

	count = ft_lstsize((t_list *)all->alst);
	while (count--)
	{
		tmp = all->alst;
		small = NULL;
		while (tmp)
		{
			if (tmp->tmp == 0 && (!small || ft_strcmp(small->key, tmp->key) > 0))
				small = tmp;
			tmp = tmp->next;
		}
		print_line(small, 1);
	}
	empty_tmp(all);
}

int		export_errors(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (0);
	i++;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int		not_existent(char *cmd, t_all *all)
{
	t_lst	*tmp;
	char	*w1;
	char	*w2;

	if (!create_words(&w1, &w2, cmd))
		return (ft_malloc_error("export"));
	tmp = all->alst;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, w1) == 0)
		{
			ft_free((void **)&w1);
			tmp->content = w2;
			return (1);
		}
		tmp = tmp->next;
	}
	if(!(tmp = ft_lstnew_ms(w1, w2)))
	{
		free_read((char ***)&w1, &w2);
		return (ft_malloc_error("export"));
	}
	ft_lstadd_back_ms(&all->alst, tmp);
	return (1);
}

void	export_id(char **cmd, t_all *all)
{
	int 	i;
	int		catch;

	i = 1;
	catch = 0;
	if (!cmd[1])
		ascii_tri_export(all);
	else
	{
		while (cmd[i])
		{
			if (export_errors(cmd[i]))
			{
				if (!(not_existent(cmd[i], all)))
				{
					catch = 1;
					all->err = 1;
				}
			}
			else
			{
				catch = 1;
				all->err = 1;
			}
			i++;
		}
	}
	if (catch == 0)
		all->err = 0;
}