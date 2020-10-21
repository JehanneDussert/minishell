/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-banv <ede-banv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 14:20:42 by ede-banv          #+#    #+#             */
/*   Updated: 2020/10/21 15:56:44 by ede-banv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_line(t_lst *lst)
{
	ft_putstr_fd("declare -x ", 1);
	ft_putstr_fd(lst->key, 1);
	ft_putstr_fd("=\"", 1);
	ft_putstr_fd(lst->content, 1);
	ft_putendl_fd("\"", 1);
}

void	ascii_tri_export(t_all *all)
{
	t_lst	*tmp;
	int		count; //taille de la liste
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
		print_line(small);
		small->tmp = 1;
	}
	tmp = all->alst;
	while (tmp)
	{
		tmp->tmp = 0;
		tmp = tmp->next;
	}
}

int		export_errors(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalpha(str[i]) && str[i] != '_')
			return (0);
		if (ft_isalpha(str[i]) || str[i] == '_')
			return (1);
		i++;
	}
	return (1);
}

int		not_existent(char *cmd, t_all *all)
{
	char	*ptr;
	t_lst	*tmp;

	if((ptr = ft_strchr(env[i], '=')))
	{
		*ptr = '\0';
		if (!(w1 = ft_strdup(env[i])))
			;//error malloc
		if (!(w2 = ft_strdup(ptr + 1)))
			;//error malloc
	}
	else //no = | is it necessaire?
	{
		if (!(w1 = ft_strdup(env[i])))
			;//error malloc
		w2 = NULL;
	}
	tmp = all->alst;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, w1) == 0)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

void	export_id(char **cmd, t_all *all)
{
	int 	i;

	i = 1;
	if (!cmd[1])
		ascii_tri_export(all);
	else
	{
		while (cmd[i])
		{
			if (export_errors(cmd[i]))
			{
				if (not_exitent(cmd[i], all))
					lst_add_env(&cmd[i], all); //s'il existe deja remplacer
				else
					replace_key(cmd[i], all);
			}
			i++;
		}
	}

}