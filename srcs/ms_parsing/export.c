/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdussert <jdussert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 14:20:42 by ede-banv          #+#    #+#             */
/*   Updated: 2020/10/21 17:56:43 by jdussert         ###   ########.fr       */
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
		if (ft_isalpha(str[i]) || str[i] == '_') // faire un return ? (on ne checke que le premier char)
			return (1);
		i++;
	}
	return (1);
}

int		not_existent(char *cmd, t_all *all)
{
	char	*ptr;
	char	*copie;
	t_lst	*tmp;
	char	*w1;
	char	*w2;

	if (!(copie = ft_strdup(cmd)))
		;//erreur malloc
	if((ptr = ft_strchr(copie, '=')))
	{
		*ptr = '\0';
		if (!(w1 = ft_strdup(copie)))
			;//error malloc
		if (!(w2 = ft_strdup(ptr + 1)))
			;//error malloc
	}
	else //no = | is it necessaire?
	{
		if (!(w1 = ft_strdup(copie)))
			;//error malloc
		w2 = NULL;
	}
	ft_free((void **)&copie);
	tmp = all->alst;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, w1) == 0)
		{
			ft_free((void **)&w1);
			tmp->content = w2;
			return (0);
		}
		tmp = tmp->next;
	}
	if(!(tmp = ft_lstnew_ms(w1, w2)))
		;//erreur malloc
	ft_lstadd_back_ms(&all->alst, tmp);
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
				not_existent(cmd[i], all);
			else
			{
				//recup code d'erreur et mettre ds $?
			}

			i++;
		}
	}

}