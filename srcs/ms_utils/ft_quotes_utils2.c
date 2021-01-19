#include "../includes/minishell.h"

void	ft_init_copy(t_copy *copy, char *comm)
{
	copy->i = 0;
	copy->j = 0;
	if_in_quote(&copy->d, &copy->s, comm);
}

void	ft_no_quote(char **comm, char ***new, t_copy *copy, t_all *all)
{
	if (comm[0][copy->i] == '$')
		ft_env(comm[0], new, copy, all);
	else
		ft_cmd_fill(comm, new, &copy->i, &copy->j);
}

void	ft_simple_quote(char **comm, t_copy *copy, char ***new)
{
	++copy->i;
	while (comm[0][copy->i] && comm[0][copy->i] != '\\' && comm[0][copy->i] != '\'' && copy->s-- >= 0)
		ft_delete_quotes(comm[0][(copy->i)++], new, &copy->j, '\'');
	if (comm[0][copy->i] && comm[0][copy->i] != '\\')
	{
		copy->i++;
		return ;
	}
}

void	ft_double_quote(char **comm, t_copy *copy, char ***new, t_all *all)
{
	++copy->i;
	if (comm[0][copy->i] == '$')
		ft_env(comm[0], new, copy, all);
	while (comm[0][copy->i] && comm[0][copy->i] != '\\' && comm[0][copy->i] != '\"' && copy->d-- >= 0)
		ft_delete_quotes(comm[0][(copy->i)++], new, &copy->j, '\"');
	if (comm[0][copy->i] && comm[0][copy->i] != '\\')
	{
		copy->i++;
		return ;
	}
}
